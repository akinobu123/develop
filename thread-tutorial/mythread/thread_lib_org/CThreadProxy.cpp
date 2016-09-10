// File: CThreadProxy.cpp    - last edit:

// Copyright(C) 2015 by Fuji Xerox Co. Ltd. All rights reserved.

#include <assert.h>
#include "CThreadProxy.h"
#include "CSynchronized.h"

using namespace ::clib;

// constructors & destructor
CThreadProxy::CThreadProxy(
    IRunnable *runnable,
    const char *name,
    size_t stackSize)
: fThreadState(eCreated)
, fThreadImpl(0)
, fSync(0)
{
    fThreadImpl = CThreadImpl::createInstance(
        runnable, 
        name, 
        stackSize, 
        this);
    assert(fThreadImpl != 0);

    fSync = CSynchronizer::createInstance();
    assert(fSync != 0);
}

CThreadProxy::~CThreadProxy()
{
    fSync->lock();

    if (fThreadState == eStarted) {
        assert(false);
        fSync->unlock();
        return;
    }

    fSync->unlock();
    delete fSync;
    delete fThreadImpl;
}

// public member functions
CThreadProxy *CThreadProxy::createInstance(
    IRunnable *runnable,
    const char *name,
    size_t stackSize)
{
    if (runnable == 0) {
        assert(false);
        return 0;
    }

    CThreadProxy *proxy = new CThreadProxy(
        runnable, 
        name, 
        stackSize);

    if (proxy->hasErrorOccurred()) {
        assert(false);
        delete proxy;
        return 0;
    }

    return proxy;
}

void CThreadProxy::start(
    bool detach)
{
    CSynchronized sync(fSync);

    if (fThreadState != eCreated) {
        assert(false);
        return;
    }

    bool result = fThreadImpl->start(detach);
    if (result) {
        if (detach) {
            fThreadImpl = 0;
            fThreadState = eDetached;
        } else {
            fThreadState = eStarted;
        }
    } else {
        assert(false);
    }
}

void CThreadProxy::join()
{
    CSynchronized sync(fSync);

    if (fThreadState == eCreated ||
            fThreadState == eDetached) {
        assert(false);
        return;
    }
    while (! (fThreadState == eTerminated ||
            fThreadState == eJoined) ) {
        sync.wait();
    }

    if (fThreadState == eJoined) {
        return;
    }

    fThreadImpl->join();
    fThreadState = eJoined;
}

void CThreadProxy::setPriority(
    int priority)
{
    CSynchronized sync(fSync);

    if (fThreadState != eCreated) {
        assert(false);
        return;
    }

    int lowestValue;
    int highestValue;

    if (getMaxPriority() > getMinPriority()) {
        highestValue = getMaxPriority();
        lowestValue = getMinPriority();
    } else {
        highestValue = getMinPriority();
        lowestValue = getMaxPriority();
    }

    if (priority < lowestValue) {
        priority = lowestValue;
    } else if (priority > highestValue) {
        priority = highestValue;
    }

    fThreadImpl->setPriority(priority);
}

int CThreadProxy::getPriority()
{
    CSynchronized sync(fSync);

    if (fThreadState == eDetached) {
        assert(false);
        return 0;
    }
    return fThreadImpl->getPriority();
}

const char *CThreadProxy::getName()
{
    CSynchronized sync(fSync);

    if (fThreadState == eDetached) {
        assert(false);
        return 0;
    }
    return fThreadImpl->getName();
}

int CThreadProxy::getMaxPriority()
{
    return CThreadImpl::getMaxPriority();
}

int CThreadProxy::getMinPriority()
{
    return CThreadImpl::getMinPriority();
}

int CThreadProxy::getSelfID()
{
    return (CThreadImpl::getSelfID());
}

void CThreadProxy::setTerminateState()
{
    CSynchronized sync(fSync);
    fThreadState = eTerminated;
    sync.notifyAll();
}

// private member functions

bool CThreadProxy::hasErrorOccurred()
{
    if (fThreadState == eCreated) {
        if ((fThreadImpl == 0) || (fSync == 0)) {
            return true;
        }
    }

    return false;
}
