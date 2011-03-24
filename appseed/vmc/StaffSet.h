// StaffSet.h: interface for the CStaffSet class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STAFFSET_H__A02AA057_2B3D_4719_96F1_2DC1EBC18BC7__INCLUDED_)
#define AFX_STAFFSET_H__A02AA057_2B3D_4719_96F1_2DC1EBC18BC7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DocumentElement.h"

class CStaffSet : public CDocumentElement  
{
public:
	CStaffSet();
	virtual ~CStaffSet();

	unsigned short m_ushStaffSet;


};

#endif // !defined(AFX_STAFFSET_H__A02AA057_2B3D_4719_96F1_2DC1EBC18BC7__INCLUDED_)
