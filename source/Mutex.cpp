
#include <iostream>
#include <string>
#include <string.h>
#include <errno.h>
#include "Mutex.hpp"

/*
** Name : m_handle_error
** Parameters : function, filename, line (these 3 params are for the error localization),
**              error_value (return value from the function that failed).
** Return value : none
**
** Description :
** * Writes a complete error message on the error output (std::cerr).
** * Indicates the localization of the error (function, file and line), the return value of
** * this function. Then displays the complete error with `errno`.
*/
static void         m_handle_error(const std::string &function, const std::string &file, int line, int error_value)
{
    std::cerr << M_RED;
    std::cerr << "An error occured at `" << function << "` ("
        << file << ":" << line << ")\t["
        << error_value << "]" << std::endl;
    std::cerr << "(" << errno << ") " << strerror(errno);
    std::cerr << M_RESET << std::endl;
}

/** ************************************************************************ **/

/*
** Name : Mutex (constructor)
** Parameters : none
** Return value : none
**
** Description :
** * Default constructor for a Mutex object.
*/
Mutex::Mutex() {}

/*
** Name : ~Mutex (destructor)
** Parameters : none
** Return value : none
**
** Description :
** * Default destructor for the Mutex object. Automatically unlocks the Mutex.
*/
Mutex::~Mutex()
{
    int value = this->unlock();
}

/*
** Name : init
** Parameters : none
** Return value : none
**
** Description :
** * Initializes the Mutex object. This function has to be called before any other one.
*/
void        Mutex::init()
{
    this->_sock = PTHREAD_MUTEX_INITIALIZER;
}

/*
** Name : lock
** Parameters : none
** Return value : (int) return value from the `pthread_mutex_lock` function
**
** Description :
** * Locks the Mutex.
*/
int         Mutex::lock()
{
    int ret_val = pthread_mutex_lock(&this->_sock);
    if (ret_val) m_handle_error(__FUNCTION__, __FILE__, __LINE__, ret_val);

    return ret_val;
}

/*
** Name : unlock
** Parameters : none
** Return value : (int) return value from the `pthread_mutex_unlock` function
**
** Description :
** * Unlocks the Mutex.
*/
int         Mutex::unlock()
{
    int ret_val = pthread_mutex_unlock(&this->_sock);
    if (ret_val) m_handle_error(__FUNCTION__, __FILE__, __LINE__, ret_val);

    return ret_val;
}

/*
** Name : trylock
** Parameters : none
** Return value : (int) return value from the `pthread_mutex_trylock` function
**
** Description :
** * Tries to lock the Mutex.
*/
int         Mutex::trylock()
{
    int ret_val = pthread_mutex_trylock(&this->_sock);
    if (ret_val) m_handle_error(__FUNCTION__, __FILE__, __LINE__, ret_val);

    return ret_val;
}
