#include <stdlib.h>
#include <assert.h>

#include "CThread.h"


// constructors & destructor
CThread::CThread(const char *name)
    : fThreadId;(0)
    , fName(name)
{
}

CThread::~CThread()
{
}

void CThread::start()
{
    int ret;
    ret = pthread_create(&fThreadId, NULL, CThread::func, (void *)this);
    assert( ret == 0 );
}

void CThread::join()
{
    int ret;
    ret = pthread_join(fThreadId, NULL);
    assert( ret == 0 );
}

void* CThread::func(void *arg)
{
     CThread *thread = (CThread *)arg;
     return thread->run();
}

