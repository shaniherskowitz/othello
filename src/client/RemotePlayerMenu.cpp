//
// Created by shani herskowitz on 12/18/17.
//
#include "RemotePlayerMenu.h"
#include "RemotePlayer.h"
#include <sstream>
#include "Client.h"
RemotePlayerMenu::RemotePlayerMenu(GameUI *print1) :print(print1){}
void RemotePlayerMenu::connectToRoom(int socket) {
    print->remotePlayerMenu();
    int choice = getChoice();
    stringstream ss;
    ss << socket;
    string socketString = ss.str();
    vector<string> gamesList;
    getGamesList(socket, &gamesList);
    if (choice == 1) sendStartCommand(socket, gamesList);
    if (choice == 2) sendJoinCommand(socket, gamesList);
}

void RemotePlayerMenu::sendStartCommand(int socket, vector<string> gamesList) {
    string command = "start";
    string gameName;
    cin >> gameName;
    while (isInGamesList(gamesList, gameName)) {
        print->gameExists();
        cin >> gameName;
    }
    sendCommand(socket, command, gameName);
}

bool RemotePlayerMenu::isInGamesList(vector<string> gamesList, string gameName) {
    vector<string>::iterator it = gamesList.begin();
    while (it != gamesList.end()) {
        if (gameName == *it) return true;
        it++;
    }
    return false;
}

void RemotePlayerMenu::sendJoinCommand(int socket, vector<string> gamesList) {
    if (gamesList.empty()) {
        print->noAvailableGames();
        exit(1);
    }
    print->getGames();
    print->getGameRooms(gamesList);
    string command = "join";
    string gameName;
    cin >> gameName;
    while (!isInGamesList(gamesList, gameName)) {
        print->gameNotExists();
        cin >> gameName;
    }
    sendCommand(socket, command, gameName);
}

int RemotePlayerMenu::getChoice() {
    int choice = 0;
    while (true) {
        cin >> choice;
        if (!cin.fail() && (choice == 2 || choice == 1)) break;
        print->problemWithInput();
        cin.clear();
        cin.ignore(std::numeric_limits<int>::max(), '\n');
    }
    return choice;
}

void RemotePlayerMenu::getAvailableGames(int socket) {

}

void RemotePlayerMenu::getGamesList(int socket, vector<string> *gamesList) {
    string command = "list_games";
    sendCommand(socket, command, "");
    unsigned numGames;
    ssize_t n = read(socket, &numGames, sizeof(numGames));
    if (n == -1) {
        print->socketWriteError();
        exit(1);
    }
    //string gamesList[numGames];
    //gamesList.reserve(numGames);
    getGamesListHelper(socket, numGames, gamesList);
}

void RemotePlayerMenu::getGamesListHelper(int socket, int size, vector<string> *gamesList) {
    //vector<string> gamesList;
    //string tempGameList[size];
    for (int i = 0; i < size; i++) {
        int gameNameSize = readNum(socket);
        char gameName[50];
        for (int j = 0; j < gameNameSize; j++) {
            char current;
            ssize_t n = read(socket, &current, sizeof(char));
            if (n == -1) {
                print->socketWriteError();
                exit(1);
            }
            if (n == 0) {
                //print->noAvailableGames();
                exit(1);
            }
            gameName[j] = current;
        }
        gameName[gameNameSize] = '\0';
        //tempGameList[i] = string(gameName);
        gamesList->push_back(string(gameName));
    }
    //print->getGames();
    //print->getGameRooms(gamesList);
    //gamesList.insert(gamesList.begin() , tempGameList , tempGameList + size ) ;
}

int RemotePlayerMenu::readNum(int socket) {
    int num;
    ssize_t n = read(socket, &num, sizeof(num));
    if (n == -1) {
        print->socketWriteError();
        exit(1);
    }
    if (num == 0) {
        //print->noAvailableGames();
        exit(1);
    }
    return num;
}

void RemotePlayerMenu::sendCommand(int socket, string command, string args) {
    /*string send = command + " " + args;
    ssize_t n = write(socket, &send, send.size() + 1);
    if (n == -1) {
      print->socketWriteError();
      exit(1);
    }*/
    string send = command + " " + args + "\0";
    int sendSize = send.size();
    ssize_t n = write(socket, &sendSize, sizeof(int));
    if (n == -1) {
        print->socketWriteError();
        exit(1);
    }
    for (int i = 0; i < sendSize; i++) {
        n = write(socket, &send.at(i), sizeof(char));
        if (n == -1) {
            print->socketWriteError();
            exit(1);
        }
    }
}

int RemotePlayerMenu::connectToServer() {
    ifstream inFile;
    inFile.open("clientSettings");
    string x;
    int port = 0;
    if (!inFile) {
        cerr << "Unable to open file";
        exit(1);   // call system to stop
    }
    while (inFile >> x) {
        if (x == "serverPort:") {
            inFile >> x;
            stringstream geek(x); //not sure we are allowed to use
            geek >> port;
        }
        if (x == "serverIP:") {
            inFile >> x;
        }
    }
    const char *IP = x.c_str();
    inFile.close();
    Client client(IP, port);
    try {
        client.connectToServer();
        print->serverConnected();
    } catch (const char *msg) {
        print->serverConnectError(msg);
        exit(-1);
    }
    connectToRoom(client.getClientSocket());
    return client.getClientSocket();

}
Game* RemotePlayerMenu::getGame() {
    int socket = connectToServer();
    ssize_t n;
    int player;
    print->waitingForPlayer();
    n = read(socket, &player, sizeof(int));
    if (n == -1) {
        print->socketReadError();
        exit(-1);
    }
    if (player == 0)
        return new Game(new RemotePlayer(Tile(X), socket, true),
                        new RemotePlayer(Tile(O), socket, false), print, 3);
    else
        return new Game(new RemotePlayer(Tile(X), socket, false),
                        new RemotePlayer(Tile(O), socket, true), print, 3);
}