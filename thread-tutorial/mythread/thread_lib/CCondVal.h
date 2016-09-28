#ifndef _SYNCHRONIZER_H
#define _SYNCHRONIZER_H

#include <pthread.h>

class CCondVal
{
private:
    CCondVal();

public:
    virtual ~CCondVal();
    static CCondVal *createInstance();
    void wait();
    void notifyAll();

private:
    pthread_t fThreadID;
    pthread_mutex_t fMutex;
    pthread_cond_t fCond;
};

#endif /* _SYNCHRONIZER_H */
