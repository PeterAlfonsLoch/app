// DocumentEvent.h: interface for the CDocumentEvent class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DOCUMENTEVENT_H__64BEAEAF_31E5_45F4_99FE_B8D0DED88957__INCLUDED_)
#define AFX_DOCUMENTEVENT_H__64BEAEAF_31E5_45F4_99FE_B8D0DED88957__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DocumentElement.h"

class CDocumentEvent :
	public CDocumentElement
{
public:
	CDocumentEvent();
	virtual ~CDocumentEvent();

};

#endif // !defined(AFX_DOCUMENTEVENT_H__64BEAEAF_31E5_45F4_99FE_B8D0DED88957__INCLUDED_)
