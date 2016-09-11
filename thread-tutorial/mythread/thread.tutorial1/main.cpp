#include <iostream>
#include <unistd.h>
#include "CRunnable.h"
#include "CSynchronizer.h"

static const char *const kThreadAName("threadA");
static const char *const kThreadBName("threadB");

int main()
{
    CSynchronizer *sync = CSynchronizer::createInstance();
 
    CRunnable *aRunnable = CRunnable::createInstance(kThreadAName, sync);

    // step 3 implement here.
    // create CRunnable instance.
    CRunnable *bRunnable = CRunnable::createInstance(kThreadBName, sync);

    sleep(1);

    // step 3 implement here.
    // delete CRunnable instance.
    delete bRunnable;
    
    delete aRunnable;
    
    delete sync;

    return 0;
}
