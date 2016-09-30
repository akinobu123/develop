#ifndef _C_MAIN_H
#define _C_MAIN_H

#include "CSub.h"
#include "CQueue.h"
#include "CCondVal.h"


class CMain
{
public:
    CMain();
    virtual ~CMain();

    // CMain's method
    void execute();

private:
    CQueue fQueueToSub;
    CQueue fQueueToMain;
    CSub *fSub;
};

#endif /* !_C_MAIN_H */
