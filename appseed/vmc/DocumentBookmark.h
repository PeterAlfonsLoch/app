// DocumentBookmark.h: interface for the CDocumentBookmark class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DOCUMENTBOOKMARK_H__20CBBC13_5649_4E01_A7D2_1A8695C79759__INCLUDED_)
#define AFX_DOCUMENTBOOKMARK_H__20CBBC13_5649_4E01_A7D2_1A8695C79759__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DocumentElement.h"

class CDocumentBookmark : public CDocumentElement  
{
public:
	// A graphic here is considered an graphical element
	// other than a musical graphic element.
	//
	// In a score without graphics, the document starts
	// with a :CDocumentBookmark of type Measure.
	//
	// Following this "Measure Bookmark", optionally it 
	// can be placed the following objects in the
	// specified order:
	//
	//		:CStaff
	//		:CClef
	//		:CKeySignature
	//		:CTimeSignature
	//
	// If a :CStaff is specified, also :CCLef,
	// :CKeySignature and :CTimeSignature must be
	// placed in the specified order.
	//
	// After that optional objects, a
	// :CDocumentBookmark of type CoTime, must be
	// placed as a placeholder if there are musical
	// graphical elements in the measure.
	// A "CoTime Bookmark" is a placeholder for
	// simultaneous musical graphical elements.
	// For each non-simultaneous graphical element
	// it should be used a "CoTime Bookmark".

	enum EType
	{
		Measure, 
		CoTime,
		Graphic,
		User
	};
	CDocumentBookmark();
	virtual ~CDocumentBookmark();

	EType m_etype;
	TICKS  m_iDelta;

};

#endif // !defined(AFX_DOCUMENTBOOKMARK_H__20CBBC13_5649_4E01_A7D2_1A8695C79759__INCLUDED_)
