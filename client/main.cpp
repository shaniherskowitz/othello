//
// Created by shani herskowitz on 12/2/17.
//

#include "../server/Server.h"
#include <iostream>
#include <stdlib.h>
using namespace std;
int main() {
  Server server(8000);
  try {
    server.start();
  } catch (const char *msg) {
    cout << "Cannot start server. Reason: " << msg << endl;
    exit(-1);
  }
}