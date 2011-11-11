// _vmsriffdecRiffId.h: interface for the CRiffId class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX__VMSRIFFDECRIFFID_H__2C392E3B_A892_4E0B_8A08_95A438B209E8__INCLUDED_)
#define AFX__VMSRIFFDECRIFFID_H__2C392E3B_A892_4E0B_8A08_95A438B209E8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

namespace _vmsriffdec
{

class CRiffId  
{
public:
   char     m_szId[4];	// WAVE file identifier = "WAVE"

public:
	bool IsWAVE();
	CRiffId();
	~CRiffId();

};

///////////////////////////////////////
} // namespace _vmsriffdec
///////////////////////////////////////


#endif // !defined(AFX__VMSRIFFDECRIFFID_H__2C392E3B_A892_4E0B_8A08_95A438B209E8__INCLUDED_)
