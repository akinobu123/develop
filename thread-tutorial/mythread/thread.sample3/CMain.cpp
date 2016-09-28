// File: CMain.cpp 

#include <iostream>
#include <sstream>
#include "CMain.h"
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

    for (int i = 0; i < 10; i++) {
        sleep(3);

        // make text
        std::ostrstream strstm ;
        strstm << _T("[A] send interval 3 sec -> print interval 1 sec : ") << i;
        std::string str = strstm;

        // push message to queue
        CMsg msg( str );
        fQueue.send( msg );
    }

    for (int i = 0; i < 10; i++) {
        sleep(1);

        // make text
        std::ostrstream strstm ;
        strstm << _T("[B] send interval 1 sec -> print interval 3 sec : ") << i;
        std::string str = strstm;

        // push message to queue
        CMsg msg( str );
        fQueue.send( msg );
    }

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

