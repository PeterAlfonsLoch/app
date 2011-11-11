// _vmsaiffdecExtended.h: interface for the CExtended class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX__VMSAIFFDECEXTENDED_H__CDC21B4E_1721_475F_80E3_22C879BE8848__INCLUDED_)
#define AFX__VMSAIFFDECEXTENDED_H__CDC21B4E_1721_475F_80E3_22C879BE8848__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

namespace _vmsaiffdec
{


class CExtended  
{
   char     m_szData[10];
public:
	bool Initialize();
	void SetValue(long double ld);
	long double GetValue();
	CExtended();
	~CExtended();

};


/////////////////////////////////////////////////////////////
} // namespace _vmsaiffdec
/////////////////////////////////////////////////////////////

#endif // !defined(AFX__VMSAIFFDECEXTENDED_H__CDC21B4E_1721_475F_80E3_22C879BE8848__INCLUDED_)
