#include <assert.h>
#include "CMutexAuto.h"
#include <iostream>


// constructors & destructor
CMutexAuto::CMutexAuto(CMutex *mutex)
: fMutex(mutex)
{
	assert( fMutex != NULL );
	
    fMutex->lock();

	::std::cout << "CMutexAuto::CMutexAuto() : locked" << ::std::endl;
}

CMutexAuto::~CMutexAuto()
{
	assert( fMutex != NULL );
	
    fMutex->unlock();

	::std::cout << "CMutexAuto::~CMutexAuto() : unlocked" << ::std::endl;
}
