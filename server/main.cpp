//
// Shani Herskowitz: 321659387
// Liora Zaidner: 323742775
//
using namespace std;
#include "Server.h"
int main() {
  Server server(8000);
  try {
    server.start();
  } catch (const char *msg) {
    cout << "Cannot start server. Reason: " << msg << endl;
    exit(-1);
  }
  //Server server(10000);
  //server.start();
  server.stop();
  //game = new Game(new HumanPlayer(Tile(X)), new RemotePlayer(Tile(O)), print, DEF_SIZE);

  return 0;
}