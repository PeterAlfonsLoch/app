// fontblurDoc.cpp : implementation of the CFontblurDoc class
//

#include "stdafx.h"
#include "fontblur.h"

#include "fontblurDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFontblurDoc

IMPLEMENT_DYNCREATE(CFontblurDoc, CDocument)

BEGIN_MESSAGE_MAP(CFontblurDoc, CDocument)
	//{{AFX_MSG_MAP(CFontblurDoc)
	ON_COMMAND(ID_VERSION1, OnVersion1)
	ON_COMMAND(ID_VERSION2, OnVersion2)
	ON_COMMAND(ID_VERSION3, OnVersion3)
	ON_UPDATE_COMMAND_UI(ID_VERSION1, OnUpdateVersion1)
	ON_UPDATE_COMMAND_UI(ID_VERSION2, OnUpdateVersion2)
	ON_UPDATE_COMMAND_UI(ID_VERSION3, OnUpdateVersion3)
	ON_COMMAND(ID_VERSION4, OnVersion4)
	ON_UPDATE_COMMAND_UI(ID_VERSION4, OnUpdateVersion4)
	ON_COMMAND(ID_VERSION5, OnVersion5)
	ON_UPDATE_COMMAND_UI(ID_VERSION5, OnUpdateVersion5)
	ON_COMMAND(ID_VERSION6, OnVersion6)
	ON_UPDATE_COMMAND_UI(ID_VERSION6, OnUpdateVersion6)
	ON_COMMAND(ID_VERSION7, OnVersion7)
	ON_UPDATE_COMMAND_UI(ID_VERSION7, OnUpdateVersion7)
	ON_COMMAND(ID_VERSION8, OnVersion8)
	ON_UPDATE_COMMAND_UI(ID_VERSION8, OnUpdateVersion8)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFontblurDoc construction/destruction

CFontblurDoc::CFontblurDoc()
{
	// TODO: add one-time construction code here
   m_iVersion = 0;
}

CFontblurDoc::~CFontblurDoc()
{
}

BOOL CFontblurDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CFontblurDoc serialization

void CFontblurDoc::Serialize(CArchive& ar)
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
// CFontblurDoc diagnostics

#ifdef _DEBUG
void CFontblurDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CFontblurDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFontblurDoc commands

int CFontblurDoc::GetVersion()
{
   return m_iVersion;
}

void CFontblurDoc::OnVersion1() 
{
	m_iVersion = 0;
   UpdateAllViews(NULL);
}

void CFontblurDoc::OnVersion2() 
{
	m_iVersion = 1;
   UpdateAllViews(NULL);
}

void CFontblurDoc::OnVersion3() 
{
	m_iVersion = 2;
   UpdateAllViews(NULL);
}

void CFontblurDoc::OnUpdateVersion1(CCmdUI* pCmdUI) 
{
   pCmdUI->SetCheck(m_iVersion == 0);
   pCmdUI->Enable(m_iVersion != 0);
}

void CFontblurDoc::OnUpdateVersion2(CCmdUI* pCmdUI) 
{
   pCmdUI->SetCheck(m_iVersion == 1);
   pCmdUI->Enable(m_iVersion != 1);
}

void CFontblurDoc::OnUpdateVersion3(CCmdUI* pCmdUI) 
{
   pCmdUI->SetCheck(m_iVersion == 2);	
   pCmdUI->Enable(m_iVersion != 2);
}

void CFontblurDoc::OnVersion4() 
{
	m_iVersion = 3;
   UpdateAllViews(NULL);
}

void CFontblurDoc::OnUpdateVersion4(CCmdUI* pCmdUI) 
{
   pCmdUI->SetCheck(m_iVersion == 3);	
   pCmdUI->Enable(m_iVersion != 3);
}

void CFontblurDoc::OnVersion5() 
{
	m_iVersion = 4;
   UpdateAllViews(NULL);
}

void CFontblurDoc::OnUpdateVersion5(CCmdUI* pCmdUI) 
{
   pCmdUI->SetCheck(m_iVersion == 4);	
   pCmdUI->Enable(m_iVersion != 4);
}

void CFontblurDoc::OnVersion6() 
{
	m_iVersion = 5;
   UpdateAllViews(NULL);
}

void CFontblurDoc::OnUpdateVersion6(CCmdUI* pCmdUI) 
{
   pCmdUI->SetCheck(m_iVersion == 5);	
   pCmdUI->Enable(m_iVersion != 5);
}

void CFontblurDoc::OnVersion7() 
{
	m_iVersion = 6;
   UpdateAllViews(NULL);
}

void CFontblurDoc::OnUpdateVersion7(CCmdUI* pCmdUI) 
{
   pCmdUI->SetCheck(m_iVersion == 6);	
   pCmdUI->Enable(m_iVersion != 6);
}

void CFontblurDoc::OnVersion8() 
{
	m_iVersion = 7;
   UpdateAllViews(NULL);
}

void CFontblurDoc::OnUpdateVersion8(CCmdUI* pCmdUI) 
{
   pCmdUI->SetCheck(m_iVersion == 7);	
   pCmdUI->Enable(m_iVersion != 7);
}
