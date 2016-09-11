// File: CSynchronized.cpp    - last edit:

#include <iostream>
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
    	::std::cout << "CSynchronized::construct() : lock : counter=" << fCounter << ::std::endl;
    } else {
        assert(false);
    }
}

CSynchronized::~CSynchronized()
{
    if (fSync != 0) {
        for(int i = 0; i < fCounter; ++i) {
        	::std::cout << "CSynchronized::destruct() : unlock " << i << ::std::endl;
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
    	::std::cout << "CSynchronized::lock() : counter=" << fCounter << ::std::endl;
    }
}

void CSynchronized::unlock()
{
    if (fSync != 0) {
        assert(fCounter > 0);
        --fCounter;
        fSync->unlock();
    	::std::cout << "CSynchronized::unlock() : counter=" << fCounter << ::std::endl;
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
