// DESymbolSDLine.h: interface for the CDESymbolSDLine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DESYMBOLSDLINE_H__1628DEC6_236D_4DA7_83C7_7F1BD70D0F8D__INCLUDED_)
#define AFX_DESYMBOLSDLINE_H__1628DEC6_236D_4DA7_83C7_7F1BD70D0F8D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DocumentElement.h"

class CDESymbolSDLine : public CDocumentElement  
{
public:
	CDESymbolSDLine();
	virtual ~CDESymbolSDLine();

	int m_ix;
	int m_iy;
	int m_ilen;
	ESymbol m_esymbol;


};

#endif // !defined(AFX_DESYMBOLSDLINE_H__1628DEC6_236D_4DA7_83C7_7F1BD70D0F8D__INCLUDED_)
