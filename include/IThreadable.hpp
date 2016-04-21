
#ifndef ITHREADABLE_HPP_
#define ITHREADABLE_HPP_

/**
*** Name : IThreadable
***
*** Description :
*** *
**/
class IThreadable
{
private:
public:
    IThreadable();
    ~IThreadable();

    virtual void    *operator()(void *args) = 0;
}

#endif /* !ITHREADABLE_HPP_ */
