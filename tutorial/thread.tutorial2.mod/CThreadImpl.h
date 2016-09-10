// File: CThreadImpl.h    - last edit:
// Hideo Kinami        26-Sep-2007

// Copyright(C) 2000 - 2007 by Fuji Xerox Co. Ltd. All rights reserved.

//
//    Linux Implementation
//

#ifndef _CLIB_C_THREAD_IMPL_H
#define _CLIB_C_THREAD_IMPL_H

#include <string>
#include <pthread.h>
#include <sched.h>

#include "CThread.h"
#include "CSynchronizer.h"

namespace clib {

    class CThreadProxy;

    class CThreadImpl
    {
    private:
        CThreadImpl(
            IRunnable *r, 
            const char *name, 
            size_t stackSize,
            CThreadProxy *proxy);

    public:
        ~CThreadImpl();

        static CThreadImpl* createInstance(
            IRunnable *r, 
            const char *name,
            size_t stackSize,
            CThreadProxy *proxy);

        bool start(
            bool detach);

        void join();

        void setPriority(
            int priority);

        int getPriority();

        const char *getName();

        static int getMaxPriority();

        static int getMinPriority();

        static int getDefaultPriority();

        static int getDefaultStackSize();

        static int getSelfID();

    private:
        enum { 
            kDefaultPriority = 50 // for Linux min = 1, max = 99
        };
        enum { 
            kDefaultStackSize = 1048576  // 1 mega-bytes
        };
        enum EState { 
            eInitialized, 
            eBeingSpawn, 
            eRunning, 
            eDetached, 
            eJoined 
        };
        enum { 
            kSchedulingPolicy = SCHED_RR 
        };

        EState fState;
        IRunnable *fRunnable;
        ::std::string fName;
        size_t fStackSize;
        int fPriority;
        pthread_t fThreadID;
        CThreadProxy *fProxy;

        void setState(
            EState s)
        {
            fState = s;
        }

        EState getState()
        {
            return fState;
        }

        static void *taskFunction(
            void *arg);
    };

    // private member inline functions
    inline int CThreadImpl::getPriority()
    {
        return fPriority;
    }

    inline const char *CThreadImpl::getName()
    {
        return fName.c_str();
    }

    inline int CThreadImpl::getMaxPriority()
    {
        return (sched_get_priority_max(kSchedulingPolicy));
    }

    inline int CThreadImpl::getMinPriority()
    {
        return (sched_get_priority_min(kSchedulingPolicy));
    }

    inline int CThreadImpl::getDefaultPriority()
    {
        return kDefaultPriority;
    }

    inline int CThreadImpl::getDefaultStackSize()
    {
        return kDefaultStackSize;
    }
    
}

#endif /* _CLIB_C_THREAD_IMPL_H */
