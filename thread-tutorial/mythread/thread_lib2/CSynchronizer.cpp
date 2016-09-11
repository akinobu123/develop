#include <stddef.h>
#include <errno.h>
#include <sys/time.h>
#include <assert.h>

#include "CSynchronizer.h"

// constructors & destructor
CSynchronizer::CSynchronizer()
{
    if (pthread_mutex_init(&fLock, NULL) != 0)  assert(false);
    if (pthread_mutex_init(&fLockForWait, NULL) != 0)  assert(false);
    if (pthread_mutex_init(&fLockForNotify, NULL) != 0)  assert(false);
    if (pthread_cond_init(&fWait, NULL) != 0)  assert(false);
}

CSynchronizer::~CSynchronizer()
{
    if (pthread_mutex_destroy(&fLock) != 0)  assert(false);
    if (pthread_mutex_destroy(&fLockForWait) != 0)  assert(false);
    if (pthread_mutex_destroy(&fLockForNotify) != 0)  assert(false);
    if (pthread_cond_destroy(&fWait) != 0)  assert(false);
}

// public member functions
CSynchronizer* CSynchronizer::createInstance()
{
    return new CSynchronizer();
}

// Gets a lock
void CSynchronizer::lock()
{
    if (pthread_mutex_lock(&fLock) != 0) {
        assert(false);
        return;
    }
}

// Releases a lock
void CSynchronizer::unlock()
{
    if (pthread_mutex_unlock(&fLock) != 0) {
        assert(false);
        return;
    }
}

// Release a lock, then waits until either some other thread invokes the notify
// method or the notifyAll method
void CSynchronizer::wait()
{
    wait(0);
}

bool CSynchronizer::wait(int msec)
{
    assert(msec >= 0);

    if (pthread_mutex_lock(&fLockForWait) != 0) {
//    if (pthread_mutex_lock(&fLock) != 0) {
        assert(false);
        return false;
    }

    bool result = true;
    if (msec <= 0) {
    	::std::cout << "CSynchronizer::wait() : before pthread_cond_wait()" << ::std::endl;
        if (pthread_cond_wait(&fWait, &fLockForWait) != 0) {
//        if (pthread_cond_wait(&fWait, &fLock) != 0) {
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

        int retcode = pthread_cond_timedwait(&fWait, &fLockForWait, &timeout);
        if (retcode == ETIMEDOUT) {
            result = false;
        } else if ( retcode < 0) {
            pthread_mutex_unlock(&fLockForWait);
            assert(false);
            return false;
        }
*/
    }

    if (pthread_mutex_unlock(&fLockForWait) != 0) {
//    if (pthread_mutex_unlock(&fLock) != 0) {
        assert(false);
        return false;
    }

    return result;
}

void CSynchronizer::notifyAll()
{
    if (pthread_mutex_lock(&fLockForNotify) != 0) {
        assert(false);
        return;
    }

	::std::cout << "CSynchronizer::notifyAll() : before pthread_cond_broadcast()" << ::std::endl;
    if ((pthread_cond_broadcast(&fWait)) != 0) {
        assert(false);
    }
	::std::cout << "CSynchronizer::notifyAll() : after pthread_cond_broadcast()" << ::std::endl;

    if (pthread_mutex_unlock(&fLockForNotify) != 0) {
        assert(false);
        return;
    }
}

