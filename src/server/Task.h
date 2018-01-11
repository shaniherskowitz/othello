//
// Created by shani herskowitz on 1/11/18.
//

#ifndef OTHELLO_TASK_H
#define OTHELLO_TASK_H

class Task {
 public:
  Task(int clientSocket, void* start);
  int getClientSocket() const;
  void *getStart() const;
  bool isTaken() const;
  void setTaken(bool taken);
 private:
  int clientSocket;
  void* start;
  bool taken;


};

#endif //OTHELLO_TASK_H
