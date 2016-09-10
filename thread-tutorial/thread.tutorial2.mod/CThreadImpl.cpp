// File: CThreadImpl.cpp    - last edit:

// Copyright(C) 2015 by Fuji Xerox Co. Ltd. All rights reserved.

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include "CThreadImpl.h"
#include "CSynchronized.h"
#include "CThreadProxy.h"

using namespace ::clib;

// constructors & destructor
CThreadImpl::CThreadImpl(
    IRunnable *runnable, 
    const char *name, 
    size_t stackSize,
    CThreadProxy *proxy)
: fState(eInitialized)
, fRunnable(runnable)
, fName(name)
, fPriority(kDefaultPriority)
, fProxy(proxy)
{
    size_t minimumStackSize = (size_t)sysconf(_SC_THREAD_STACK_MIN);

    if (stackSize == 0) {
        fStackSize = kDefaultStackSize;
    } else if (stackSize < minimumStackSize) {
        fStackSize = minimumStackSize;
    } else {
        fStackSize = stackSize;
    }
}

CThreadImpl::~CThreadImpl()
{
    // Nothing to do.
}

// public member functions
CThreadImpl *CThreadImpl::createInstance(
    IRunnable *runnable,
    const char *name,
    size_t stackSize,
    CThreadProxy *proxy)
{
    assert(runnable != 0);

    return new CThreadImpl(
        runnable, 
        name, 
        stackSize,
        proxy);
}

// Creates a thread, then IRunnable object's run method is called
bool CThreadImpl::start(
    bool detach)
{
    assert(getState() == eInitialized);

    pthread_attr_t threadAttribute;

    if (getState() != eInitialized) {
        assert(false);
        return false;
    }

    if (pthread_attr_init(&threadAttribute) != 0) {
        assert(false);
        return false;
    }

    if (pthread_attr_setstacksize(&threadAttribute, fStackSize) != 0) {
        pthread_attr_destroy(&threadAttribute);
        assert(false);
        return false;
    }

    int result;
    result = pthread_attr_setschedpolicy(&threadAttribute, kSchedulingPolicy);
    if (result != 0) {
        if (result == ENOTSUP) {
            // clib_warning("The scheduling policy is not supoorted. Ignored.");
        } else {
            pthread_attr_destroy(&threadAttribute);
            assert(false);
            return false;
        }
    }

    if (detach) {
        if (pthread_attr_setdetachstate(&threadAttribute,
                                        PTHREAD_CREATE_DETACHED) != 0) {
            pthread_attr_destroy(&threadAttribute);
            assert(false);
            return false;
        }
        fProxy = 0;
        setState(eDetached);
    } else {
        if (pthread_attr_setdetachstate(&threadAttribute,
                                        PTHREAD_CREATE_JOINABLE) != 0) {
            pthread_attr_destroy(&threadAttribute);
            assert(false);
            return false;
        }
        setState(eBeingSpawn);
    }

    result = pthread_create(&fThreadID, &threadAttribute,
                            CThreadImpl::taskFunction, (void *)this);
    if (result != 0) {
        pthread_attr_destroy(&threadAttribute);
        // clib_warning("pthread_create error. fPriority= %d, errno = %d (%s)", fPriority, result, strerror(result));
        assert(false);
        return false;
    }

    if (pthread_attr_destroy(&threadAttribute) != 0) {
        assert(false);
    }

    return true;
}

void CThreadImpl::join()
{
    assert(getState() == eBeingSpawn);
    bool result = (pthread_join(fThreadID, NULL) == 0);
    assert(result && "pthread_join error");

    setState(eJoined);
}

void CThreadImpl::setPriority(
    int priority)
{
    assert(getState() == eInitialized);
    fPriority = priority;
}

int CThreadImpl::getSelfID()
{
    return (int)pthread_self();
}

// private member functions
void *CThreadImpl::taskFunction(void *arg)
{
    CThreadImpl *impl = (CThreadImpl *)arg;

    impl->fRunnable->run();

    if (impl->getState() == eDetached) {
        delete impl;
        return 0;
    }

    if (impl->fProxy) {
        impl->fProxy->setTerminateState();
    }

    return 0;
}

