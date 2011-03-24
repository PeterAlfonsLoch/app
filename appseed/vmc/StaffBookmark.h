// StaffBookmark.h: interface for the CStaffBookmark class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STAFFBOOKMARK_H__615D9382_FA8A_41A2_A0C9_BB1670512B55__INCLUDED_)
#define AFX_STAFFBOOKMARK_H__615D9382_FA8A_41A2_A0C9_BB1670512B55__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DocumentElement.h"

class CStaffBookmark : public CDocumentElement  
{
public:
	CStaffBookmark();
	virtual ~CStaffBookmark();

	unsigned short m_ushStaff;

};

#endif // !defined(AFX_STAFFBOOKMARK_H__615D9382_FA8A_41A2_A0C9_BB1670512B55__INCLUDED_)
