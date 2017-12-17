#include "Client.h"

Client::Client(const char *serverIP, int serverPort) :
    serverIP(serverIP), serverPort(serverPort), clientSocket(0) {
}
void Client::connectToServer() {
  // Create a socket point
  clientSocket = socket(AF_INET, SOCK_STREAM, 0);
  if (clientSocket == -1) throw "Error opening socket";
  // Convert the ip string to a network address
  struct in_addr address;
  if (!inet_aton(serverIP, &address)) {
    throw "Can't parse IP address";
  }
  // Get a hostent structure for the given host address
  struct hostent *server;
  server = gethostbyaddr((const void *) &address, sizeof(address), AF_INET);
  if (server == NULL) throw "Host is unreachable";

  // Create a structure for the server address
  struct sockaddr_in serverAddress;
  bzero((char *) &address, sizeof(address));
  serverAddress.sin_family = AF_INET;
  memcpy((char *) &serverAddress.sin_addr.s_addr, (char *) server->h_addr, server->h_length);
  // htons converts values between host and network byte orders
  serverAddress.sin_port = htons(serverPort);
  // Establish a connection with the TCP server
  if (connect(clientSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) == -1) {
    throw "Error connecting to server";
  }
}
int Client::getClientSocket() const {
  return clientSocket;
}
/*string Client::sendMove() {
  char buffer[100];
  bzero(&buffer,sizeof(buffer));

  ssize_t r = read(clientSocket, buffer, 5 *sizeof(char));
  if (r == -1 || buffer == nullptr) {
    throw "Error reading result from socket";
  }

  cout << buffer;
<<<<<<< HEAD
}*/
/*=======

}
>>>>>>> e5fcee56e980f3b0f6cc02343ee3eedb7deceaf6*/
