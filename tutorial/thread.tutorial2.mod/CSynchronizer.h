// File: CSynchronizer.h - last edit:

// Copyright(C) 2015 by Fuji Xerox Co. Ltd. All rights reserved.

#ifndef _CLIB_C_SYNCHRONIZER_H
#define _CLIB_C_SYNCHRONIZER_H

namespace clib {

    class CSynchronizer
    {
    public:
    	enum EClassVersion { kClassVersion = 6 };

    	virtual ~CSynchronizer();

	    static CSynchronizer *createInstance(
            EClassVersion version = kClassVersion);

    	virtual void lock() = 0;
    
	    virtual void unlock() = 0;

    	virtual void wait() = 0;

	    virtual bool wait(
            int msec) = 0;

    	virtual void notify() = 0;

	    virtual void notifyAll() = 0;

    };

}
#endif /* _CLIB_C_SYNCHRONIZER_H */
