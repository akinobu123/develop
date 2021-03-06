#ifndef _C_QUEUE_H
#define _C_QUEUE_H

#include <queue>
#include "CCondVal.h"
#include "IMsg.h"

class CQueue
{
public:
    CQueue();
    virtual ~CQueue();
    
    void send( IMsg& msg );
    void receive( IMsg* msg );

private:
    ::std::queue<IMsg*> fData;
    CCondVal* fCondVal;
};

#endif /* _C_QUEUE_H */
