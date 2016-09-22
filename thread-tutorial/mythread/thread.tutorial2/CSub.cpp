// File: CSub.cpp

#include <iostream>
#include <unistd.h>
#include <assert.h>
#include "CSub.h"

// constructors & destructor
CSub::CSub( ICallbackReceiver *callbackReceiver )
 : fThread(0)
 , fCallbackReceiver(callbackReceiver)
{
    // Nothing to do.
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
    ::std::cout << "CSub:proc requested" << ::std::endl;
    fThread = CThread::createInstance(this, "");
    fThread->start();
}

// public member functions
// IRunnable's method
void CSub::run()
{
    // sub process
    
    for (int i = 0; i < 3; i++) {
        sleep(1);
        ::std::cout << "CSub:now processing..." << ::std::endl;
    }

    ::std::cout << "CSub:completed" << ::std::endl;
    
    fCallbackReceiver->onProcCompleted();
}

