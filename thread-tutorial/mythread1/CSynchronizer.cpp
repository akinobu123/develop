#include <stddef.h>
#include <errno.h>
#include <sys/time.h>
#include <assert.h>

#include "CSynchronizer.h"

// constructors & destructor
CSynchronizer::CSynchronizer()
{
    if (pthread_mutex_init(&fLock, NULL) != 0) {
        assert(false);
    }

    if (pthread_cond_init(&fNotified, NULL) != 0) {
        assert(false);
    }
}

CSynchronizer::~CSynchronizer()
{
    if (pthread_mutex_destroy(&fLock) != 0) {
        assert(false);
    }

    if (pthread_cond_destroy(&fNotified) != 0) {
        assert(false);
    }
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

    if (pthread_mutex_lock(&fLock) != 0) {
        assert(false);
        return false;
    }

    bool result = true;
    if (msec <= 0) {
        if (pthread_cond_wait(&fNotified, &fLock) != 0) {
            assert(false);
            return false;
        }
    } else {
        struct timeval now;
        gettimeofday(&now, 0);

        struct timespec timeout;
        timeout.tv_sec = now.tv_sec + (msec / 1000);

        unsigned long usec = (msec % 1000) * 1000 + now.tv_usec;
        timeout.tv_sec += ( usec / 1000000 );  // carry over
        usec = usec % 1000000;

        timeout.tv_nsec = usec * 1000;  // micro-sec * 1000 = nano-sec

        int retcode = pthread_cond_timedwait(&fNotified, &fLock, &timeout);
        if (retcode == ETIMEDOUT) {
            result = false;
        } else if ( retcode < 0) {
            pthread_mutex_unlock(&fLock);
            assert(false);
            return false;
        }
    }

    if (pthread_mutex_unlock(&fLock) != 0) {
        assert(false);
        return false;
    }

    return result;
}

void CSynchronizer::notifyAll()
{
    if (pthread_mutex_lock(&fLock) != 0) {
        assert(false);
        return;
    }

    if ((pthread_cond_broadcast(&fNotified)) != 0) {
        assert(false);
    }

    if (pthread_mutex_unlock(&fLock) != 0) {
        assert(false);
        return;
    }
}

