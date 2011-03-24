// Staff.h: interface for the CStaff class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STAFF_H__BB852576_2B6E_4046_BE43_659E4E309081__INCLUDED_)
#define AFX_STAFF_H__BB852576_2B6E_4046_BE43_659E4E309081__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DocumentVisual.h"

class CStaff : public CDocumentVisual
{
public:
	enum EType
	{

	};
	CStaff();
	virtual ~CStaff();

	unsigned short m_ushStaff;

};

#endif // !defined(AFX_STAFF_H__BB852576_2B6E_4046_BE43_659E4E309081__INCLUDED_)
