// LevelMeterDoc.cpp : implementation file
//

#include "StdAfx.h"
#include "resource.h"
#include "MidiTrackSelectControlInterface.h"
#include "MidiTrackSelectDDX.h"
#include "MidiTrackSelectDoc.h"
#include "MidiTrackSelectViewUpdateHint.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMidiTrackSelectDoc

IMPLEMENT_DYNCREATE(CMidiTrackSelectDoc, CDocument)

CMidiTrackSelectDoc::CMidiTrackSelectDoc()
{
}

BOOL CMidiTrackSelectDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

CMidiTrackSelectDoc::~CMidiTrackSelectDoc()
{
}


BEGIN_MESSAGE_MAP(CMidiTrackSelectDoc, CDocument)
	//{{AFX_MSG_MAP(CMidiTrackSelectDoc)
	ON_COMMAND(ID_APPLY, OnApply)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMidiTrackSelectDoc diagnostics

#ifdef _DEBUG
void CMidiTrackSelectDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMidiTrackSelectDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMidiTrackSelectDoc serialization

void CMidiTrackSelectDoc::Serialize(CArchive& ar)
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
// CMidiTrackSelectDoc commands

bool CMidiTrackSelectDoc::Initialize(MidiSequence *pmidisequence, bool bEnable)
{
   
   CMidiTrackSelectViewUpdateHint uh;

   uh.SetType(CMidiTrackSelectViewUpdateHint::TypeInitialize);
   uh.m_pmidisequence = pmidisequence;


   UpdateAllViews(NULL, 0, &uh);

   return uh.m_bResult;
}

void CMidiTrackSelectDoc::OnApply() 
{
   m_pddx->m_pcontrol->OnTrackSelectApply();	
}
