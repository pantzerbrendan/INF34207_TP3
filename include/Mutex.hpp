// threadMutexInit(), threadMutexLock(),
// threadMutextUnlock()

#ifndef MUTEX_HPP
#define MUTEX_HPP

#include <pthread.h>
#include <sys/types.h>

#define M_RED       "\033[31m"
#define M_RESET     "\033[0m"

class Mutex
{
private:
    pthread_mutex_t _sock;

public:
    Mutex();
    ~Mutex();

    void        init();
    int         lock();
    int         unlock();
    int         trylock();
};

#endif /* !MUTEX_HPP */
