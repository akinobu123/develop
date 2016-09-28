#include <stdlib.h>
#include <assert.h>

#include "CThread.h"


// constructors & destructor
CThread::CThread(IRunnable *runnable, const char *name)
: fRunnable(runnable)
, fName(name)
{

}


CThread::~CThread()
{
    // Nothing to do.
}


// Public member functions
CThread *CThread::createInstance(IRunnable *runnable, const char *name)
{
    return new CThread(runnable, name);
}


void CThread::start()
{
    int ret;
    ret = pthread_create(&fThreadId, NULL, CThread::func, (void *)this);
    assert(ret == 0);
}


void CThread::join()
{
    int ret;
    ret = pthread_join(fThreadId, NULL);
    assert(ret == 0);
}


void *CThread::func(void *arg)
{
     CThread *thread = (CThread *)arg;

     thread->fRunnable->run();
}

