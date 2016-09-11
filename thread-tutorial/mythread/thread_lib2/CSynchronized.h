// File: CSynchronized.h - last edit:


#ifndef _C_SYNCHRONIZED_H
#define _C_SYNCHRONIZED_H

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

private:
//    void *operator new(size_t size);
};

#endif /* _C_SYNCHRONIZED_H */
