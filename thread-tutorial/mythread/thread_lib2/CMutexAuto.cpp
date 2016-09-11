#include <assert.h>
#include "CMutexAuto.h"
#include <iostream>


// constructors & destructor
CMutexAuto::CMutexAuto(CMutex *mutex)
: fMutex(mutex)
{
	::std::cout << "CMutexAuto::CMutexAuto() : before lock" << ::std::endl;
    if (fMutex != 0) {
        fMutex->lock();
    } else {
        assert(false);
    }
	::std::cout << "CMutexAuto::CMutexAuto() : after lock" << ::std::endl;
}

CMutexAuto::~CMutexAuto()
{
	::std::cout << "CMutexAuto::~CMutexAuto() : before unlock " << ::std::endl;
    if (fMutex != 0) {
        fMutex->unlock();
    }
	::std::cout << "CMutexAuto::~CMutexAuto() : after unlock " << ::std::endl;
}
