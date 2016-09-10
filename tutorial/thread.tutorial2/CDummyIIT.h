// File: CDummyIIT.h      - last edit:

// Copyright(C) 2015 by Fuji Xerox Co., Ltd. All rights reserved.

#ifndef _C_DUMMY_IIT_H
#define _C_DUMMY_IIT_H

#include "IRunnable.h"
#include "CThread.h"

class CDummyIIT:
    public ::clib::IRunnable
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

    // ::clib::IRunnable's method
    virtual void run();

    // CDummyIIT's method
    // async process.
    void startScan();

private:
    ::clib::CThread *fThread;
    ICallbackReceiver *fCallbackReceiver;

};

#endif /* !_C_DUMMY_IIT_H */

