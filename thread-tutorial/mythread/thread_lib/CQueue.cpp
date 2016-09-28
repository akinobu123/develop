#include <assert.h>

#include "CQueue.h"

// constructors & destructor
CQueue::CQueue()
    : fData()
    , fCondVal(NULL)
{
    fCondVal = CCondVal::createInstance();
}

CQueue::~CQueue()
{
    while( ! fData.empty() ) {
        IMsg* tmp = fData.front();
        delete tmp;
        fData.pop_front();
    }
    delete fCondVal;
}

void CQueue::send( IMsg& msg )
{
    fCondVal.lockForSync();

    // processing
    IMsg* myMsg = msg.duplicate();
    fData.push( myMsg );

    // notify
    fCondVal.notifyAll();
    fCondVal.unlockForSync();
}

void CQueue::receive( IMsg* msg )
{
    fCondVal.lockForSync();
    // wait until queue is not empty.
    while (fData.empty()) {
        fCondVal.wait();
    }

    // processing
    IMsg* myMsg = fData.front();
    fData.pop();
    msg->copy( myMsg );
    delete myMsg;

    fCondVal.unlockForSync();
}
