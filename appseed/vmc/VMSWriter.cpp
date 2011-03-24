// VMSWriter.cpp : implementation file
//

#include "stdafx.h"
#include "VmcApp.h"
#include "VMSWriter.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVMSWriter

//IMPLEMENT_DYNCREATE(CVMSWriter, Document)

CVMSWriter::CVMSWriter(::ca::application * papp) :
   ::ca::ca(papp)
{
}

BOOL CVMSWriter::OnNewDocument()
{
	if (!Document::OnNewDocument())
		return FALSE;
	return TRUE;
}

CVMSWriter::~CVMSWriter()
{
}

/*
BEGIN_MESSAGE_MAP(CVMSWriter, Document)
	//{{AFX_MSG_MAP(CVMSWriter)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/
/////////////////////////////////////////////////////////////////////////////
// CVMSWriter diagnostics

#ifdef _DEBUG
void CVMSWriter::AssertValid() const
{
	Document::AssertValid();
}

void CVMSWriter::Dump(CDumpContext& dc) const
{
	Document::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CVMSWriter serialization

void CVMSWriter::Serialize(Ex1Archive& ar)
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
// CVMSWriter commands
