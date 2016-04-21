
#include <iostream>
#include <string>
#include <string.h>
#include <errno.h>
#include "Thread.hpp"

uint64_t    gettid(pthread_t self);
void        t_handle_error(const std::string &function, const std::string &file, int line, int error_value);

/*
** Name : Thread (constructor)
** Parameters : none
** Return value : none
**
** Description :
** * Default constructor for the Thread object.
*/
Thread::Thread() {}

/*
** Name : ~Thread (destructor)
** Parameters : none
** Return value : none
**
** Description :
** * Default destructor for the Thread object. Automatically exits the thread.
*/
Thread::~Thread()
{
    this->exit();
}

/*
** Name : create
** Parameters :
** Return value : (int)
**
** Description :
** * Creates a new thread. The routine passed as parameter is the one that will
** * be used by the thread.
*/
int         Thread::create(void *(*routine) (void *), void *params)
{
    int ret_val = pthread_create(this->_handle, NULL, routine, params);
    if (ret_val == -1) handle_error(__FUNCTION__, __FILE__, __LINE__, ret_val);

    this->_tid = gettid(this->_handle);
    return ret_val;
}

/*
** Name : create
** Parameters : object, parameters
** Return value : (int)
**
** Description :
** * Creates a new thread. The routine called is the `operator()` member function
** * from the object passed as parameter. This object has to be inheriting the `IThreadable` class.
*/
int         Thread::create(IThreadable *obj, void *params)
{
    int ret_val = pthread_create(this->_handle, NULL, obj->operator(), params);
    if (ret_val == -1) handle_error(__FUNCTION__, __FILE__, __LINE__, ret_val);

    this->_tid = gettid(this->_handle);
    return ret_val;
}

/*
** Name : init
** Parameters :
** Return value : (int)
**
** Description :
** * Initializes a new thread. The routine passed as parameter is the one that will
** * be used by the thread.
*/
int         Thread::init(void *(*routine) (void *), void *params)
{
    return this->create(routine, params);
}

/*
** Name : init
** Parameters : object, parameters
** Return value : (int)
**
** Description :
** * Initializes a new thread. The routine called is the `operator()` member function
** * from the object passed as parameter. This object has to be inheriting the `IThreadable` class.
*/
int         Thread::init(IThreadable *obj, void *params)
{
    return this->create(obj, params);
}

/*
** Name : join
** Parameters :
** Return value : (int)
**
** Description :
** * Joins the thread passed as parameter. Suspends execution of the calling thread
** * until the target thread terminates, unless the target thread has already terminated.
*/
int         Thread::join(void **thread_return = NULL)
{
    int ret_val = pthread_join(this->_handle, thread_return);
    if (ret_val == -1) handle_error(__FUNCTION__, __FILE__, __LINE__, ret_val);

    return ret_val;
}

/*
** Name : exit
** Parameters : return value for the joined thread
** Return value : none
**
** Description :
** * Terminates the calling thread and returns a value via retval that (if the thread
** * is joinable) is available to another thread in the same process that calls `join`.
*/
void         Thread::exit(void *retval = NULL)
{
    pthread_exit(retval);
}

/*
** Name : yield
** Parameters : none
** Return value : (int)
**
** Description :
**
*/
int         Thread::yield()
{
    std::clog << "Not implemented yet." << std::endl;
}

/*
** Name : self
** Parameters : none
** Return value : (pthread_t) Reference on the ID / handle
**
** Description :
** * Returns a reference on the current thread ID / handle.
*/
pthread_t   &Thread::self() const { return this->_handle; }

/*
** Name : getThreadID
** Parameters :
** Return value : (uint64_t)
**
** Description :
** * Returns the identifier of the thread.
*/
uint64_t    Thread::getThreadID() const { return this->_tid; }

/** ************************************************************************ **/

/*
** Name : gettid
** Parameters : thread from which to get the ID from
** Return value : (uint64_t) ID of the thread passed as parameter
**
** Description :
** * Gets the id of the thread passed as parameter and returns it.
*/
static uint64_t     gettid(pthread_t self)
{
    uint64_t        tid = 0;

    memcpy(&tid, &self, std::min(sizeof(tid), sizeof(self)));
    return (tid);
}

/*
** Name : t_handle_error
** Parameters : function, filename, line (these 3 params are for the error localization),
**              error_value (return value from the function that failed).
** Return value : none
**
** Description :
** * Writes a complete error message on the error output (std::cerr).
** * Indicates the localization of the error (function, file and line), the return value of
** * this function. Then displays the complete error with `errno`.
*/
static void         t_handle_error(const std::string &function, const std::string &file, int line, int error_value)
{
    std::cerr << T_RED;
    std::cerr << "An error occured at `" << function << "` ("
        << file << ":" << line << ")\t["
        << error_value << "]" << std::endl;
    std::cerr << "(" << errno << ") " << strerror(errno);
    std::cerr << T_RESET << std::endl;
}
