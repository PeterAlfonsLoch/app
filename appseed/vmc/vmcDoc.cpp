// vmcDoc.cpp : implementation of the CVmcDoc class
//

#include "stdafx.h"
#include "vmcApp.h"

#include "vmcDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVmcDoc

/*BEGIN_MESSAGE_MAP(CVmcDoc, Document)
	//{{AFX_MSG_MAP(CVmcDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Enable default OLE container implementation
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, Document::OnUpdatePasteMenu)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE_LINK, Document::OnUpdatePasteLinkMenu)
	ON_UPDATE_COMMAND_UI(ID_OLE_EDIT_CONVERT, Document::OnUpdateObjectVerbMenu)
	ON_COMMAND(ID_OLE_EDIT_CONVERT, Document::OnEditConvert)
	ON_UPDATE_COMMAND_UI(ID_OLE_EDIT_LINKS, Document::OnUpdateEditLinksMenu)
	ON_COMMAND(ID_OLE_EDIT_LINKS, Document::OnEditLinks)
	ON_UPDATE_COMMAND_UI_RANGE(ID_OLE_VERB_FIRST, ID_OLE_VERB_LAST, Document::OnUpdateObjectVerbMenu)
	ON_COMMAND(ID_FILE_SEND_MAIL, OnFileSendMail)
	ON_UPDATE_COMMAND_UI(ID_FILE_SEND_MAIL, OnUpdateFileSendMail)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CVmcDoc, Document)
	//{{AFX_DISPATCH_MAP(CVmcDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//      DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()
*/
// Note: we add support for IID_IVmc to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {B0E4904B-9E0B-44CF-AA7A-88225EC70B8C}
/*static const IID IID_IVmc =
{ 0xb0e4904b, 0x9e0b, 0x44cf, { 0xaa, 0x7a, 0x88, 0x22, 0x5e, 0xc7, 0xb, 0x8c } };

BEGIN_INTERFACE_MAP(CVmcDoc, Document)
	INTERFACE_PART(CVmcDoc, IID_IVmc, Dispatch)
END_INTERFACE_MAP()
*/
/////////////////////////////////////////////////////////////////////////////
// CVmcDoc construction/destruction

CVmcDoc::CVmcDoc(::ca::application * papp)
{
}

CVmcDoc::~CVmcDoc()
{
}

BOOL CVmcDoc::OnNewDocument()
{
	if (!Document::OnNewDocument())
		return FALSE;
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CVmcDoc diagnostics

#ifdef _DEBUG
void CVmcDoc::AssertValid() const
{
	Document::AssertValid();
}

void CVmcDoc::Dump(CDumpContext& dc) const
{
	Document::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CVmcDoc commands
