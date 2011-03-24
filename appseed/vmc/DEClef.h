// DEClef.h: interface for the CDEClef class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DECLEF_H__2B215CC9_70B0_4E0E_B9F6_EB9CE7046570__INCLUDED_)
#define AFX_DECLEF_H__2B215CC9_70B0_4E0E_B9F6_EB9CE7046570__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DocumentElement.h"

class CDEClef : public CDocumentElement  
{
public:
	enum EType
	{
		Treble,
		Middle,
		Bass
	};

	CDEClef();
	virtual ~CDEClef();

	EType m_etype;

};

#endif // !defined(AFX_DECLEF_H__2B215CC9_70B0_4E0E_B9F6_EB9CE7046570__INCLUDED_)
