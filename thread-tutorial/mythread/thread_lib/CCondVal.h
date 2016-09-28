#ifndef _CONDVAL_H
#define _CONDVAL_H

#include <pthread.h>

class CCondVal
{
private:
    CCondVal();
    bool init();

public:
    virtual ~CCondVal();
    static CCondVal *createInstance();
    
    void lockForSync();
    void unlockForSync();
    
    void wait();
    void notifyAll();

private:
    pthread_mutex_t fMutex;
    pthread_cond_t fCond;
};

#endif /* _CONDVAL_H */
