// audiogenDoc.cpp : implementation of the CAudiogenDoc class
//

#include "stdafx.h"

#include "audiogenDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAudiogenDoc

IMPLEMENT_DYNCREATE(CAudiogenDoc, CDocument)

BEGIN_MESSAGE_MAP(CAudiogenDoc, CDocument)
	//{{AFX_MSG_MAP(CAudiogenDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAudiogenDoc construction/destruction

CAudiogenDoc::CAudiogenDoc()
{
	// TODO: add one-time construction code here

}

CAudiogenDoc::~CAudiogenDoc()
{
}

BOOL CAudiogenDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CAudiogenDoc serialization

void CAudiogenDoc::Serialize(CArchive& ar)
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
// CAudiogenDoc diagnostics

#ifdef _DEBUG
void CAudiogenDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CAudiogenDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAudiogenDoc commands
