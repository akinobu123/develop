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
	::std::cout << "CMutex::~CMutex() : before init" << ::std::endl;
    if (pthread_mutex_destroy(&fMutex) != 0)  assert(false);
	::std::cout << "CMutex::~CMutex() : after init" << ::std::endl;
}

// public member functions
CMutex* CMutex::createInstance()
{
	::std::cout << "CMutex::createInstance() : before new" << ::std::endl;
    return new CMutex();
	::std::cout << "CMutex::createInstance() : after new" << ::std::endl;
}

// Gets a lock
void CMutex::lock()
{
	::std::cout << "CMutex::lock() : before pthread_mutex_lock" << ::std::endl;
    if (pthread_mutex_lock(&fMutex) != 0) {
        assert(false);
        return;
    }
	::std::cout << "CMutex::lock() : after pthread_mutex_lock" << ::std::endl;
}

// Releases a lock
void CMutex::unlock()
{
	::std::cout << "CMutex::unlock() : before pthread_mutex_unlock" << ::std::endl;
    if (pthread_mutex_unlock(&fMutex) != 0) {
        assert(false);
        return;
    }
	::std::cout << "CMutex::unlock() : after pthread_mutex_unlock" << ::std::endl;
}
