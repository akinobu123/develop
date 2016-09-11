// File: CJob.h 

#ifndef _C_JOB_H
#define _C_JOB_H

#include "CDummyIIT.h"
#include "CMutex.h"
#include "CSynchronizer.h"


class CJob : public CDummyIIT::ICallbackReceiver
{
public:
    CJob();

    virtual ~CJob();

    // CJob's method
    void execute();

    // CDummyIIT::ICallbackReceiver's method
    virtual void onScanCompleted();

private:
    bool fIsScanCompleted;
    CSynchronizer *fSync;
    CDummyIIT *fDummyIIT;

    void waitForScanCompleted();

};

#endif /* !_C_JOB_H */
