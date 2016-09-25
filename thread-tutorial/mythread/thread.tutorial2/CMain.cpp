// File: CMain.cpp 

#include <iostream>
#include "CMain.h"

// constructors & destructor
CMain::CMain()
 : fIsProcCompleted(false)
 , fSync(0)
 , fSub(0)
{
	fSync = CSynchronizer::createInstance();
	fSub = new CSub(this);
}

CMain::~CMain()
{
	delete fSub;
	delete fSync;
}

// CMain's method
void CMain::execute()
{
	::std::cout << "CMain::execute() : before startProc()" << ::std::endl;

	fSub->startProc();

	::std::cout << "CMain::execute() : after startProc()" << ::std::endl;

	// ... do some Main-process on parallel with sub-process.

	waitForProcCompleted();

	::std::cout << "CMain::execute() : after waitForProcCompleted()" << ::std::endl;

	// ... do Main-process remaining after waiting for sub-process.

}

// public member functions
// CSub::ICallbackReceiver's method
void CMain::onProcCompleted()
{
	fSync->lockForSync();
	::std::cout << "CMain::onProcCompleted() : start" << ::std::endl;

	fIsProcCompleted = true;

	fSync->notifyAll();

	::std::cout << "CMain::onProcCompleted() : end" << ::std::endl;
	fSync->unlockForSync();
}

// private member functions
void CMain::waitForProcCompleted()
{
	fSync->lockForSync();
	::std::cout << "CMain::waitForProcCompleted() : start" << ::std::endl;

	while (! fIsProcCompleted) {
	    fSync->wait();
	}

	::std::cout << "CMain::waitForProcCompleted() : end" << ::std::endl;
	fSync->unlockForSync();
}

