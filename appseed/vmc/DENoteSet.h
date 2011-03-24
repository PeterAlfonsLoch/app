// DENoteSet.h: interface for the CDENoteSet class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DENOTESET_H__16C01E75_BA22_45B7_A1E9_FDE5448FF9F4__INCLUDED_)
#define AFX_DENOTESET_H__16C01E75_BA22_45B7_A1E9_FDE5448FF9F4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DocumentElement.h"

class CDENoteSet : public CDocumentElement  
{
public:
	CDENoteSet();
	virtual ~CDENoteSet();

	unsigned char m_uchNoteSet;

};

#endif // !defined(AFX_DENOTESET_H__16C01E75_BA22_45B7_A1E9_FDE5448FF9F4__INCLUDED_)
