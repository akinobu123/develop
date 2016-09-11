// File: CSynchronized.cpp    - last edit:

#include <assert.h>
#include "CSynchronized.h"
#include <iostream>


// constructors & destructor
CSynchronized::CSynchronized(CSynchronizer *sync)
: fSync(sync)
//, fCounter(0)
{
	::std::cout << "CSynchronized::construct() : before lock" << ::std::endl;
    if (fSync != 0) {
        fSync->lock();
//        ++fCounter;
    } else {
        assert(false);
    }
//    ::std::cout << "CSynchronized::construct() : lock : counter=" << fCounter << ::std::endl;
	::std::cout << "CSynchronized::construct() : after lock" << ::std::endl;
}

CSynchronized::~CSynchronized()
{
	::std::cout << "CSynchronized::destruct() : before unlock " << ::std::endl;
    if (fSync != 0) {
//        for(int i = 0; i < fCounter; ++i) {
            fSync->unlock();
//    }
    }
//    ::std::cout << "CSynchronized::destruct() : unlock " << i << ::std::endl;
	::std::cout << "CSynchronized::destruct() : after unlock " << ::std::endl;
}

// public member functions
void CSynchronized::lock()
{
//    ::std::cout << "CSynchronized::lock() : counter=" << fCounter << ::std::endl;
	::std::cout << "CSynchronized::lock() : before lock" << ::std::endl;
    if (fSync != 0) {
        fSync->lock();
//        ++fCounter;
    }
	::std::cout << "CSynchronized::lock() : after lock" << ::std::endl;
}

void CSynchronized::unlock()
{
	::std::cout << "CSynchronized::unlock() : before unlock" << ::std::endl;
    if (fSync != 0) {
//        assert(fCounter > 0);
//        --fCounter;
        fSync->unlock();
    }
//    ::std::cout << "CSynchronized::unlock() : counter=" << fCounter << ::std::endl;
	::std::cout << "CSynchronized::unlock() : after unlock" << ::std::endl;
}

void CSynchronized::wait()
{
	::std::cout << "CSynchronized::wait() : before wait" << ::std::endl;
    if (fSync != 0) {
        fSync->wait();
    }
	::std::cout << "CSynchronized::wait() : after wait" << ::std::endl;
}

/*
bool CSynchronized::wait(int msec)
{
    if (fSync != 0) {
        return fSync->wait(msec);
    }
    return false;
}
*/

void CSynchronized::notifyAll()
{
	::std::cout << "CSynchronized::notifyAll() : before notifyAll" << ::std::endl;
    if (fSync != 0) {
        fSync->notifyAll();
    }
	::std::cout << "CSynchronized::notifyAll() : after notifyAll" << ::std::endl;
}
