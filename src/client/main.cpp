#include "Client.h"
#include "Menu.h"
using namespace std;
int main() {
  Menu *menu = new Menu();
  menu->showMenu();
  delete menu;
}