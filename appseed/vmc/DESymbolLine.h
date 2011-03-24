// DESymbolLine.h: interface for the CDESymbolLine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DESYMBOLLINE_H__EACFFB44_C82D_4EBA_B368_8581DDA301E2__INCLUDED_)
#define AFX_DESYMBOLLINE_H__EACFFB44_C82D_4EBA_B368_8581DDA301E2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DocumentElement.h"

class CDESymbolLine : public CDocumentElement  
{
public:
	CDESymbolLine();
	virtual ~CDESymbolLine();

	int m_istartx;
	int m_istarty;
	int m_ifinalx;
	int m_ifinaly;
	ESymbol m_esymbol;


};

#endif // !defined(AFX_DESYMBOLLINE_H__EACFFB44_C82D_4EBA_B368_8581DDA301E2__INCLUDED_)
