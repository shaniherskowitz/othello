

//
// Created by shani herskowitz on 1/11/18.
//

#include <sstream>
#include "Task.h"
#include "ServerGames.h"
#include "commands/CommandsManager.h"
#define END_GAME -2
#include <cmath>
int Task::getClientSocket() const {
  return clientSocket;
}
void *Task::getStart() const {
  return start;
}
#define CLOSE_GAME ""

Task::Task(int clientSocket, void* start) : clientSocket(clientSocket) , start(start), taken(false){}

bool Task::isTaken() const {
  return taken;
}
void Task::setTaken(bool taken) {
  Task::taken = taken;
}
