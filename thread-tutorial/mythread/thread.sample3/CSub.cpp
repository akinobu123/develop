#include <iostream>
#include "CSub.h"
#include "CMsg.h"

// constructors & destructor
CSub::CSub( ICallbackReceiver *callbackReceiver, CQueue* queue )
    : fThread(0)
    , fCallbackReceiver(callbackReceiver)
    , fQueue(queue)
{
}

CSub::~CSub()
{
    if (fThread != 0) {
        fThread->join();
        delete fThread;
    }
}

// CSub's method
// async process.
void CSub::startProc()
{
    fThread = CThread::createInstance(this, "");
    fThread->start();
}

// public member functions
// IRunnable's method
void CSub::run()
{
    // sub process
    
    for (int i = 0; i < 5; i++) {
        sleep(1);
        
        CMsg msg;
        fQueue->receive( &msg );
        ::std::cout << msg.getStr() << ::std::endl;
    }

    for (int i = 0; i < 5; i++) {
        sleep(2);
        
        CMsg msg;
        fQueue->receive( &msg );
        ::std::cout << msg.getStr() << ::std::endl;
    }
    
    fCallbackReceiver->onProcCompleted();
}

