// File: CMain.cpp 

#include <iostream>
#include "CMain.h"

// constructors & destructor
CMain::CMain()
 : fIsProcCompleted(false)
 , fCondVal(0)
 , fSub(0)
{
    fCondVal = CCondVal::createInstance();
    fSub = new CSub(this);
}

CMain::~CMain()
{
    delete fSub;
    delete fCondVal;
}

// CMain's method
void CMain::execute()
{
    ::std::cout << "CMain::execute() : before startProc()" << ::std::endl;

    fSub->startProc();
    
    ::std::cout << "CMain::execute() : after startProc()" << ::std::endl;

    waitForProcCompleted();
    
    ::std::cout << "CMain::execute() : after waitForProcCompleted()" << ::std::endl;
    
    // ... do Main process etc.

}

// public member functions
// CSub::ICallbackReceiver's method
void CMain::onProcCompleted()
{
    ::std::cout << "CMain::onProcCompleted() : start" << ::std::endl;

    fIsProcCompleted = true;
    
    fCondVal->notifyAll();
    
    ::std::cout << "CMain::onProcCompleted() : end" << ::std::endl;
}

// private member functions
void CMain::waitForProcCompleted()
{
    ::std::cout << "CMain::waitForProcCompleted() : start" << ::std::endl;
    
    while (! fIsProcCompleted) {
	    fCondVal->wait();
    }

    ::std::cout << "CMain::waitForProcCompleted() : end" << ::std::endl;
}

