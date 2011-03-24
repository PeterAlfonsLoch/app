// filerenDoc.cpp : implementation of the CFilerenDoc class
//

#include "stdafx.h"
#include "fileren.h"

#include "filerenDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFilerenDoc

IMPLEMENT_DYNCREATE(CFilerenDoc, CDocument)

BEGIN_MESSAGE_MAP(CFilerenDoc, CDocument)
	//{{AFX_MSG_MAP(CFilerenDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFilerenDoc construction/destruction

CFilerenDoc::CFilerenDoc()
{
	// TODO: add one-time construction code here

}

CFilerenDoc::~CFilerenDoc()
{
}

BOOL CFilerenDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CFilerenDoc serialization

void CFilerenDoc::Serialize(CArchive& ar)
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
// CFilerenDoc diagnostics

#ifdef _DEBUG
void CFilerenDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CFilerenDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFilerenDoc commands
