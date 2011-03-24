#include "StdAfx.h"

/*
BEGIN_MESSAGE_MAP(view, BaseView)
	//{{AFX_MSG_MAP(view)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, BaseView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, BaseView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, BaseView::OnFilePrintPreview)
END_MESSAGE_MAP()

*/

view::view()
{
	// TODO: add construction code here

}

view::~view()
{
}

BOOL view::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return BaseView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// view drawing

void view::_001OnDraw(CDC* pDC)
{
	document* pDoc = get_document();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// view printing

BOOL view::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void view::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void view::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// view diagnostics

#ifdef _DEBUG
void view::AssertValid() const
{
	BaseView::AssertValid();
}

void view::Dump(CDumpContext& dc) const
{
	BaseView::Dump(dc);
}

document* view::get_document() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(document)));
	return (document*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// view message handlers
