// File: IRunnable.h	- last edit:


#ifndef _CLIB_I_RUNNABLE_H
#define _CLIB_I_RUNNABLE_H

class IRunnable
{
public:
    virtual ~IRunnable() { }

    virtual void run() = 0;
};

#endif /* _I_RUNNABLE_H */
