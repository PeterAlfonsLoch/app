// mk1expanderView.cpp : implementation of the CMk1expanderView class
//

#include "stdafx.h"
#include "mk1expander.h"

#include "mk1expanderDoc.h"
#include "mk1expanderView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMk1expanderView

IMPLEMENT_DYNCREATE(CMk1expanderView, CView)

BEGIN_MESSAGE_MAP(CMk1expanderView, CView)
	//{{AFX_MSG_MAP(CMk1expanderView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMk1expanderView construction/destruction

CMk1expanderView::CMk1expanderView()
{
	// TODO: add construction code here

}

CMk1expanderView::~CMk1expanderView()
{
}

BOOL CMk1expanderView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMk1expanderView drawing

void CMk1expanderView::OnDraw(CDC* pDC)
{
	CMk1expanderDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CMk1expanderView printing

BOOL CMk1expanderView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMk1expanderView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMk1expanderView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMk1expanderView diagnostics

#ifdef _DEBUG
void CMk1expanderView::AssertValid() const
{
	CView::AssertValid();
}

void CMk1expanderView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMk1expanderDoc* CMk1expanderView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMk1expanderDoc)));
	return (CMk1expanderDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMk1expanderView message handlers
