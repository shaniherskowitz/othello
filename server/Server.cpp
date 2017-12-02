//
// Created by liora on 02/12/17.
//

#include "Server.h"
#include "Player.h"
#include "RemotePlayer.h"
#include "Game.h"

using namespace std;
#define MAX_CONNECTED_CLIENTS 5

Server::Server(int port): port(port), serverSocket(0) {}

void Server::start() {
    // Create a socket point
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) throw "Error opening socket";

    // Assign a local address to the socket
    struct sockaddr_in serverAddress;
    bzero((void *) &serverAddress, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(port);
    if (bind(serverSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) == -1) {
        throw "Error on binding";
    }

    // Start listening to incoming connections
    listen(serverSocket, MAX_CONNECTED_CLIENTS);
    // Define the client socket's structures
    struct sockaddr_in playerAddress1;
    struct sockaddr_in playerAddress2;
    socklen_t playerAddressLen1;
    socklen_t playerAddressLen2;
    while (true) {
        cout << "Waiting for player X to connect..." << endl;
        // Accept a new client connection
        int playerSocket1 = accept(serverSocket, (struct sockaddr *) &playerAddress1, &playerAddressLen1);
        if (playerSocket1 == -1) throw "Error on accept";
        Player* player1 = new RemotePlayer(Tile(X), playerSocket1);
        cout << "Player X connected. Waiting for player O to connect..." << endl;

        // Accept a new client connection
        int playerSocket2 = accept(serverSocket, (struct sockaddr *) &playerAddress2, &playerAddressLen2);
        if (playerSocket2 == -1) throw "Error on accept";
        cout << "Player O connected." << endl;
        Player* player2 = new RemotePlayer(Tile(O), playerSocket2);
        GameUI* print = new ConsolUI();
        Game game = Game(player1, player2, print, 8);
        game.run();
        //handleClient(clientSocket);
        // Close communication with the client
        close(playerSocket1);
        close(playerSocket2);
    }
}

// Handle requests from a specific client
void Server::handleClient(int clientSocket) {
    int arg1, arg2;
    char op;
    while (true) {
        // Read new exercise arguments
        int n = read(clientSocket, &arg1, sizeof(arg1));
        if (n == -1) {
            cout << "Error reading arg1" << endl;
            return;
        }
        if (n == 0) {
            cout << "Client disconnected" << endl;
            return;
        }
        n = read(clientSocket, &op, sizeof(op));
        if (n == -1) {
            cout << "Error reading operator" << endl;
            return;
        }
        n = read(clientSocket, &arg2, sizeof(arg2));
        if (n == -1) {
            cout << "Error reading arg2" << endl;
            return;
        }
        cout << "Got exercise: " << arg1 << op << arg2 << endl;
        int result = calc(arg1, op, arg2);
        // Write the result back to the client
        n = write(clientSocket, &result, sizeof(result));
        if (n == -1) {
            cout << "Error writing to socket" << endl;
            return;
        }
    }
}

int Server::calc(int arg1, const char op, int arg2) const {
    switch (op) {
        case '+':
            return arg1 + arg2;
        case '-':
            return arg1 - arg2;
        case '*':
            return arg1 * arg2;
        case '/':
            return arg1 / arg2;
        default:
            cout << "Invalid operator" << endl;
            return 0;
    }
}
void Server::stop() {
    close(serverSocket);
}
