#ifndef _C_MAIN_H
#define _C_MAIN_H

#include "CSub.h"
#include "CQueue.h"
#include "CCondVal.h"


class CMain : public CSub::ICallbackReceiver
{
public:
    CMain();
    virtual ~CMain();

    // CMain's method
    void execute();

    // CSub::ICallbackReceiver's method
    virtual void onProcCompleted();
    
private:
    void waitForProcCompleted();

private:
    bool fIsProcCompleted;
    CQueue fQueue;
    CCondVal *fCondVal;
    CSub *fSub;
};

#endif /* !_C_MAIN_H */
