// oszipView.cpp : implementation of the COszipView class
//

#include "stdafx.h"
#include "oszip.h"

#include "oszipDoc.h"
#include "oszipView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COszipView

IMPLEMENT_DYNCREATE(COszipView, CHtmlView)

BEGIN_MESSAGE_MAP(COszipView, CHtmlView)
	//{{AFX_MSG_MAP(COszipView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CHtmlView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CHtmlView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CHtmlView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COszipView construction/destruction

COszipView::COszipView()
{
	// TODO: add construction code here

}

COszipView::~COszipView()
{
}

BOOL COszipView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CHtmlView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// COszipView drawing

void COszipView::OnDraw(CDC* pDC)
{
	COszipDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
//	CListCtrl& refCtrl = GetListCtrl();
	//refCtrl.InsertItem(0, "Item!");
	// TODO: add draw code for native data here
}

void COszipView::OnInitialUpdate()
{
	CHtmlView::OnInitialUpdate();

//	Navigate("http://localhost/oszip");

	// TODO: You may populate your ListView with items by directly accessing
	//  its list control through a call to GetListCtrl().
}

/////////////////////////////////////////////////////////////////////////////
// COszipView printing

BOOL COszipView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void COszipView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void COszipView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// COszipView diagnostics

#ifdef _DEBUG
void COszipView::AssertValid() const
{
	CHtmlView::AssertValid();
}

void COszipView::Dump(CDumpContext& dc) const
{
	CHtmlView::Dump(dc);
}

COszipDoc* COszipView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COszipDoc)));
	return (COszipDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// COszipView message handlers
void COszipView::OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct)
{
	//TODO: add code to react to the user changing the view style of your window
}
