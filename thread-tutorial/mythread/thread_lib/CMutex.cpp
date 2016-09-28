#include <stddef.h>
#include <errno.h>
#include <assert.h>

#include "CMutex.h"

// constructors & destructor
CMutex::CMutex()
{
    fMutex = PTHREAD_MUTEX_INITIALIZER;
    pthread_mutex_init(&fMutex, NULL);
}

CMutex::~CMutex()
{
    pthread_mutex_destroy(&fMutex);
}

// Gets a lock
void CMutex::lock()
{
    int ret = 0;
    ret = pthread_mutex_lock(&fMutex);
    assert( ret == 0 );
}

// Releases a lock
void CMutex::unlock()
{
    int ret = 0;
    ret = pthread_mutex_unlock(&fMutex);
    assert( ret == 0 );
}
