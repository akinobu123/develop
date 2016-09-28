#include <assert.h>

#include "CQueue.h"

// constructors & destructor
CQueue::CQueue()
    : fData()
    , fCondVal()
{
}

CQueue::~CQueue()
{
    for( auto itr = fData.begin(); itr != fData.end(); ++itr) {
        delete &(*itr);
    }
    fData.clear();
}

void CQueue::send( IMsg& msg )
{
    fCondVal.lockForSync();

    // processing
    IMsg* myMsg = msg.duplicate();
    fData.push_back( myMsg );

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
    fData.pop_front();
    msg->copy( myMsg );
    delete myMsg;

    fCondVal.unlockForSync();
}
