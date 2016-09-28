#ifndef _C_MUTEXAUTO_H
#define _C_MUTEXAUTO_H

#include <stddef.h>
#include "CMutex.h"

class CMutexAuto
{
public:
    CMutexAuto(CMutex *mutex);
    ~CMutexAuto();

private:
    CMutex *fMutex;
};

#endif /* _C_MUTEXAUTO_H */
