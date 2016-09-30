#include <iostream>
#include "CSub.h"
#include "CMsg.h"

// constructors & destructor
CSub::CSub(CQueue* queueToSub, CQueue* queueToMain )
    : CThread("CSub")
    , fQueueToSub(queueToSub)
    , fQueueToMain(queueToMain)
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
    
    for (int i = 0; i < 5; i++) {
        sleep(1);
        
        CMsg msg;
        fQueueToSub->receive( &msg );
        ::std::cout << msg.getStr() << ::std::endl;
    }

    for (int i = 0; i < 5; i++) {
        sleep(2);
        
        CMsg msg;
        fQueueToSub->receive( &msg );
        ::std::cout << msg.getStr() << ::std::endl;
    }
    
    CMsg msg("ended");
    fQueueToMain->send( msg );

    return NULL;
}

