#ifndef _C_SUB_H_
#define _C_SUB_H_

#include "CThread.h"
#include "CQueue.h"
#include <unistd.h>

class CSub : public CThread
{
public:
    CSub(CQueue* queueToSub, CQueue* queueToMain);

    virtual ~CSub();

    // IRunnable's method
    virtual void* run();

private:
    CQueue* fQueueToSub;
    CQueue* fQueueToMain;

};

#endif /* !_C_SUB_H_*/

