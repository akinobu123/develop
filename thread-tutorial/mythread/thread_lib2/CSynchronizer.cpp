#include <stddef.h>
#include <errno.h>
#include <sys/time.h>
#include <assert.h>
#include <iostream>

#include "CSynchronizer.h"

// constructors & destructor
CSynchronizer::CSynchronizer()
{
	::std::cout << "CSynchronizer::CSynchronizer() : before pthread_xxx_init()" << ::std::endl;

    if (pthread_mutex_init(&fMutex, NULL) != 0)  assert(false);
    if (pthread_cond_init(&fCond, NULL) != 0)  assert(false);

	::std::cout << "CSynchronizer::CSynchronizer() : after pthread_xxx_init()" << ::std::endl;
}

CSynchronizer::~CSynchronizer()
{
	::std::cout << "CSynchronizer::~CSynchronizer() : before pthread_xxx_destroy()" << ::std::endl;

    if (pthread_mutex_destroy(&fMutex) != 0)  assert(false);
    if (pthread_cond_destroy(&fCond) != 0)  assert(false);

	::std::cout << "CSynchronizer::~CSynchronizer() : after pthread_xxx_destroy()" << ::std::endl;
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
    wait(0);
}

bool CSynchronizer::wait(int msec)
{
	::std::cout << "CSynchronizer::wait() : before pthread_mutex_lock()" << ::std::endl;

    assert(msec >= 0);

    if (pthread_mutex_lock(&fMutex) != 0) {
        assert(false);
        return false;
    }

    bool result = true;
    if (msec <= 0) {
    	::std::cout << "CSynchronizer::wait() : before pthread_cond_wait()" << ::std::endl;
        if (pthread_cond_wait(&fCond, &fMutex) != 0) {
            assert(false);
            return false;
        }
    	::std::cout << "CSynchronizer::wait() : after pthread_cond_wait()" << ::std::endl;
    } else {
    	assert(false);
/*
        struct timeval now;
        gettimeofday(&now, 0);

        struct timespec timeout;
        timeout.tv_sec = now.tv_sec + (msec / 1000);

        unsigned long usec = (msec % 1000) * 1000 + now.tv_usec;
        timeout.tv_sec += ( usec / 1000000 );  // carry over
        usec = usec % 1000000;

        timeout.tv_nsec = usec * 1000;  // micro-sec * 1000 = nano-sec

        int retcode = pthread_cond_timedwait(&fCond, &fMutex, &timeout);
        if (retcode == ETIMEDOUT) {
            result = false;
        } else if ( retcode < 0) {
            pthread_mutex_unlock(&fMutex);
            assert(false);
            return false;
        }
*/
    }

    if (pthread_mutex_unlock(&fMutex) != 0) {
        assert(false);
        return false;
    }
    
	::std::cout << "CSynchronizer::wait() : after pthread_mutex_unlock()" << ::std::endl;

    return result;
}

void CSynchronizer::notifyAll()
{
	::std::cout << "CSynchronizer::notifyAll() : before pthread_mutex_lock()" << ::std::endl;

    if (pthread_mutex_lock(&fMutex) != 0) {
        assert(false);
        return;
    }

	::std::cout << "CSynchronizer::notifyAll() : before pthread_cond_broadcast()" << ::std::endl;

    if ((pthread_cond_broadcast(&fCond)) != 0) {
        assert(false);
    }
    
	::std::cout << "CSynchronizer::notifyAll() : after pthread_cond_broadcast()" << ::std::endl;

    if (pthread_mutex_unlock(&fMutex) != 0) {
        assert(false);
        return;
    }
}

