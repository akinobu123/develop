#ifndef _C_MUTEX_H
#define _C_MUTEX_H

#include <pthread.h>

class CMutex
{
private:
    CMutex();

public:
    virtual ~CMutex();
    static CMutex *createInstance();
    void lock();
    void unlock();

private:
    pthread_mutex_t fMutex;
};

#endif /* _C_MUTEX_H */
