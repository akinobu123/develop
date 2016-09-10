// File: CJob.h      - last edit:

// Copyright(C) 2015 by Fuji Xerox Co., Ltd. All rights reserved.

#ifndef _C_JOB_H
#define _C_JOB_H

#include "CDummyIIT.h"
#include "CSynchronizer.h"


class CJob:
    public CDummyIIT::ICallbackReceiver
{
public:
    CJob();

    virtual ~CJob();

    // CDummyIIT::ICallbackReceiver's method
    virtual void onScanCompleted();

    // CJob's method
    void execute();

private:
    bool fIsScanCompleted;
    CSynchronizer *fSync;
    CDummyIIT *fDummyIIT;

    void getReadyToScan();

    void waitForScanCompleted();

};

#endif /* !_C_JOB_H */
