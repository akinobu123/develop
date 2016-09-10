// File: CThread.cpp    - last edit:

// Copyright(C) 2015 by Fuji Xerox Co. Ltd. All rights reserved.

// public member functions

#include <stdlib.h>
#include <assert.h>

#include "CThread.h"
#include "CThreadProxy.h"

using namespace ::clib;

CThread::~CThread()
{
    // Nothing to do.
}

// Public member functions
CThread *CThread::createInstance(
    IRunnable *runnable,
    const char *name,
    EClassVersion version)
{
    assert(version == kClassVersion);
    return CThreadProxy::createInstance(runnable, name, 0);
}

CThread *CThread::createInstance(
    IRunnable *runnable,
    const char *name,
    size_t stackSize,
    EClassVersion version)
{
    assert(version == kClassVersion);
    return CThreadProxy::createInstance(runnable, name, stackSize);
}

int CThread::getMaxPriority()
{
    return CThreadProxy::getMaxPriority();
}

int CThread::getMinPriority()
{
    return CThreadProxy::getMinPriority();
}

int CThread::getSelfID()
{
    return CThreadProxy::getSelfID();
}

