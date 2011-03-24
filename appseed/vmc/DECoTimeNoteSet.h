// DECoTimeNoteSet.h: interface for the CDECoTimeNoteSet class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DECOTIMENOTESET_H__8CC35B7D_C3F5_439F_92FC_2586CE8CB785__INCLUDED_)
#define AFX_DECOTIMENOTESET_H__8CC35B7D_C3F5_439F_92FC_2586CE8CB785__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DocumentElement.h"

class CDECoTimeNoteSet :
	public CDocumentElement
{
public:
	CDECoTimeNoteSet();
	virtual ~CDECoTimeNoteSet();

	unsigned char m_uchNoteSet;
	unsigned char m_uchCoTimeNoteSet;
	

};

#endif // !defined(AFX_DECOTIMENOTESET_H__8CC35B7D_C3F5_439F_92FC_2586CE8CB785__INCLUDED_)
