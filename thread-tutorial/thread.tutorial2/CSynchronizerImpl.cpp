// File: CSynchronizerImpl.cpp    - last edit:

// Copyright(C) 2000 - 2007 by Fuji Xerox Co. Ltd. All rights reserved.

#include <stddef.h>
#include <errno.h>
#include <sys/time.h>
#include <assert.h>

#include "CSynchronizerImpl.h"

using namespace ::clib;

// constructors & destructor
CSynchronizerImpl::CSynchronizerImpl()
: fState(eUnlocked)
, fLockedLevel(0)
{
    int result;

    if ((result = pthread_mutex_init(&fLock, NULL)) != 0) {
        setState(eInvalid);
        setErrorNumber(result);
        assert(false);
    }

    if ((result = pthread_cond_init(&fReleased, NULL)) != 0) {
        setState(eInvalid);
        setErrorNumber(result);
        assert(false);
    }

    if ((result = pthread_cond_init(&fNotified, NULL)) != 0) {
        setState(eInvalid);
        setErrorNumber(result);
        assert(false);
    }
}

CSynchronizerImpl::~CSynchronizerImpl()
{
    assert(getState() != eLocked);
    setState(eInvalid);

    bool result = (pthread_mutex_destroy(&fLock) == 0);
    assert(result);

    result = (pthread_cond_destroy(&fReleased) == 0);
    assert(result);

    result = (pthread_cond_destroy(&fNotified) == 0);
    assert(result);
}

// public member functions
CSynchronizerImpl* CSynchronizerImpl::createInstance()
{
    return new CSynchronizerImpl();
}

// Gets a lock
void CSynchronizerImpl::lock()
{
    if (pthread_mutex_lock(&fLock) != 0) {
        assert(false);
        return;
    }

    if (getState() != eLocked) {
        setState(eLocked);
        setThreadID(pthread_self());
    } else if (!pthread_equal(getThreadID(), pthread_self())) {
        while (getState() == eLocked) {
            pthread_cond_wait(&fReleased, &fLock);
        }

        setState(eLocked);
        setThreadID(pthread_self());
    } else {
        // Recursive call.  Just increment the locked level.
    }


    incrementLockedLevel();

    if (pthread_mutex_unlock(&fLock) != 0) {
        assert(false);
        return ;
    }
}

// Releases a lock
void CSynchronizerImpl::unlock()
{
    bool released = false;

    if (pthread_mutex_lock(&fLock) != 0) {
        assert(false);
        return;
    }

    if (! isLockedBySelf()) {
        pthread_mutex_unlock(&fLock);
        assert(false);
        return;
    }

    decrementLockedLevel();

    if (getLockedLevel() == 0) {
        setState(eUnlocked);
        released = true;
    }

    if (released) {
        if (pthread_cond_signal(&fReleased) != 0) {
            assert(false);
            return;
        }
    }

    if (pthread_mutex_unlock(&fLock) != 0) {
        assert(false);
        return;
    }
}

// Release a lock, then waits until either some other thread invokes the notify
// method or the notifyAll method
void CSynchronizerImpl::wait()
{
    wait(0);
}

bool CSynchronizerImpl::wait(
    int msec)
{
    assert(msec >= 0);

    if (pthread_mutex_lock(&fLock) != 0) {
        assert(false);
        return false;
    }

    if (! isLockedBySelf()) {
        pthread_mutex_unlock(&fLock);
        assert(false);
        return false;
    }

    saveThreadLockedInfo();

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

    while (getState() == eLocked) {
        pthread_cond_wait(&fReleased, &fLock);
    }

    restoreThreadLockedInfo();

    if (pthread_mutex_unlock(&fLock) != 0) {
        assert(false);
        return false;
    }

    return result;
}


void CSynchronizerImpl::notify()
{
    if (pthread_mutex_lock(&fLock) != 0) {
        assert(false);
        return;
    }

    if (! isLockedBySelf()) {
        pthread_mutex_unlock(&fLock);
        assert(false);
        return;
    }

    if ((pthread_cond_signal(&fNotified)) != 0) {
        assert(false);
    }

    if (pthread_mutex_unlock(&fLock) != 0) {
        assert(false);
        return;
    }
}

void CSynchronizerImpl::notifyAll()
{
    if (pthread_mutex_lock(&fLock) != 0) {
        assert(false);
        return;
    }

    if (! isLockedBySelf()) {
        pthread_mutex_unlock(&fLock);
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

// private member functions
void CSynchronizerImpl::setState(
    EState state)
{
    assert(fState == eUnlocked || fState == eLocked);
    fState = state;
}



CSynchronizerImpl::EState CSynchronizerImpl::getState()
{
    assert(fState == eUnlocked || fState == eLocked);
    return fState;
}

bool CSynchronizerImpl::isLockedBySelf()
{
    if ((getState() == eLocked) &&
            pthread_equal(getThreadID(), pthread_self())) {
        return true;
    }

    return false;
}

void CSynchronizerImpl::saveThreadLockedInfo()
{
    assert(isLockedBySelf());

    putThreadLockedLevel(pthread_self(), getLockedLevel());
    setLockedLevel(0);
    setState(eUnlocked);

    if (pthread_cond_signal(&fReleased) != 0) {
        assert(false);
        return;
    }
}

void CSynchronizerImpl::restoreThreadLockedInfo()
{
    assert(getState() == eUnlocked);

    setLockedLevel(getThreadLockedLevel(pthread_self()));
    removeThreadLockedLevel(pthread_self());
    setThreadID(pthread_self());
    setState(eLocked);
}

void CSynchronizerImpl::putThreadLockedLevel(
    pthread_t threadID, 
    int level)
{
    if (level == 1) {
        return;
    }

    for (int i = 0; i < kThreadListSize; ++i) {
        if (fThreadList[i].fEmpty) {
            fThreadList[i].fThreadID = threadID;
            fThreadList[i].fLockedLevel = level;
            fThreadList[i].fEmpty = false;
            return;
        }
    }
    assert(false);
}

int CSynchronizerImpl::getThreadLockedLevel(
    pthread_t threadID)
{

    for (int i = 0; i < kThreadListSize; ++i) {
        if (fThreadList[i].fEmpty == false &&
                pthread_equal(fThreadList[i].fThreadID, threadID)) {
            return fThreadList[i].fLockedLevel;
        }
    }

    return 1;     // if ThreadID not found, return 1.
}


void CSynchronizerImpl::removeThreadLockedLevel(
    pthread_t threadID)
{
    assert(threadID >= 0);

    for (int i = 0; i < kThreadListSize; ++i) {
        if (fThreadList[i].fEmpty == false &&
                pthread_equal(fThreadList[i].fThreadID, threadID)) {
            fThreadList[i].fLockedLevel = 0;
            fThreadList[i].fEmpty = true;
            return ;
        }
    }
}


void CSynchronizerImpl::setLockedLevel(
    int level)
{
    assert(level >= 0);
    fLockedLevel = level;
}

void CSynchronizerImpl::incrementLockedLevel()
{
    assert(fLockedLevel >= 0);
    ++fLockedLevel;
}

void CSynchronizerImpl::decrementLockedLevel()
{
    assert(fLockedLevel > 0);
    --fLockedLevel;
}

