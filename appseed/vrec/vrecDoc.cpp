// vrecDoc.cpp : implementation of the VRecDocument class
//

#include "stdafx.h"
#include "vrec.h"

#include "vrecDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// VRecDocument

IMPLEMENT_DYNCREATE(VRecDocument, Document)

BEGIN_MESSAGE_MAP(VRecDocument, Document)
	//{{AFX_MSG_MAP(VRecDocument)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// VRecDocument construction/destruction

VRecDocument::VRecDocument()
{
	// TODO: add one-time construction code here

}

VRecDocument::~VRecDocument()
{
}

BOOL VRecDocument::OnNewDocument()
{
	if (!Document::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// VRecDocument serialization

void VRecDocument::Serialize(CArchive& ar)
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
// VRecDocument diagnostics

#ifdef _DEBUG
void VRecDocument::AssertValid() const
{
	Document::AssertValid();
}

void VRecDocument::Dump(CDumpContext& dc) const
{
	Document::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// VRecDocument commands
