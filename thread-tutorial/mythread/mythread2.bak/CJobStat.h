// File: CJobStat.h      - last edit:

// Copyright(C) 2015 by Fuji Xerox Co., Ltd. All rights reserved.

#ifndef _C_JOB_STAT_H
#define _C_JOB_STAT_H

#include "CSynchronizer.h"


class CJobStat
{
public:
    CJobStat();

    virtual ~CJobStat();

    void onScanCompleted();
    bool isScanCompleted();
    void wait();
    void notifyAll();

private:
    bool fIsScanCompleted;
    CSynchronizer *fSync;

};

#endif /* !_C_JOB_STAT_H */
