// File: CJobStat.cpp      - last edit:

// Copyright(C) 2015 by Fuji Xerox Co., Ltd. All rights reserved.

#include <iostream>
#include "CJobStat.h"
#include "CSynchronized.h"

// constructors & destructor
CJobStat::CJobStat()
: fIsScanCompleted(false)
, fSync(0)
{
    fSync = CSynchronizer::createInstance();
} 

CJobStat::~CJobStat()
{
    delete fSync;
}

void CJobStat::onScanCompleted()
{
    CSynchronized sync(fSync);
    fIsScanCompleted = true;
}

bool CJobStat::isScanCompleted()
{
    CSynchronized sync(fSync);
    return fIsScanCompleted;
}

void CJobStat::wait()
{
    fSync->wait();
}

void CJobStat::notifyAll()
{
    fSync->notifyAll();
}

