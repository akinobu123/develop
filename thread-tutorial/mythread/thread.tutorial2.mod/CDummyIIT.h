// File: CDummyIIT.h 

#ifndef _C_DUMMY_IIT_H
#define _C_DUMMY_IIT_H

#include "IRunnable.h"
#include "CThread.h"
#include "CSynchronizer.h"
#include <unistd.h>

class CDummyIIT:
    public IRunnable
{
public:
    class ICallbackReceiver
    {
    public:
        virtual ~ICallbackReceiver() { }

        // ICallbackReceiver's method
        virtual void onScanCompleted() = 0;
    };

    CDummyIIT(
        ICallbackReceiver *callbackReceiver, CSynchronizer* sync);

    virtual ~CDummyIIT();

    // IRunnable's method
    virtual void run();

    // CDummyIIT's method
    // async process.
    void startScan();

private:
    CSynchronizer *fSync;
    CThread *fThread;
    ICallbackReceiver *fCallbackReceiver;

};

#endif /* !_C_DUMMY_IIT_H */

