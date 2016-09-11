#include "CJob.h"

int main()
{
    CJob *job = new CJob();
    job->execute();

    delete job;
    return 0;
}
