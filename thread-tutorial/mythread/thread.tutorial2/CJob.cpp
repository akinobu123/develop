// File: CJob.cpp

#include <iostream>
#include "CJob.h"
#include "CSynchronized.h"

// constructors & destructor
CJob::CJob()
: fIsScanCompleted(false)
, fSync(0)
, fDummyIIT(0)
{
    fSync = CSynchronizer::createInstance();
    fDummyIIT = new CDummyIIT(this);
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

    ::std::cout << "CJob:wait end" << ::std::endl;
}

