// DupDoc.cpp : implementation of the DupDoc class
//

#include "stdafx.h"
#include "util_dup.h"

#include "DupDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// DupDoc

IMPLEMENT_DYNCREATE(DupDoc, CDocument)

BEGIN_MESSAGE_MAP(DupDoc, CDocument)
END_MESSAGE_MAP()


// DupDoc construction/destruction

DupDoc::DupDoc()
{
	// TODO: add one-time construction code here

}

DupDoc::~DupDoc()
{
}

BOOL DupDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// DupDoc serialization

void DupDoc::Serialize(CArchive& ar)
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


// DupDoc diagnostics

#ifdef _DEBUG
void DupDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void DupDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// DupDoc commands
