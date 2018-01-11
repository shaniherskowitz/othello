//
// Created by shani herskowitz on 1/11/18.
//

#include <pthread.h>
#include <deque>
#include "ThreadPool.h"
#include "Server.h"
pthread_mutex_t mutex1;
std::vector<Task> listOfTasks;
template<
    class Task,
    class Container = std::deque<Task>
> class queue;


ThreadPool::ThreadPool(int threadCount) {
  pthread_t currThread;
  for (int i = 0; i < threadCount; ++i) {
    int rc = pthread_create(&currThread, NULL, &ThreadPool::startTask, &listOfTasks);
    if (rc != 0) {
      cout << "Error: unable to create thread, " << rc << endl;
      exit(-1);
    }
    listOfThreads.push_back(currThread);
  }

}

void *ThreadPool::startTask(void *args) {
  while (true) {

    vector<Task> test = listOfTasks;
    for (int i = 0; i < listOfTasks.size(); ++i) {
      int clientSocket = listOfTasks[i].getClientSocket();
      if(!listOfTasks[i].isTaken()) {
        if (clientSocket == -1) ((Server *) listOfTasks[i].getStart())->stop();
        else ((Server *) listOfTasks[i].getStart())->handleClient(clientSocket);
        pthread_mutex_trylock(&mutex1);
        listOfTasks[i].setTaken(true);
        pthread_mutex_unlock(&mutex1);
      }
    }

  }

  return args;
}

void ThreadPool::closeThreads() {
  for (int i = 0; i < listOfThreads.size(); ++i) {
    pthread_detach(listOfThreads[i]);
    pthread_cancel(listOfThreads[i]);
  }
}

void ThreadPool::addTask(Task task) {
  pthread_mutex_trylock(&mutex1);
  listOfTasks.push_back(task);
  pthread_mutex_unlock(&mutex1);
}
/*void ThreadPool::removeTask(Task task) {
  for (int i = 0; i < listOfTasks.size(); ++i) {
    if (listOfTasks[i].getClientSocket() == task.getClientSocket());
  }
}*/