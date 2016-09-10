// File: CThreadProxy.h    - last edit:

// Copyright(C) 2015 by Fuji Xerox Co. Ltd. All rights reserved.

#ifndef _CLIB_C_THREAD_PROXY_H
#define _CLIB_C_THREAD_PROXY_H

#include "CThread.h"
#include "CThreadImpl.h"
#include "CSynchronizer.h"

namespace clib {

    class CThreadProxy: 
        public CThread
    {
    private:
        CThreadProxy(
            IRunnable *runnable, 
            const char *name,
            size_t stackSize);

    public:
        ~CThreadProxy();

        static CThreadProxy *createInstance(
            IRunnable *runnable, 
            const char *name,
            size_t stackSize);

        virtual void start(
            bool detach);

        virtual void join();

        virtual void setPriority(
            int priority);

        virtual int getPriority();

        virtual const char *getName();

        void setTerminateState();

        static int getMaxPriority();

        static int getMinPriority();
        
        static int getSelfID();

    private:
        enum EState {
            eCreated, 
            eStarted, 
            eTerminated, 
            eDetached, 
            eJoined
        };

        EState fThreadState;
        CThreadImpl *fThreadImpl;
        CSynchronizer *fSync;

        bool hasErrorOccurred();
    };

}

#endif /* _CLIB_C_THREAD_PROXY_H */
