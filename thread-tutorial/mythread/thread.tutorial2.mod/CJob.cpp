// File: CJob.cpp 

#include <iostream>
#include "CJob.h"
#include "CMutexAuto.h"

// constructors & destructor
CJob::CJob()
: fIsScanCompleted(false)
, fMutex(0)
, fSync(0)
, fDummyIIT(0)
{
    fMutex = new CMutex();
    fSync = CSynchronizer::createInstance();
    fDummyIIT = new CDummyIIT(this);
}

CJob::~CJob()
{
    delete fDummyIIT;
    delete fSync;
    delete fMutex;
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
    // implement here.
//    ::std::cout << "CJob::onScanCompleted() : before mutexAuto" << ::std::endl;
//    CMutexAuto mutexAuto(fMutex);
//    ::std::cout << "CJob::onScanCompleted() : after mutexAuto" << ::std::endl;
	CMutex mutex;
	mutex.lock();
    fIsScanCompleted = true;
    mutex.unlock();
    
    ::std::cout << "CJob::onScanCompleted() : complete flag setted" << ::std::endl;
    fSync->notifyAll();
    ::std::cout << "CJob::onScanCompleted() : after notifyAll" << ::std::endl;
}

// private member functions
void CJob::waitForScanCompleted()
{
    ::std::cout << "CJob::waitForScanCompleted() : start" << ::std::endl;

    // implement here.
//    CMutexAuto mutexAuto(fMutex);
    
    while (! fIsScanCompleted) {

        ::std::cout << "CJob::waitForScanCompleted() : on-loop (before wait)" << ::std::endl;

	    fSync->wait();

        ::std::cout << "CJob::waitForScanCompleted() : on-loop (after wait)" << ::std::endl;
    }

    ::std::cout << "CJob::waitForScanCompleted() : end" << ::std::endl;
}

