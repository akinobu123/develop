// File: CDummyIIT.h

#ifndef _C_DUMMY_IIT_H
#define _C_DUMMY_IIT_H

#include "IRunnable.h"
#include "CThread.h"

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
        ICallbackReceiver *callbackReceiver);

    virtual ~CDummyIIT();

    // IRunnable's method
    virtual void run();

    // CDummyIIT's method
    // async process.
    void startScan();

private:
    CThread *fThread;
    ICallbackReceiver *fCallbackReceiver;

};

#endif /* !_C_DUMMY_IIT_H */

