#include <assert.h>
#include <iostream>
#include "CMutexAuto.h"


// constructors & destructor
CMutexAuto::CMutexAuto(CMutex *mutex)
: fMutex(mutex)
{
    assert( fMutex != NULL );

    fMutex->lock();
}

CMutexAuto::~CMutexAuto()
{
    assert( fMutex != NULL );

    fMutex->unlock();
}
