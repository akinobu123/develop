// File: CDummyIIT.cpp


#include <iostream>
#include <unistd.h>
#include <assert.h>
#include "CDummyIIT.h"

// constructors & destructor
CDummyIIT::CDummyIIT( ICallbackReceiver *callbackReceiver )
 : fThread(0)
 , fCallbackReceiver(callbackReceiver)
{
    // Nothing to do.
}

CDummyIIT::~CDummyIIT()
{
    if (fThread != 0) {
        fThread->join();
        delete fThread;
    }
}

// CDummyIIT's method
// async process.
void CDummyIIT::startScan()
{
    ::std::cout << "CDummyIIT:scan requested" << ::std::endl;
    assert(fThread == 0);
    fThread = CThread::createInstance(this, "");
    fThread->start();
}

// public member functions
// IRunnable's method
void CDummyIIT::run()
{
    // dummy scan process
    
    for (int i = 0; i < 3; i++) {
        sleep(1);
        ::std::cout << "CDummyIIT:now scanning..." << ::std::endl;
    }

    ::std::cout << "CDummyIIT:scan completed" << ::std::endl;
    
    fCallbackReceiver->onScanCompleted();
}

