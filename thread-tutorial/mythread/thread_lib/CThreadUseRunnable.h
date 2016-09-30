#include <pthread.h>
#include <string>

#include "IRunnable.h"

class CThreadUseRunnable
{
private:
    CThreadUseRunnable(IRunnable *runnable, const char *name);
    
public:
    virtual ~CThreadUseRunnable();
    static CThreadUseRunnable *createInstance(IRunnable *runnable, const char *name);
    
    void start();
    void join();

private:
    static void *func(void *arg);

private:
    IRunnable *fRunnable;
    ::std::string fName;
    pthread_t fThreadId;

};

