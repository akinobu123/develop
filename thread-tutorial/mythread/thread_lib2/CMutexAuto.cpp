#include <assert.h>
#include "CMutexAuto.h"
#include <iostream>


// constructors & destructor
CMutexAuto::CMutexAuto(CMutex *mutex)
: fMutex(mutex)
{
    if (fMutex != 0) {
        fMutex->lock();
    } else {
        assert(false);
    }
	::std::cout << "CMutexAuto::CMutexAuto() : locked" << ::std::endl;
}

CMutexAuto::~CMutexAuto()
{
    if (fMutex != 0) {
        fMutex->unlock();
    }
	::std::cout << "CMutexAuto::~CMutexAuto() : unlocked" << ::std::endl;
}
