// _vmsaiffdecChunkHeader.h: interface for the CChunkHeader class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX__VMSAIFFDECCHUNKHEADER_H__DF6145F5_8A75_493E_AEDD_C1CBAB91D7BC__INCLUDED_)
#define AFX__VMSAIFFDECCHUNKHEADER_H__DF6145F5_8A75_493E_AEDD_C1CBAB91D7BC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "_vmsaiffdecID.h"




namespace _vmsaiffdec
{

class CChunkHeader  
{
public:
   CID         m_id;
   DWORD       m_lSize;
public:
	bool Initialize();
	DWORD GetSize();
	CChunkHeader();
	~CChunkHeader();

};

/////////////////////////////////////////////////////////////
} // namespace _vmsaiffdec
/////////////////////////////////////////////////////////////


#endif // !defined(AFX__VMSAIFFDECCHUNKHEADER_H__DF6145F5_8A75_493E_AEDD_C1CBAB91D7BC__INCLUDED_)
