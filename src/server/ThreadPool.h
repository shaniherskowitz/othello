//
// Created by shani herskowitz on 1/11/18.
//

#ifndef OTHELLO_THREADPOOL_H
#define OTHELLO_THREADPOOL_H
#include <vector>
#include "Task.h"
#include <queue>
class ThreadPool {
 public:
  /**
   * creates pool with specific amount of threads.
   * @param threadsNum
   */
  ThreadPool(int threadsNum);
  /**
   *
   * @param task adds tak for pool to handel.
   */
  void addTask(Task *task);
  /**
   * delete all threads in pool.
   */
  void terminate();
  /**
   * The ThredPool's destructor.
   */
  virtual ~ThreadPool();
 private:
  std::queue<Task *> tasksQueue;
  pthread_t* threads;
  void executeTasks();
  bool stopped;
  pthread_mutex_t lock;
  static void *execute(void *arg);


};

#endif //OTHELLO_THREADPOOL_H
