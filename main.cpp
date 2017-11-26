#include "Menu.h"
int main() {
  Menu *menu = new Menu();
  menu->showMenu();
  delete menu;

  return 0;
}