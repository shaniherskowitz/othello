#include "Client.h"
#include "Menu.h"

using namespace std;

/**
 * A main class to run the client connection.
 * @return
 */
int main() {
  Menu *menu = new Menu();
  menu->showMenu();
  delete menu;
}