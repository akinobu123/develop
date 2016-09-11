#ifndef _C_MUTEX_H
#define _C_MUTEX_H

#include <pthread.h>

class CMutex
{
public:
    CMutex();
    virtual ~CMutex();
    void lock();
    void unlock();

private:
    pthread_mutex_t fMutex;
};

#endif /* _C_MUTEX_H */
