
#ifndef THREAD_HPP_
#define THREAD_HPP_

#include <pthread.h>
#include <sys/types.h>
#include <stdint.h>
#include "IThreadable.hpp"

#define T_RED       "\033[31m"
#define T_RESET     "\033[0m"

class Thread
{
private:
    pthread_t       _handle;
    uint64_t        _tid;

public:
    Thread();
    ~Thread();

    int             create(void *(*routine) (void *), void *params);
  //    int             create(IThreadable *obj, void *params);

    int             init(void *(*routine) (void *), void *params);
  //    int             init(IThreadable *obj, void *params);

    int             join(void **thread_return = NULL);
    void	    exit(void *retval = NULL);
    int             yield();
    pthread_t       self() const;

    uint64_t        getThreadID() const;
};

#endif /* !THREAD_HPP_ */
