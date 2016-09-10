// File: CRunnable.h      - last edit:

// Copyright(C) 2015 by Fuji Xerox Co., Ltd. All rights reserved.

#ifndef _C_RUNNABLE_H
#define _C_RUNNABLE_H

#include <string>
#include "CSynchronizer.h"
#include "CThread.h"

class CRunnable:
    public IRunnable
{
private:
    CRunnable(
        const char *id,
        CSynchronizer *sync);

public:
    virtual ~CRunnable();

    static CRunnable *createInstance(
        const char *id,
        CSynchronizer *sync);

    // IRunnable's method
    virtual void run();

private:
    bool fIsTerminated;
    ::std::string fID;
    CSynchronizer *fSync;
    CThread *fThread;

    void start();

    bool isTerminated();

    void print();

    void terminate();

};

#endif /* !_C_RUNNABLE_H */
