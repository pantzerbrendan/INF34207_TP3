
#include <exception>
#include <iostream>
#include "../include/Thread.hpp"
#include "../include/Mutex.hpp"

Mutex *mtx;

void *function(void *arg)
{
  long long sig1 = reinterpret_cast<long long>(arg);
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
  Thread t1, t2;
  int i = 1;
  
  try
    {
      mtx = new Mutex();
      mtx->init();
      t1.create(function, (void*)i++);
      t2.create(function, (void*)i);
    }
  catch (std::exception e)
    {
      std::cerr << e.what() << std::endl;
    }
  t1.join();
  t2.join();
  return (0);
}
