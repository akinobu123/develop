// File: CThread.h    - last edit:

// Copyright(C) 2015 by Fuji Xerox Co. Ltd. All rights reserved.

#ifndef _CLIB_C_THREAD_H
#define _CLIB_C_THREAD_H

#include <stddef.h>

#include "IRunnable.h"

namespace clib {

    class CThread
    {
    public:
        enum EClassVersion {
            kClassVersion = 5
        };

        virtual ~CThread();

        static CThread *createInstance(
            IRunnable *runnable,
            const char *name,
            EClassVersion version = kClassVersion);

        static CThread *createInstance(
            IRunnable *runnable,
            const char *name,
            size_t stackSize,
            EClassVersion version = kClassVersion);

        virtual void start(
            bool detach = false) = 0;

        virtual void join() = 0;

        virtual void setPriority(
            int priority) = 0;

        virtual int getPriority() = 0;

        virtual const char *getName() = 0;

        static int getMaxPriority();

        static int getMinPriority();

        static int getSelfID();
    };

}

#endif /* _CLIB_C_THREAD_H */
