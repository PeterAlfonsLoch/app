// vmeDoc.cpp : implementation of the CVmeDoc class
//

#include "stdafx.h"
#include "VmeApp.h"

#include "vmeDoc.h"
#include "CntrItem.h"
#include "SrvrItem.h"

#include "MidiFile.h"
#include "MidiSequence.h"
#include "MidiTracks.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVmeDoc

IMPLEMENT_DYNCREATE(CVmeDoc, COleServerDoc)

BEGIN_MESSAGE_MAP(CVmeDoc, COleServerDoc)
	//{{AFX_MSG_MAP(CVmeDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Enable default OLE container implementation
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, COleServerDoc::OnUpdatePasteMenu)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE_LINK, COleServerDoc::OnUpdatePasteLinkMenu)
	ON_UPDATE_COMMAND_UI(ID_OLE_EDIT_CONVERT, COleServerDoc::OnUpdateObjectVerbMenu)
	ON_COMMAND(ID_OLE_EDIT_CONVERT, COleServerDoc::OnEditConvert)
	ON_UPDATE_COMMAND_UI(ID_OLE_EDIT_LINKS, COleServerDoc::OnUpdateEditLinksMenu)
	ON_COMMAND(ID_OLE_EDIT_LINKS, COleServerDoc::OnEditLinks)
	ON_UPDATE_COMMAND_UI_RANGE(ID_OLE_VERB_FIRST, ID_OLE_VERB_LAST, COleServerDoc::OnUpdateObjectVerbMenu)
	ON_COMMAND(ID_FILE_SEND_MAIL, OnFileSendMail)
	ON_UPDATE_COMMAND_UI(ID_FILE_SEND_MAIL, OnUpdateFileSendMail)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CVmeDoc, COleServerDoc)
	//{{AFX_DISPATCH_MAP(CVmeDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//      DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IVme to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {0522F639-F013-4637-86D8-8614B3EE770B}
static const IID IID_IVme =
{ 0x522f639, 0xf013, 0x4637, { 0x86, 0xd8, 0x86, 0x14, 0xb3, 0xee, 0x77, 0xb } };

BEGIN_INTERFACE_MAP(CVmeDoc, COleServerDoc)
	INTERFACE_PART(CVmeDoc, IID_IVme, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVmeDoc construction/destruction

CVmeDoc::CVmeDoc()
{
	// Use OLE compound files
	EnableCompoundFile();

	// TODO: add one-time construction code here

	EnableAutomation();

	AfxOleLockApp();
}

CVmeDoc::~CVmeDoc()
{
	AfxOleUnlockApp();
}

BOOL CVmeDoc::OnNewDocument()
{
	if (!COleServerDoc::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CVmeDoc server implementation

COleServerItem* CVmeDoc::OnGetEmbeddedItem()
{
	// OnGetEmbeddedItem is called by the framework to get the COleServerItem
	//  that is associated with the document.  It is only called when necessary.

	CVmeSrvrItem* pItem = new CVmeSrvrItem(this);
	ASSERT_VALID(pItem);
	return pItem;
}

/////////////////////////////////////////////////////////////////////////////
// CVmeDoc Active Document server implementation

CDocObjectServer *CVmeDoc::GetDocObjectServer(LPOLEDOCUMENTSITE pDocSite)
{
	return new CDocObjectServer(this, pDocSite);
}



/////////////////////////////////////////////////////////////////////////////
// CVmeDoc serialization

void CVmeDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
        HelperGetMidiSequence()->SaveFile(ar);
		// TODO: add storing code here
	}
	else
	{
        HelperGetMidiSequence()->OpenFile(ar, CMidiFile::OpenForPlaying);
		// TODO: add loading code here
	}

	// Calling the base class COleServerDoc enables serialization
	//  of the container document's COleClientItem objects.
//	COleServerDoc::Serialize(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CVmeDoc diagnostics

#ifdef _DEBUG
void CVmeDoc::AssertValid() const
{
	COleServerDoc::AssertValid();
}

void CVmeDoc::Dump(CDumpContext& dc) const
{
	COleServerDoc::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CVmeDoc commands

void CVmeDoc::DeleteContents() 
{
	// TODO: Add your specialized code here and/or call the base class
    HelperDeleteContents();
	COleServerDoc::DeleteContents();
}

BOOL CVmeDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
//	if (!COleServerDoc::OnOpenDocument(lpszPathName))
//		return FALSE;

	if (!HelperOnOpenDocument(lpszPathName))
		return FALSE;

    CMidiFile * pMidiFile = HelperGetMidiSequence()->GetFile();
    pMidiFile->m_ptracks->ExpandTrack(0);
    pMidiFile->ToWorkStorage();

	// TODO: Add your specialized creation code here
	
	return TRUE;
}
