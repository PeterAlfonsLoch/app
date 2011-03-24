// vmsmiditonetView.cpp : implementation of the CVmsmiditonetView class
//

#include "stdafx.h"
#include "vmsmiditonet.h"

#include "vmsmiditonetDoc.h"
#include "vmsmiditonetView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVmsmiditonetView

IMPLEMENT_DYNCREATE(CVmsmiditonetView, CView)

BEGIN_MESSAGE_MAP(CVmsmiditonetView, CView)
	//{{AFX_MSG_MAP(CVmsmiditonetView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVmsmiditonetView construction/destruction

CVmsmiditonetView::CVmsmiditonetView()
{
	// TODO: add construction code here

}

CVmsmiditonetView::~CVmsmiditonetView()
{
}

BOOL CVmsmiditonetView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CVmsmiditonetView drawing

void CVmsmiditonetView::OnDraw(CDC* pDC)
{
	CVmsmiditonetDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CVmsmiditonetView printing

BOOL CVmsmiditonetView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CVmsmiditonetView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CVmsmiditonetView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CVmsmiditonetView diagnostics

#ifdef _DEBUG
void CVmsmiditonetView::AssertValid() const
{
	CView::AssertValid();
}

void CVmsmiditonetView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CVmsmiditonetDoc* CVmsmiditonetView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CVmsmiditonetDoc)));
	return (CVmsmiditonetDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CVmsmiditonetView message handlers

void CVmsmiditonetView::Go()
{

}

void CVmsmiditonetView::Stop()
{

}
