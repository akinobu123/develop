// File: CSynchronizerImpl.h    - last edit:

// Copyright(C) 2015 by Fuji Xerox Co. Ltd. All rights reserved.

#ifndef _CLIB_C_SYNCHRONIZER_IMPL_H
#define _CLIB_C_SYNCHRONIZER_IMPL_H

#include <pthread.h>
#include "CSynchronizer.h"

namespace clib {

    class CSynchronizerImpl : public CSynchronizer
    {
    private:
        CSynchronizerImpl();

    public:
        virtual ~CSynchronizerImpl();

        static CSynchronizerImpl *createInstance();

        virtual void lock();

        virtual void unlock();

        virtual void wait();

        virtual bool wait(
            int msec);

        virtual void notify();

        virtual void notifyAll();

    private:
        enum EState { 
            eUnlocked, 
            eLocked, 
            eInvalid 
        };

        enum { 
            kThreadListSize = 16 
        };

        class CThreadLockedLevel
        {
        public:
            CThreadLockedLevel()
            : fLockedLevel(0),
              fEmpty(true)
            { }

            pthread_t fThreadID;
            int fLockedLevel;
            bool fEmpty;
        };

        friend class CThreadLockedLevel;

        EState fState;
        int fErrorNumber;
        pthread_t fThreadID;
        int fLockedLevel;
        CThreadLockedLevel fThreadList[kThreadListSize];
        pthread_mutex_t fLock;
        pthread_cond_t fReleased;
        pthread_cond_t fNotified;

        void setState(
            EState s);

        EState getState();

        void setErrorNumber(
            int error);

        int getErrorNumber();

        void setThreadID(
            pthread_t threadID);

        pthread_t getThreadID();

        int getLockedLevel();

        void setLockedLevel(
            int level);

        void incrementLockedLevel();

        void decrementLockedLevel();

        bool isLockedBySelf();

        void saveThreadLockedInfo();

        void restoreThreadLockedInfo();

        void putThreadLockedLevel(
            pthread_t threadID, 
            int level);

        int getThreadLockedLevel(
            pthread_t threadID);

        void removeThreadLockedLevel(
            pthread_t threadID);
    };

    // private member inline functions
    inline void CSynchronizerImpl::setErrorNumber(
        int error)
    {
        fErrorNumber = error;
    }

    inline int CSynchronizerImpl::getErrorNumber()
    {
        return fErrorNumber;
    }

    inline void CSynchronizerImpl::setThreadID(
        pthread_t threadID)
    {
        fThreadID = threadID;
    }

    inline pthread_t CSynchronizerImpl::getThreadID()
    {
        return fThreadID;
    }

    inline int CSynchronizerImpl::getLockedLevel()
    {
        return fLockedLevel;
    }

}

#endif /* _CLIB_C_SYNCHRONIZER_IMPL_H */
