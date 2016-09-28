#include <pthread.h>
#include <string>

#include "IRunnable.h"

class CThread
{
private:
    CThread(IRunnable *runnable, const char *name);
    
public:
    virtual ~CThread();
    static CThread *createInstance(IRunnable *runnable, const char *name);
    
    void start();
    void join();

private:
    static void *func(void *arg);

private:
    IRunnable *fRunnable;
    ::std::string fName;
    pthread_t fThreadId;

};

