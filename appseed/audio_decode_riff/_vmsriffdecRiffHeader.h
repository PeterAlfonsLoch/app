// _vmsriffdecRiffHeader.h: interface for the CRiffHeader class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX__VMSRIFFDECRIFFHEADER_H__6FEB858F_0D57_4C70_954D_351D93AC9950__INCLUDED_)
#define AFX__VMSRIFFDECRIFFHEADER_H__6FEB858F_0D57_4C70_954D_351D93AC9950__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

namespace _vmsriffdec
{

class CRiffHeader  
{
public:
   char     m_szId[4];  	   // identifier string = "RIFF"
	DWORD    m_dwLength;    	// remaining length after this header
public:
	DWORD GetLength();
	bool IsRIFF();
	CRiffHeader();
	~CRiffHeader();
};

///////////////////////////////////////
} // namespace _vmsriffdec
///////////////////////////////////////

#endif // !defined(AFX__VMSRIFFDECRIFFHEADER_H__6FEB858F_0D57_4C70_954D_351D93AC9950__INCLUDED_)
