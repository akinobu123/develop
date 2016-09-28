#ifndef _CONDVAL_H
#define _CONDVAL_H

#include <pthread.h>
#include "CMutex.h"

class CCondVal
{
private:
    CCondVal();

public:
    virtual ~CCondVal();
    static CCondVal *createInstance();
    
    void lockForSync();
    void unlockForSync();
    
    void wait();
    void notifyAll();

private:
    CMutex fMutex;
    pthread_cond_t fCond;
};

#endif /* _CONDVAL_H */
