// DENote.h: interface for the CDENote class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DENOTE_H__3FD57558_FBB5_494B_9888_941E558C4563__INCLUDED_)
#define AFX_DENOTE_H__3FD57558_FBB5_494B_9888_941E558C4563__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DocumentElement.h"
#include "MusicNote.h"

class CDENote :
	public CDocumentElement,
	public CMusicNote
{
public:
	CDENote();
	virtual ~CDENote();

	unsigned char m_uchNoteSet;
	unsigned char m_uchCoTimeNoteSet;

};

#endif // !defined(AFX_DENOTE_H__3FD57558_FBB5_494B_9888_941E558C4563__INCLUDED_)
