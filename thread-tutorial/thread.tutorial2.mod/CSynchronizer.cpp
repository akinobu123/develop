// File: CSynchronizer.cpp	- last edit:

// Copyright(C) 2015 by Fuji Xerox Co. Ltd. All rights reserved.

#include <stdlib.h>
#include <assert.h>
#include "CSynchronizer.h"
#include "CSynchronizerImpl.h"

using namespace ::clib;

CSynchronizer::~CSynchronizer()
{
    // Nothing to do.
}

CSynchronizer* CSynchronizer::createInstance(
    EClassVersion version)
{
    assert(version == kClassVersion);
    return CSynchronizerImpl::createInstance();
}
