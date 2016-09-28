#include <stddef.h>
#include <errno.h>
#include <assert.h>

#include "CCondVal.h"

// constructors & destructor
CCondVal::CCondVal()
    : fMutex()
{
    fMutex = PTHREAD_COND_INITIALIZER;;
    pthread_cond_init(&fCond, NULL);
}

// public member functions
CCondVal::~CCondVal()
{
    pthread_cond_destroy( &fCond );
}

CCondVal* CCondVal::createInstance()
{
    return new CCondVal();
}


void CCondVal::lockForSync()
{
    fMutex.lock();
}

void CCondVal::unlockForSync()
{
    fMutex.unlock();
}


// Release a lock, then waits until either some other thread invokes the notify
// method or the notifyAll method
void CCondVal::wait()
{
    pthread_cond_wait(&fCond, fMutex.get_data());
}

void CCondVal::notifyAll()
{
    pthread_cond_broadcast(&fCond);
}

