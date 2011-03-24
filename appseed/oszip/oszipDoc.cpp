// oszipDoc.cpp : implementation of the COszipDoc class
//

#include "stdafx.h"
#include "oszip.h"
#include "oszipVIew.h"

#include "oszipDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COszipDoc

IMPLEMENT_DYNCREATE(COszipDoc, CDocument)

BEGIN_MESSAGE_MAP(COszipDoc, CDocument)
	//{{AFX_MSG_MAP(COszipDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_SEND_MAIL, OnFileSendMail)
	ON_UPDATE_COMMAND_UI(ID_FILE_SEND_MAIL, OnUpdateFileSendMail)
END_MESSAGE_MAP()


// Note: we add support for IID_IOszip to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {3EF458C1-6DC0-4547-BB02-EB48BDA31E11}
static const IID IID_IOszip =
{ 0x3ef458c1, 0x6dc0, 0x4547, { 0xbb, 0x2, 0xeb, 0x48, 0xbd, 0xa3, 0x1e, 0x11 } };

/////////////////////////////////////////////////////////////////////////////
// COszipDoc construction/destruction

COszipDoc::COszipDoc()
{
	// TODO: add one-time construction code here

	EnableAutomation();

	AfxOleLockApp();
}

COszipDoc::~COszipDoc()
{
	AfxOleUnlockApp();
}

BOOL COszipDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

//	POSITION pos = GetFirstViewPosition();
//	COszipView * pview = (COszipView *) GetNextView(pos);

//	pview->Navigate("http://localhost/zip");

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// COszipDoc serialization

void COszipDoc::Serialize(CArchive& ar)
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
// COszipDoc diagnostics

#ifdef _DEBUG
void COszipDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void COszipDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// COszipDoc commands
