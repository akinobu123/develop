#ifndef _C_SUB_H_
#define _C_SUB_H_

#include "CThread.h"
#include <unistd.h>

class CSub : public CThread
{
public:
    // --- inner class ---
    class ICallbackReceiver
    {
    public:
        virtual ~ICallbackReceiver() { }

        // ICallbackReceiver's method
        virtual void onProcCompleted() = 0;
    };
    // --- inner class ---

    CSub(ICallbackReceiver *callbackReceiver);

    virtual ~CSub();

    // CThread's method
    virtual void* run();

private:
    ICallbackReceiver *fCallbackReceiver;

};

#endif /* !_C_SUB_H_*/

