// Clef.h: interface for the CClef class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CLEF_H__CAF8DC73_21EA_46C1_8F88_46C356169103__INCLUDED_)
#define AFX_CLEF_H__CAF8DC73_21EA_46C1_8F88_46C356169103__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DocumentVisual.h"

class CClef :
	public CDocumentVisual
{
public:
	enum EType
	{
		Treble,
		Middle,
		Bass
	};
	CClef();
	virtual ~CClef();

	EType m_etype;

};

#endif // !defined(AFX_CLEF_H__CAF8DC73_21EA_46C1_8F88_46C356169103__INCLUDED_)
