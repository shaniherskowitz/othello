//
// Created by shani herskowitz on 1/11/18.
//

#ifndef OTHELLO_LINE_H
#define OTHELLO_LINE_H
#include <queue>
#include <pthread.h>
pthread_mutex_t mutex2;
template<typename Data>
class concurrent_queue
{
 private:
  std::queue<Data> the_queue;
  mutable pthread_mutex_t mutex2;
  condition_variable the_condition_variable;
 public:
  void push(Data const& data)
  {
    boost::mutex::scoped_lock lock(the_mutex);
    the_queue.push(data);
    lock.unlock();
    the_condition_variable.notify_one();
  }

  bool empty() const
  {
    boost::mutex::scoped_lock lock(the_mutex);
    return the_queue.empty();
  }

  bool try_pop(Data& popped_value)
  {
    boost::mutex::scoped_lock lock(the_mutex);
    if(the_queue.empty())
    {
      return false;
    }

    popped_value=the_queue.front();
    the_queue.pop();
    return true;
  }

  void wait_and_pop(Data& popped_value)
  {
    boost::mutex::scoped_lock lock(the_mutex);
    while(the_queue.empty())
    {
      the_condition_variable.wait(lock);
    }

    popped_value=the_queue.front();
    the_queue.pop();
  }

};

#endif //OTHELLO_LINE_H
