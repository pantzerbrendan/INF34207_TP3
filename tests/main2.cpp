
#include <vector>
#include <iostream>
#include "../include/Thread.hpp"
#include "../include/Mutex.hpp"
#include "../include/IThreadable.hpp"

Mutex *mtx;

void *function(void *args)
{
  long long sig1 = reinterpret_cast<long long>(args);
  int sig = static_cast<int>(sig1);
  for (int index = 0; index < 10; index++)
    {
      mtx->lock();
      std::cout << sig << " : " << index << std::endl;
      mtx->unlock();
    }
  
  return (NULL);
}

int main(int ac, char **av)
{
  std::vector<Thread *> threads;

  mtx = new Mutex();
  mtx->init();
  for (int i = 0; i < 5; i++)
    threads.push_back(new Thread());

  for (int i = 0; i < 5; i++)
    threads[i]->create(function, (void*)i);

  for (int i = 0; i < 5; i++)
    threads[i]->join();

  threads.clear();
  return (0);
}
