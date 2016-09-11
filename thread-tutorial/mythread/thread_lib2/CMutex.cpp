#include <stddef.h>
#include <errno.h>
#include <assert.h>
#include <iostream>

#include "CMutex.h"

// constructors & destructor
CMutex::CMutex()
{
	::std::cout << "CMutex::CMutex() : before init" << ::std::endl;
    if (pthread_mutex_init(&fMutex, NULL) != 0)  assert(false);
	::std::cout << "CMutex::CMutex() : after init" << ::std::endl;
}

CMutex::~CMutex()
{
	::std::cout << "CMutex::~CMutex() : before destroy" << ::std::endl;
    if (pthread_mutex_destroy(&fMutex) != 0)  assert(false);
	::std::cout << "CMutex::~CMutex() : after destroy" << ::std::endl;
}

// Gets a lock
void CMutex::lock()
{
    if (pthread_mutex_lock(&fMutex) != 0) {
        assert(false);
        return;
    }
}

// Releases a lock
void CMutex::unlock()
{
    if (pthread_mutex_unlock(&fMutex) != 0) {
        assert(false);
        return;
    }
}
