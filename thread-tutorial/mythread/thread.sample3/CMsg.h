#ifndef _C_MSG_H_
#define _C_MSG_H_

#include <string>
#include "IMsg.h"

class CMsg : public IMsg
{
public:
    CMsg( ::std::string data ) { fData = data; };
    CMsg() { fData = ""; };
    virtual ~CMsg() {};
    
    // IMsg's methods
    virtual IMsg* duplicate()
    {
        return (IMsg*) new CMsg( fData );
    }

    virtual void copy( IMsg* msg )
    {
        fData = ((CMsg*)msg)->fData;
    }
    
    // original methods
    ::std::string getStr() { return fData; };

private:
    ::std::string fData;

};

#endif /* !_C_MSG_H_*/

