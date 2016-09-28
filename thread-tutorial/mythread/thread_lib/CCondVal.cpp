#include <stddef.h>
#include <errno.h>
#include <sys/time.h>
#include <assert.h>
#include <iostream>

#include "CCondVal.h"

// constructors & destructor
CCondVal::CCondVal()
	: fMutex(PTHREAD_MUTEX_INITIALIZER)
	, fCond(PTHREAD_COND_INITIALIZER)
{
}

bool CCondVal::init()
{
    pthread_mutex_init(&fMutex, NULL);
    pthread_cond_init(&fCond, NULL);
    return true;
}

// public member functions
CCondVal::~CCondVal()
{
    pthread_cond_destroy( &fCond );
    pthread_mutex_destroy( &fMutex );
}

CCondVal* CCondVal::createInstance()
{
    CCondVal* tmp = new CCondVal();
    if( ! tmp->init() ) {
        return NULL;
    }
    return tmp;
}


void CCondVal::lockForSync()
{
    int ret = 0;
    ret = pthread_mutex_lock(&fMutex);
    assert( ret == 0 );
}

void CCondVal::unlockForSync()
{
    int ret = 0;
    ret = pthread_mutex_unlock(&fMutex);
    assert( ret == 0 );
}


// Release a lock, then waits until either some other thread invokes the notify
// method or the notifyAll method
void CCondVal::wait()
{
    pthread_cond_wait(&fCond, &fMutex);
}

void CCondVal::notifyAll()
{
    pthread_cond_broadcast(&fCond);
}

