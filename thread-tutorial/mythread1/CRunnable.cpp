// File: CRunnable.cpp      - last edit:
// Norihiko Tsuyuzaki    30-Jun-2015

// Copyright(C) 2015 by Fuji Xerox Co., Ltd. All rights reserved.

#include <iostream>
#include <unistd.h>
#include "CRunnable.h"
#include "CSynchronized.h"

// constructors & destructor
CRunnable::CRunnable( const char *id, CSynchronizer *sync )
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
CRunnable *CRunnable::createInstance( const char *id, CSynchronizer *sync )
{
    CRunnable *instance = new CRunnable(id, sync);
    instance->start();
    return instance;
}

// ::clib::IRunnable's method
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
    CSynchronized sync(fSync);
    
    return fIsTerminated;
}

void CRunnable::print()
{
    CSynchronized sync(fSync);
    
    ::std::cout << ::std::endl;
    for (int i = 0; i < 10; i++) {
        ::std::cout << fID << " " << i << ::std::endl;
        usleep(3); // for context switch.
    }
}

void CRunnable::terminate()
{
    CSynchronized sync(fSync);

    fIsTerminated = true;
}

