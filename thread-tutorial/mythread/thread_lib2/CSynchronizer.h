#ifndef _SYNCHRONIZER_H
#define _SYNCHRONIZER_H

#include <pthread.h>

class CSynchronizer
{
private:
    CSynchronizer();

public:
    virtual ~CSynchronizer();
    static CSynchronizer *createInstance();
    void lock();
    void unlock();
    void wait();
    void notifyAll();

private:
    bool wait(int msec);

    pthread_t fThreadID;
    pthread_mutex_t fLock;
    pthread_mutex_t fLockForWait;
    pthread_mutex_t fLockForNotify;
    pthread_cond_t fWait;
};

#endif /* _SYNCHRONIZER_H */
