#include <iostream>
#include "CRunnable.h"
#include "CSynchronized.h"
#include <unistd.h>

// constructors & destructor
CRunnable::CRunnable(
    const char *id,
    CSynchronizer *sync)
: fIsTerminated(false)
, fID(id)
, fSync(sync)
, fThread(0)
{
    fThread = CThread::createInstance(this, "");
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
    CSynchronizer *sync)
{
    CRunnable *instance = new CRunnable(id, sync);
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
    // step1 implement here.
    // call fThread's start().
    fThread->start();
}

bool CRunnable::isTerminated()
{
    // step2 implement here.
    // use fSync and return fIsTerminated.
    return fIsTerminated;
}

void CRunnable::print()
{
    // step4 implement here.
    // use fSync.
    CSynchronized sync(fSync);
    ::std::cout << ::std::endl;
    for (int i = 0; i < 10; i++) {
        ::std::cout << fID << " " << i << ::std::endl;
        usleep(3); // for context switch.
    }
}

void CRunnable::terminate()
{
    // step2 implement here.
    // use fSync and set fIsTerminated true.
    CSynchronized sync(fSync);
	fIsTerminated = true;   
}

