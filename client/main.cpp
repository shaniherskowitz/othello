//
// Created by shani herskowitz on 12/2/17.
//

#include "Client.h"
#include "Menu.h"
using namespace std;
int main() {
  Menu *menu = new Menu();
  menu->showMenu();
  delete menu;
}