// File: CDummyIIT.cpp

#include <iostream>
#include <unistd.h>
#include <assert.h>
#include "CDummyIIT.h"
#include "CSynchronized.h"

// constructors & destructor
CDummyIIT::CDummyIIT(
    ICallbackReceiver *callbackReceiver, CSynchronizer* sync)
: fThread(0)
, fCallbackReceiver(callbackReceiver)
, fSync(sync)
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
    
    CSynchronized sync(fSync);
    fCallbackReceiver->onScanCompleted();
    sync.notifyAll();
}

// CDummyIIT's method
// async process.
void CDummyIIT::startScan()
{
    ::std::cout << "CDummyIIT:scan requested" << ::std::endl;
    assert((fThread == 0) && "One shot");
    fThread = CThread::createInstance(this, "");
    fThread->start();
}

