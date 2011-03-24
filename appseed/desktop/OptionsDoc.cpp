// OptionsDoc.cpp : implementation file
//

#include "stdafx.h"
#include "OptionsDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// OptionsDoc

IMPLEMENT_DYNCREATE(OptionsDoc, Document)

OptionsDoc::OptionsDoc()
{
}

BOOL OptionsDoc::OnNewDocument()
{
	if (!Document::OnNewDocument())
		return FALSE;
	return TRUE;
}

OptionsDoc::~OptionsDoc()
{
}


BEGIN_MESSAGE_MAP(OptionsDoc, Document)
	//{{AFX_MSG_MAP(OptionsDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// OptionsDoc diagnostics

#ifdef _DEBUG
void OptionsDoc::AssertValid() const
{
	Document::AssertValid();
}

void OptionsDoc::Dump(CDumpContext& dc) const
{
	Document::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// OptionsDoc serialization

void OptionsDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// OptionsDoc commands
