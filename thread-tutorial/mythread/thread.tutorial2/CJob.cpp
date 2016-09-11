// File: CJob.cpp 

#include <iostream>
#include "CJob.h"

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

// CJob's method
void CJob::execute()
{
    ::std::cout << "CJob::execute() : before startScan()" << ::std::endl;

    fDummyIIT->startScan();
    
    ::std::cout << "CJob::execute() : after startScan()" << ::std::endl;

    waitForScanCompleted();
    
    ::std::cout << "CJob::execute() : after waitForScanCompleted()" << ::std::endl;
    
    // ... do IOT process etc.

}

// public member functions
// CDummyIIT::ICallbackReceiver's method
void CJob::onScanCompleted()
{
    ::std::cout << "CJob::onScanCompleted() : start" << ::std::endl;

    fIsScanCompleted = true;
    
    fSync->notifyAll();
    
    ::std::cout << "CJob::onScanCompleted() : end" << ::std::endl;
}

// private member functions
void CJob::waitForScanCompleted()
{
    ::std::cout << "CJob::waitForScanCompleted() : start" << ::std::endl;
    
    while (! fIsScanCompleted) {
	    fSync->wait();
    }

    ::std::cout << "CJob::waitForScanCompleted() : end" << ::std::endl;
}

