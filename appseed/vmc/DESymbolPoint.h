// DESymbolPoint.h: interface for the CDESymbolPoint class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DESYMBOLPOINT_H__5BA2660C_EB4F_4E4C_8129_C7564CB0CD46__INCLUDED_)
#define AFX_DESYMBOLPOINT_H__5BA2660C_EB4F_4E4C_8129_C7564CB0CD46__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DocumentElement.h"

class CDESymbolPoint :
	public CDocumentElement
{
public:
	CDESymbolPoint();
	virtual ~CDESymbolPoint();

	int m_ix;
	int m_iy;
	ESymbol m_esymbol;

};

#endif // !defined(AFX_DESYMBOLPOINT_H__5BA2660C_EB4F_4E4C_8129_C7564CB0CD46__INCLUDED_)
