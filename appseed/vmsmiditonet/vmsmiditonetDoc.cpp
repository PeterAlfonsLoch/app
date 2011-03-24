// vmsmiditonetDoc.cpp : implementation of the CVmsmiditonetDoc class
//

#include "stdafx.h"
#include "vmsmiditonet.h"

#include "vmsmiditonetDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVmsmiditonetDoc

IMPLEMENT_DYNCREATE(CVmsmiditonetDoc, CDocument)

BEGIN_MESSAGE_MAP(CVmsmiditonetDoc, CDocument)
	//{{AFX_MSG_MAP(CVmsmiditonetDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVmsmiditonetDoc construction/destruction

CVmsmiditonetDoc::CVmsmiditonetDoc()
{
	// TODO: add one-time construction code here

}

CVmsmiditonetDoc::~CVmsmiditonetDoc()
{
}

BOOL CVmsmiditonetDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CVmsmiditonetDoc serialization

void CVmsmiditonetDoc::Serialize(CArchive& ar)
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
// CVmsmiditonetDoc diagnostics

#ifdef _DEBUG
void CVmsmiditonetDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CVmsmiditonetDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CVmsmiditonetDoc commands
