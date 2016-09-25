#include <stddef.h>
#include <errno.h>
#include <sys/time.h>
#include <assert.h>
#include <iostream>

#include "CSynchronizer.h"

// constructors & destructor
CSynchronizer::CSynchronizer()
{
    if (pthread_mutex_init(&fMutex, NULL) != 0) {
        assert(false);
    }

    if (pthread_cond_init(&fCond, NULL) != 0) {
        assert(false);
    }
}

CSynchronizer::~CSynchronizer()
{
    if (pthread_mutex_destroy(&fMutex) != 0) {
        assert(false);
    }
    
    if (pthread_cond_destroy(&fCond) != 0) {
        assert(false);
    }
}

// public member functions
CSynchronizer* CSynchronizer::createInstance()
{
    return new CSynchronizer();
}

// Release a lock, then waits until either some other thread invokes the notify
// method or the notifyAll method
void CSynchronizer::wait()
{
    if (pthread_mutex_lock(&fMutex) != 0) {
        assert(false);
    }

	::std::cout << "CSynchronizer::wait() : before pthread_cond_wait()" << ::std::endl;
    if (pthread_cond_wait(&fCond, &fMutex) != 0) {
        assert(false);
    }
	::std::cout << "CSynchronizer::wait() : after pthread_cond_wait()" << ::std::endl;

    if (pthread_mutex_unlock(&fMutex) != 0) {
        assert(false);
    }
}


void CSynchronizer::notifyAll()
{
    if (pthread_mutex_lock(&fMutex) != 0) {
        assert(false);
    }

    if ((pthread_cond_broadcast(&fCond)) != 0) {
        assert(false);
    }
	::std::cout << "CSynchronizer::notifyAll() : after pthread_cond_broadcast()" << ::std::endl;

    if (pthread_mutex_unlock(&fMutex) != 0) {
        assert(false);
    }
}

