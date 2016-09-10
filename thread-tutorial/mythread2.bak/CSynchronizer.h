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
    bool wait(int msec);
    void notifyAll();

private:
    pthread_t fThreadID;
    pthread_mutex_t fLock;
    pthread_cond_t fNotified;
};

#endif /* _SYNCHRONIZER_H */
