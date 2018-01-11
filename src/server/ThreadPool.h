//
// Created by shani herskowitz on 1/11/18.
//

#ifndef OTHELLO_THREADPOOL_H
#define OTHELLO_THREADPOOL_H
#include <vector>
#include "Task.h"
class ThreadPool {
 public:
  ThreadPool(int threadCount);
  void closeThreads();
  static void *startTask(void *args);
  void addTask(Task task);
 private:
  std::vector<pthread_t> listOfThreads;


};

#endif //OTHELLO_THREADPOOL_H
