#include <pthread.h>
#include <string>

class CThread
{
public:
    CThread(const char *name);
    virtual ~CThread();
    
    void start();
    void join();
    virtual void* run() = 0;

private:
    static void* func(void *arg);

private:
    pthread_t fThreadId;
    ::std::string fName;

};

