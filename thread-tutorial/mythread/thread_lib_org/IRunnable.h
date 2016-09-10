// File: IRunnable.h	- last edit:

// Copyright(C) 2015 by Fuji Xerox Co. Ltd. All rights reserved.

#ifndef _CLIB_I_RUNNABLE_H
#define _CLIB_I_RUNNABLE_H

namespace clib {

    class IRunnable
    {
    public:
	    virtual ~IRunnable() { }

	    virtual void run() = 0;
    };

}
#endif /* _CLIB_I_RUNNABLE_H */
