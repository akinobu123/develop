#include <iostream>
#include <unistd.h>
#include "CRunnable.h"
#include "CMutex.h"

static const char *const kThreadAName("threadA");
static const char *const kThreadBName("threadB");

int main()
{
    CMutex *mutex = new CMutex();
 
    CRunnable *aRunnable = CRunnable::createInstance(kThreadAName, mutex);

    CRunnable *bRunnable = CRunnable::createInstance(kThreadBName, mutex);

    sleep(1);

    delete bRunnable;
    
    delete aRunnable;
    
    delete mutex;

    return 0;
}
