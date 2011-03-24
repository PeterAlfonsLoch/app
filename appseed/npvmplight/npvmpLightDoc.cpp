// npvmpDoc.cpp : implementation of the CNpvmpDoc class
//

#include "stdafx.h"
#include "npvmpLight.h"

#include "npvmpLightDoc.h"
#include "npvmpLightCntrItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNpvmpDoc

IMPLEMENT_DYNCREATE(CNpvmpDoc, COleDocument)

BEGIN_MESSAGE_MAP(CNpvmpDoc, COleDocument)
	//{{AFX_MSG_MAP(CNpvmpDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Enable default OLE container implementation
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, COleDocument::OnUpdatePasteMenu)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE_LINK, COleDocument::OnUpdatePasteLinkMenu)
	ON_UPDATE_COMMAND_UI(ID_OLE_EDIT_CONVERT, COleDocument::OnUpdateObjectVerbMenu)
	ON_COMMAND(ID_OLE_EDIT_CONVERT, COleDocument::OnEditConvert)
	ON_UPDATE_COMMAND_UI(ID_OLE_EDIT_LINKS, COleDocument::OnUpdateEditLinksMenu)
	ON_COMMAND(ID_OLE_EDIT_LINKS, COleDocument::OnEditLinks)
	ON_UPDATE_COMMAND_UI_RANGE(ID_OLE_VERB_FIRST, ID_OLE_VERB_LAST, COleDocument::OnUpdateObjectVerbMenu)
	ON_COMMAND(ID_FILE_SEND_MAIL, OnFileSendMail)
	ON_UPDATE_COMMAND_UI(ID_FILE_SEND_MAIL, OnUpdateFileSendMail)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CNpvmpDoc, COleDocument)
	//{{AFX_DISPATCH_MAP(CNpvmpDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//      DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_INpvmp to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {AB8B0BED-B5EB-479A-A479-B35ED41FE038}
static const IID IID_INpvmp =
{ 0xab8b0bed, 0xb5eb, 0x479a, { 0xa4, 0x79, 0xb3, 0x5e, 0xd4, 0x1f, 0xe0, 0x38 } };

BEGIN_INTERFACE_MAP(CNpvmpDoc, COleDocument)
	INTERFACE_PART(CNpvmpDoc, IID_INpvmp, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNpvmpDoc construction/destruction

CNpvmpDoc::CNpvmpDoc()
{
	// Use OLE compound files
	EnableCompoundFile();

	// TODO: add one-time construction code here

	EnableAutomation();

	AfxOleLockApp();
}

CNpvmpDoc::~CNpvmpDoc()
{
	AfxOleUnlockApp();
}

BOOL CNpvmpDoc::OnNewDocument()
{
	if (!COleDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CNpvmpDoc serialization

void CNpvmpDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}

	// Calling the base class COleDocument enables serialization
	//  of the container document's COleClientItem objects.
	COleDocument::Serialize(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CNpvmpDoc diagnostics

#ifdef _DEBUG
void CNpvmpDoc::AssertValid() const
{
	COleDocument::AssertValid();
}

void CNpvmpDoc::Dump(CDumpContext& dc) const
{
	COleDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CNpvmpDoc commands
