// vmsaudioprofileDoc.cpp : implementation of the AudioProfileDoc class
//

#include "stdafx.h"
#include "vmsaudioprofile.h"

#include "vmsaudioprofileDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// AudioProfileDoc

IMPLEMENT_DYNCREATE(AudioProfileDoc, CDocument)

BEGIN_MESSAGE_MAP(AudioProfileDoc, CDocument)
	//{{AFX_MSG_MAP(AudioProfileDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_SEND_MAIL, OnFileSendMail)
	ON_UPDATE_COMMAND_UI(ID_FILE_SEND_MAIL, OnUpdateFileSendMail)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(AudioProfileDoc, CDocument)
	//{{AFX_DISPATCH_MAP(AudioProfileDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//      DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IVmsaudioprofile to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {AF1C4FE5-B6F9-4DF5-A803-CD5E370B9A8A}
static const IID IID_IVmsaudioprofile =
{ 0xaf1c4fe5, 0xb6f9, 0x4df5, { 0xa8, 0x3, 0xcd, 0x5e, 0x37, 0xb, 0x9a, 0x8a } };

BEGIN_INTERFACE_MAP(AudioProfileDoc, CDocument)
	INTERFACE_PART(AudioProfileDoc, IID_IVmsaudioprofile, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// AudioProfileDoc construction/destruction

AudioProfileDoc::AudioProfileDoc()
{
	// TODO: add one-time construction code here

	EnableAutomation();

	AfxOleLockApp();
}

AudioProfileDoc::~AudioProfileDoc()
{
	AfxOleUnlockApp();
}

BOOL AudioProfileDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// AudioProfileDoc serialization

void AudioProfileDoc::Serialize(CArchive& ar)
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
// AudioProfileDoc diagnostics

#ifdef _DEBUG
void AudioProfileDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void AudioProfileDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// AudioProfileDoc commands
