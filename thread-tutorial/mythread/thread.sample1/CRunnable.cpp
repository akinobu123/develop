#include <iostream>
#include "CRunnable.h"
#include "CMutexAuto.h"
#include <unistd.h>

// constructors & destructor
CRunnable::CRunnable(
    const char *id,
    CMutex *mutex)
: fIsTerminated(false)
, fID(id)
, fMutex(mutex)
, fThread(0)
{
    fThread = CThreadUseRunnable::createInstance(this, "");
}

CRunnable::~CRunnable()
{
    terminate();
    fThread->join();
    delete fThread;
}

// public member functions
CRunnable *CRunnable::createInstance(
    const char *id,
    CMutex *mutex)
{
    CRunnable *instance = new CRunnable(id, mutex);
    instance->start();
    return instance;
}

// IRunnable's method
void CRunnable::run()
{
    while (! isTerminated()) {
        print();
        usleep(3); // for context switch.
    }
}

// private member function
void CRunnable::start()
{
    fThread->start();
}

bool CRunnable::isTerminated()
{
    CMutexAuto mutexAuto(fMutex);

    ::std::cout << fID << " test flag" << ::std::endl;

    return fIsTerminated;
}

void CRunnable::print()
{
    CMutexAuto mutexAuto(fMutex);

    ::std::cout << ::std::endl;
    for (int i = 0; i < 10; i++) {
        ::std::cout << fID << " " << i << ::std::endl;
        usleep(3); // for context switch.
    }
}

void CRunnable::terminate()
{
    CMutexAuto mutexAuto(fMutex);

    ::std::cout << fID << " set flag" << ::std::endl;

	fIsTerminated = true;   
}

