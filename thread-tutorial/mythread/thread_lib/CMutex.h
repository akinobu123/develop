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
    
    pthread_mutex_t * get_data() { return &fMutex; }

private:
    pthread_mutex_t fMutex;
};

#endif /* _C_MUTEX_H */
