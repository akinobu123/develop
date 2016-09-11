// File: CJob.cpp 

#include <iostream>
#include "CJob.h"
#include "CJobStat.h"
#include "CSynchronized.h"

// constructors & destructor
CJob::CJob()
: fIsScanCompleted(false)
, fSync(0)
, fDummyIIT(0)
{
    fSync = CSynchronizer::createInstance();
    fDummyIIT = new CDummyIIT(this, fSync);
}

CJob::~CJob()
{
    delete fDummyIIT;
    delete fSync;
}

// public member functions
// CDummyIIT::ICallbackReceiver's method
void CJob::onScanCompleted()
{
    // implement here.
    CSynchronized sync(fSync);
    fIsScanCompleted = true;
    sync.notifyAll();
}

// CJob's method
void CJob::execute()
{
    ::std::cout << "CJob:execute requested" << ::std::endl;

    fDummyIIT->startScan();
    
    ::std::cout << "CJob:scan requested" << ::std::endl;

    waitForScanCompleted();
    
    ::std::cout << "CJob:scan completed" << ::std::endl;
    
    // ... do IOT process etc.

}

// private member functions
void CJob::waitForScanCompleted()
{
    ::std::cout << "CJob:wait start" << ::std::endl;

    // implement here.
    CSynchronized sync(fSync);
    while (! fIsScanCompleted) {

            ::std::cout << "CJob:wait on-loop (before wait)" << ::std::endl;

	    sync.wait();

            ::std::cout << "CJob:wait on-loop (after wait)" << ::std::endl;
    }

    ::std::cout << "CJob:wait end" << ::std::endl;
}

