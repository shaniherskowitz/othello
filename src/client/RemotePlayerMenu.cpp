//
// Created by shani herskowitz on 12/18/17.
//
#include "RemotePlayer.h"
#include <sstream>
#include "Client.h"
#include "Game.h"
#include "RemotePlayerMenu.h"

RemotePlayerMenu::RemotePlayerMenu(GameUI *print1) :print(print1){}
void RemotePlayerMenu::connectToRoom(int socket) {
    print->remotePlayerMenu();
    int choice = 0;
    stringstream ss;
    ss << socket;
    string socketString = ss.str();
    while (true) {
        cin >> choice;
        if (!cin.fail() && (choice == 2 || choice == 1)) break;
        print->problemWithInput();
        cin.clear();
        cin.ignore(std::numeric_limits<int>::max(), '\n');
    }
    if (choice == 1) {
        string command = "start";
        string gameName;
        cin >> gameName;
        sendCommand(socket, command,gameName);
    } else {
        string command = "list_games";
        string gameName;
        sendCommand(socket, command, "");
        getGames(socket);
        string command2 = "join";
        cin >> gameName;
        sendCommand(socket, command2, gameName);

    }
}

void RemotePlayerMenu::getGames(int socket) {
    string game;
    int size;
    ssize_t n = read(socket, &size, sizeof(size));
    if (n == -1) {
        print->socketWriteError();
        exit(1);
    }
    if (size == 0) {
        print->noAvailableGames();
        exit(1);
    }
    else print->getGames();
    while (size > 0) {
        read(socket, &game, sizeof(game));
        print->printGameRoom(game);
        size--;
    }
}

void RemotePlayerMenu::sendCommand(int socket, string command, string args) {
    /*string send = command + " " + args;
    ssize_t n = write(socket, &send, send.size() + 1);
    if (n == -1) {
      print->socketWriteError();
      exit(1);
    }*/
    string send = command + " " + args;
    ssize_t n = write(socket, &send, send.size() + 1);
    if (n == -1) {
        print->socketWriteError();
        exit(1);
    }
    for (int i = 0; i < send.size(); i++) {
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
                        new RemotePlayer(Tile(O), socket, false), print, 8);
    else
        return new Game(new RemotePlayer(Tile(X), socket, false),
                        new RemotePlayer(Tile(O), socket, true), print, 8);
}