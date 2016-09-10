// File: CSynchronized.cpp    - last edit:

// Copyright(C) 2015 by Fuji Xerox Co. Ltd. All rights reserved.

#include <assert.h>
#include "CSynchronized.h"


// constructors & destructor
CSynchronized::CSynchronized(CSynchronizer *sync)
: fSync(sync)
, fCounter(0)
{
    if (fSync != 0) {
        fSync->lock();
        ++fCounter;
    } else {
        assert(false);
    }
}

CSynchronized::~CSynchronized()
{
    if (fSync != 0) {
        for(int i = 0; i < fCounter; ++i) {
            fSync->unlock();
        }
    }
}

// public member functions
void CSynchronized::lock()
{
    if (fSync != 0) {
        fSync->lock();
        ++fCounter;
    }
}

void CSynchronized::unlock()
{
    if (fSync != 0) {
        assert(fCounter > 0);
        --fCounter;
        fSync->unlock();
    }
}

void CSynchronized::wait()
{
    if (fSync != 0) {
        fSync->wait();
    }
}

bool CSynchronized::wait(int msec)
{
    if (fSync != 0) {
        return fSync->wait(msec);
    }
    return false;
}

void CSynchronized::notifyAll()
{
    if (fSync != 0) {
        fSync->notifyAll();
    }
}
