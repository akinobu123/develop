// File: CMain.cpp 

#include <iostream>
#include <sstream>
#include "CMain.h"
#include "CQueue.h"
#include "CMsg.h"

// constructors & destructor
CMain::CMain()
    : fQueueToSub()
    , fQueueToMain()
    , fSub(0)
{
    fSub = new CSub(&fQueueToSub, &fQueueToMain);
}

CMain::~CMain()
{
    fSub->join();
    delete fSub;
}


// CMain's method
void CMain::execute()
{

    fSub->start();

    for (int i = 0; i < 5; i++) {
        sleep(2);

        // make text
        ::std::ostringstream strstm ;
        strstm << "[A] send interval 2 sec -> print interval 1 sec : " << i;

        // push message to queue
        CMsg msg( strstm.str() );
        fQueueToSub.send( msg );
    }

    for (int i = 0; i < 5; i++) {
        sleep(1);

        // make text
        ::std::ostringstream strstm ;
        strstm << "[B] send interval 1 sec -> print interval 2 sec : " << i;

        // push message to queue
        CMsg msg( strstm.str() );
        fQueueToSub.send( msg );
    }
    
    ::std::cout << "CMain : all sended. waiting for CSub." << ::std::endl;

    // waiting for CSub queueing.
    CMsg msg;
    while(msg.getStr() != "ended") {
        fQueueToMain.receive( &msg );
    }
    ::std::cout << "CMain : received end-msg from CSub." << ::std::endl;
}

