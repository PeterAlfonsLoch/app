// vmsnettomidiDoc.cpp : implementation of the CVmsnettomidiDoc class
//

#include "stdafx.h"
#include "vmsnettomidi.h"

#include "vmsnettomidiDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVmsnettomidiDoc

IMPLEMENT_DYNCREATE(CVmsnettomidiDoc, CDocument)

BEGIN_MESSAGE_MAP(CVmsnettomidiDoc, CDocument)
	//{{AFX_MSG_MAP(CVmsnettomidiDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVmsnettomidiDoc construction/destruction

CVmsnettomidiDoc::CVmsnettomidiDoc()
{
	// TODO: add one-time construction code here

}

CVmsnettomidiDoc::~CVmsnettomidiDoc()
{
}

BOOL CVmsnettomidiDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CVmsnettomidiDoc serialization

void CVmsnettomidiDoc::Serialize(CArchive& ar)
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
// CVmsnettomidiDoc diagnostics

#ifdef _DEBUG
void CVmsnettomidiDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CVmsnettomidiDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CVmsnettomidiDoc commands
