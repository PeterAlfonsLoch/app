// VmsTextView.cpp : implementation file
//

#include "stdafx.h"
//#include "vmsp.h"
#include "VmsTextView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVmsTextView

IMPLEMENT_DYNCREATE(CVmsTextView, CRichEditView)

CVmsTextView::CVmsTextView()
{
}

CVmsTextView::~CVmsTextView()
{
}


BEGIN_MESSAGE_MAP(CVmsTextView, CRichEditView)
	//{{AFX_MSG_MAP(CVmsTextView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVmsTextView drawing

void CVmsTextView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CVmsTextView diagnostics

#ifdef _DEBUG
void CVmsTextView::AssertValid() const
{
	CView::AssertValid();
}

void CVmsTextView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CVmsTextView message handlers
