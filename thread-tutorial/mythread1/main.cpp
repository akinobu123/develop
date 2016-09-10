#include <iostream>
#include "CSynchronizer.h"
#include "CSynchronized.h"
#include "CRunnable.h"
#include "unistd.h"

static const char *const kThreadAName("threadA");
static const char *const kThreadBName("threadB");

int main()
{
    CSynchronizer *sync = CSynchronizer::createInstance();
 
    CRunnable *aRunnable = CRunnable::createInstance(kThreadAName, sync);

    CRunnable *bRunnable = CRunnable::createInstance(kThreadBName, sync);

    sleep(1);

    delete bRunnable;
    
    delete aRunnable;
    
    delete sync;

    return 0;
}
