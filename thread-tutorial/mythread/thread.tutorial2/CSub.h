// File: CSub.h 

#ifndef _C_SUB_H_
#define _C_SUB_H_

#include "IRunnable.h"
#include "CThread.h"
#include <unistd.h>

class CSub:
    public IRunnable
{
public:
    class ICallbackReceiver
    {
    public:
        virtual ~ICallbackReceiver() { }

        // ICallbackReceiver's method
        virtual void onProcCompleted() = 0;
    };

    CSub(ICallbackReceiver *callbackReceiver);

    virtual ~CSub();

    // CSub's method
    // async process.
    void startProc();

    // IRunnable's method
    virtual void run();

private:
    CThread *fThread;
    ICallbackReceiver *fCallbackReceiver;

};

#endif /* !_C_SUB_H_*/

