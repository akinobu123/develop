// File: CRunnable.h      - last edit:

#ifndef _C_RUNNABLE_H
#define _C_RUNNABLE_H

#include <string>
#include "CMutex.h"
#include "CThread.h"

class CRunnable : public IRunnable
{
private:
    CRunnable(
        const char *id,
        CMutex *mutex);

public:
    virtual ~CRunnable();

    static CRunnable *createInstance(
        const char *id,
        CMutex *mutex);

    // IRunnable's method
    virtual void run();

private:
    bool fIsTerminated;
    ::std::string fID;
    CMutex *fMutex;
    CThread *fThread;

    void start();

    bool isTerminated();

    void print();

    void terminate();

};

#endif /* !_C_RUNNABLE_H */
