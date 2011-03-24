// CRC.h: interface for the CCRC class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CRC_H__49844964_7010_4D2A_A88B_2D4F4CFD948B__INCLUDED_)
#define AFX_CRC_H__49844964_7010_4D2A_A88B_2D4F4CFD948B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CLASS_DECL_ca CCRC  
{
public:
	typedef unsigned long Type;
    enum Key
    {
        ethernetKey = 0x04c11db7
    };

    //static Type const c;
public:
	CCRC(Type key);
	virtual ~CCRC();

public:
	Type Done ();

protected:
	Type m_key;	// really 33-bit key, counting implicit 1 top-bit
	Type m_register;
};

#endif // !defined(AFX_CRC_H__49844964_7010_4D2A_A88B_2D4F4CFD948B__INCLUDED_)
