// File: CSynchronized.h - last edit:

// Copyright(C) 2015 by Fuji Xerox Co. Ltd. All rights reserved.

#ifndef _CLIB_C_SYNCHRONIZED_H
#define _CLIB_C_SYNCHRONIZED_H

#include <stddef.h>
#include "CSynchronizer.h"

class CSynchronized
{
public:
    CSynchronized(CSynchronizer *sync);
    ~CSynchronized();

    void lock();
    void unlock();
    void wait();
    bool wait(int msec);
    void notifyAll();

private:
    CSynchronizer *fSync;
    int fCounter;

private:
    void *operator new(size_t size);
};

#endif /* _CLIB_C_SYNCHRONIZED_H */
