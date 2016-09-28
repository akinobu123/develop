// File: CMain.cpp 

#include <iostream>
#include <sstream>
#include "CMain.h"
#include "CQueue.h"
#include "CMsg.h"

// constructors & destructor
CMain::CMain()
    : fIsProcCompleted(false)
    , fQueue()
    , fCondVal(0)
    , fSub(0)
{
    fCondVal = CCondVal::createInstance();
    fSub = new CSub(this, &fQueue);
}

CMain::~CMain()
{
    delete fSub;
    delete fCondVal;
}


// CMain's method
void CMain::execute()
{

    fSub->startProc();

    for (int i = 0; i < 5; i++) {
        sleep(2);

        // make text
        ::std::ostringstream strstm ;
        strstm << "[A] send interval 2 sec -> print interval 1 sec : " << i;

        // push message to queue
        CMsg msg( strstm.str() );
        fQueue.send( msg );
    }

    for (int i = 0; i < 5; i++) {
        sleep(1);

        // make text
        ::std::ostringstream strstm ;
        strstm << "[B] send interval 1 sec -> print interval 2 sec : " << i;

        // push message to queue
        CMsg msg( strstm.str() );
        fQueue.send( msg );
    }
    
    ::std::cout << "CMain : all sended. waiting for CSub." << ::std::endl;

    waitForProcCompleted();
}

// public member functions
// CSub::ICallbackReceiver's method
void CMain::onProcCompleted()
{
    fCondVal->lockForSync();

    fIsProcCompleted = true;

    fCondVal->notifyAll();

    fCondVal->unlockForSync();
}

// private member functions
void CMain::waitForProcCompleted()
{
    fCondVal->lockForSync();

    while (! fIsProcCompleted) {
        fCondVal->wait();
    }
    fCondVal->unlockForSync();
}

