// File: CMain.h 

#ifndef _C_MAIN_H
#define _C_MAIN_H

#include "CSub.h"
#include "CMutex.h"
#include "CSynchronizer.h"


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
    bool fIsProcCompleted;
    CSynchronizer *fSync;
    CSub *fSub;

    void waitForProcCompleted();

};

#endif /* !_C_MAIN_H */
