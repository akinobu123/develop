#include "CMain.h"

int main()
{
    CMain *mainJob = new CMain();
    mainJob->execute();

    delete mainJob;
    return 0;
}
