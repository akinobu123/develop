#ifndef _I_MSG_H
#define _I_MSG_H

class IMsg
{
public:
    virtual ~IMsg() { }

    virtual IMsg* duplicate() = 0;
    virtual void copy( IMsg* msg ) = 0;
};

#endif /* _I_MSG_H */
