// cynceappDoc.cpp : implementation of the CcynceappDoc class
//

#include "stdafx.h"
#include "cynceapp.h"

#include "cynceappDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CcynceappDoc

IMPLEMENT_DYNCREATE(CcynceappDoc, CDocument)

BEGIN_MESSAGE_MAP(CcynceappDoc, CDocument)
	ON_COMMAND(ID_FILE_SEND_MAIL, &CcynceappDoc::OnFileSendMail)
	ON_UPDATE_COMMAND_UI(ID_FILE_SEND_MAIL, &CcynceappDoc::OnUpdateFileSendMail)
END_MESSAGE_MAP()


// CcynceappDoc construction/destruction

CcynceappDoc::CcynceappDoc()
{
	// TODO: add one-time construction code here

}

CcynceappDoc::~CcynceappDoc()
{
}

BOOL CcynceappDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CcynceappDoc serialization

void CcynceappDoc::Serialize(CArchive& ar)
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


// CcynceappDoc diagnostics

#ifdef _DEBUG
void CcynceappDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CcynceappDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CcynceappDoc commands
