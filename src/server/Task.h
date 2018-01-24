//
// Created by shani herskowitz on 1/11/18.
//

#ifndef OTHELLO_TASK_H
#define OTHELLO_TASK_H

class Task {
 public:
  /**
   * creates new task with function to execute.
   * @param func  to execute in task
   * @param arg for the function.
   */
  Task(void * (*func)(void *arg), void* arg) :
      func(func), arg(arg) {}
  /**
   * executes tasks function.
   */
  void execute() {
    func(arg);
  }
  /**
   * tasks destructor.
   */
  virtual ~Task() {}
 private:
  void * (*func)(void *arg);
  void *arg;


};

#endif //OTHELLO_TASK_H
