#include "ServerGames.h"

using namespace std;


#include <cstdlib>
#include "Server.h"
#include <fstream>
#include <sstream>

int main() {
  ifstream inFile;
  inFile.open("serverSettings");
  string x;
  int port = 0;
  if (!inFile) {
    cerr << "Unable to open file";
    exit(1);   // call system to stop
  }
  while (inFile >> x) if (x == "serverPort:") inFile >> x;

  stringstream geek(x); //not sure we are allowed to use
  geek >> port;

  inFile.close();
  Server server(port);
  try {
    server.start();
  } catch (const char *msg) {
    cout << "Cannot start server. Reason: " << msg << endl;
    exit(-1);
  }

  return 0;
}