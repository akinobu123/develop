#include <iostream>
#include <unistd.h>
#include <assert.h>
#include "CSub.h"

// constructors & destructor
CSub::CSub( ICallbackReceiver *callbackReceiver )
    : CThread("CSub")
    , fCallbackReceiver(callbackReceiver)
{
}

CSub::~CSub()
{
}

// public member functions
// IRunnable's method
void* CSub::run()
{
    // sub process
    
    for (int i = 0; i < 3; i++) {
        sleep(1);
        ::std::cout << "CSub:now processing..." << ::std::endl;
    }

    ::std::cout << "CSub:completed" << ::std::endl;
    
    fCallbackReceiver->onProcCompleted();

    return NULL;
}

