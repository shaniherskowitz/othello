#ifndef OTHELLO_REMOTEPLAYERMENU_H
#define OTHELLO_REMOTEPLAYERMENU_H

#include "Game.h"
#include "Client.h"

/**
 * Defining a RemotePlayerMenu class to control the communication between the
 * client socket and player.
 */
class RemotePlayerMenu {
  GameUI *print;

 public:
    /**
     * The RemotePlayerMenu constructor.
     * @param print1 The GameUI.
     */
  RemotePlayerMenu(GameUI *print1);

    /**
     * The method returns the game the player is playing.
     * @return The game the player is playing.
     */
  Game *getGame();

    /**
     * The method opens the client settings file and opens a socket connection.
     * @return The client socket.
     */
  int connectToServer();

    /**
     * The method connects the player of given client socket to a gameRoom.
     * @param socket The given client socket.
     */
  void connectToRoom(int socket);

    /**
     * The method writes the command with its arguments to the given socket.
     * @param socket The given player socket.
     * @param command The command to execute.
     * @param args The command's arguments.
     */
  void sendCommand(int socket, string command, string args);

    /**
     * The method helps the getGamesList to read the strings from the socket.
     * @param socket The given socket.
     * @param size The amount of strings to be read.
     * @param gamesList The list of games represented in strings.
     */
  void getGamesListHelper(int socket, int size, vector<string> *gamesList);

    /**
     * The method gets an empty vector of gameNames and updates it from the
     * server's gameLists.
     * @param socket The given socket.
     * @param gamesList The gamesList vector.
     */
  void getGamesList(int socket, vector<string> *gamesList);

    /**
     * The method reads an integer from the socket.
     * @param socket The given socket.
     * @return The read integer.
     */
  int readNum(int socket);

    /**
     * The method scans the menu's choice/option from player.
     * @return The choice/option.
     */
    int getChoice();

    /**
     * The method checks the read/write to the socket.
     * @param bytesWritten The number of bytes read from socket.
     */
    void checkSocketConnection(ssize_t bytesWritten);

    /**
     * The method sends a command to start a game of gameName to the server.
     * @param socket The server socket.
     * @param gamesList The gamesList.
     */
    void sendStartCommand(int socket, vector<string> gamesList);

    /**
     * The method checks if game of gameName is an existing game.
     * @param gamesList The list of games.
     * @param gameName The game of gameName.
     * @return True if the gameName already exists on the list, else false.
     */
    bool isInGamesList(vector<string> gamesList, string gameName);

    /**
     * the method sends a join game command to a specific game of gameName.
     * @param socket the server socket.
     * @param gamesList The gamesList.
     */
    void sendJoinCommand(int socket, vector<string> gamesList);

    /**
     * The method opens the client settings file and initializes a client
     * accordingly.
     * @return The initialized client.
     */
    Client *openFile();
};

#endif //OTHELLO_REMOTEPLAYERMENU_H
