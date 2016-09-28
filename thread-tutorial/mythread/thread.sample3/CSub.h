#ifndef _C_SUB_H_
#define _C_SUB_H_

#include "IRunnable.h"
#include "CThread.h"
#include "CQueue.h"
#include <unistd.h>

class CSub : public IRunnable
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

    CSub(ICallbackReceiver *callbackReceiver, CQueue* queue);

    virtual ~CSub();

    // CSub's method
    void startProc();

    // IRunnable's method
    virtual void run();

private:
    CThread *fThread;
    ICallbackReceiver *fCallbackReceiver;
    CQueue* fQueue;

};

#endif /* !_C_SUB_H_*/

