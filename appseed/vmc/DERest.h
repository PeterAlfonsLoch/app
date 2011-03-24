// DERest.h: interface for the CDERest class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DEREST_H__CE604766_FCAF_4111_A64B_063879C0E0B9__INCLUDED_)
#define AFX_DEREST_H__CE604766_FCAF_4111_A64B_063879C0E0B9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DocumentElement.h"
#include "MusicRest.h"

class CDERest :
	public CDocumentElement,
	public CMusicRest
{
public:
	CDERest();
	virtual ~CDERest();

};

#endif // !defined(AFX_DEREST_H__CE604766_FCAF_4111_A64B_063879C0E0B9__INCLUDED_)
