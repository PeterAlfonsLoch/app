// VmsMusDll.h: interface for the CVmsMusDll class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VMSMUSDLL_H__8281F13A_ED0F_407C_BCAA_DC0F615AF678__INCLUDED_)
#define AFX_VMSMUSDLL_H__8281F13A_ED0F_407C_BCAA_DC0F615AF678__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CLASS_DECL_VMSMUS CVmsMusDll  
{
public:
	static bool LoadString(string &rstr, UINT nID);
	CVmsMusDll();
	virtual ~CVmsMusDll();

};

#endif // !defined(AFX_VMSMUSDLL_H__8281F13A_ED0F_407C_BCAA_DC0F615AF678__INCLUDED_)
