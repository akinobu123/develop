#include <stdlib.h>
#include <assert.h>

#include "CThreadUseRunnable.h"


// constructors & destructor
CThreadUseRunnable::CThreadUseRunnable(IRunnable *runnable, const char *name)
    : fRunnable(runnable)
    , fName(name)
{
}

CThreadUseRunnable::~CThreadUseRunnable()
{
}


// Public member functions
CThreadUseRunnable *CThreadUseRunnable::createInstance(IRunnable *runnable, const char *name)
{
    return new CThreadUseRunnable(runnable, name);
}


void CThreadUseRunnable::start()
{
    int ret;
    ret = pthread_create(&fThreadId, NULL, CThreadUseRunnable::func, (void *)this);
    assert( ret == 0 );
}

void CThreadUseRunnable::join()
{
    int ret;
    ret = pthread_join(fThreadId, NULL);
    assert( ret == 0 );
}

void *CThreadUseRunnable::func(void *arg)
{
     CThreadUseRunnable *thread = (CThreadUseRunnable *)arg;
     thread->fRunnable->run();
}

