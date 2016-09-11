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
    void wait();
    void notifyAll();

private:
    bool wait(int msec);

    pthread_t fThreadID;
    pthread_mutex_t fMutex;
    pthread_cond_t fCond;
};

#endif /* _SYNCHRONIZER_H */
