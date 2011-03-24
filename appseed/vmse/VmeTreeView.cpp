// VmeTreeView.cpp : implementation of the CVmeTreeView class
//

#include "stdafx.h"
#include "VmeApp.h"

#include "vmeDoc.h"
#include "VmeTreeView.h"
#include "VmeViewUpdateHint.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVmeTreeView

IMPLEMENT_DYNCREATE(CVmeTreeView, CTreeView)

BEGIN_MESSAGE_MAP(CVmeTreeView, CTreeView)
	//{{AFX_MSG_MAP(CVmeTreeView)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, OnSelchanged)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CTreeView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CTreeView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CTreeView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVmeTreeView construction/destruction

CVmeTreeView::CVmeTreeView()
{
	// TODO: add construction code here

}

CVmeTreeView::~CVmeTreeView()
{
}

BOOL CVmeTreeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CTreeView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CVmeTreeView drawing

void CVmeTreeView::OnDraw(CDC* pDC)
{
	CVmeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}


/////////////////////////////////////////////////////////////////////////////
// CVmeTreeView printing

BOOL CVmeTreeView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CVmeTreeView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CVmeTreeView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CVmeTreeView::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();

    m_tree.hMidiTracksEvents = GetTreeCtrl().InsertItem("Trilhas de Eventos MIDI", 0);
    GetTreeCtrl().InsertItem("Dummy", 0);
	// TODO: You may populate your TreeView with items by directly accessing
	//  its tree control through a call to GetTreeCtrl().
}

/////////////////////////////////////////////////////////////////////////////
// CVmeTreeView diagnostics

#ifdef _DEBUG
void CVmeTreeView::AssertValid() const
{
	CTreeView::AssertValid();
}

void CVmeTreeView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}

CVmeDoc* CVmeTreeView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CVmeDoc)));
	return (CVmeDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CVmeTreeView message handlers

void CVmeTreeView::OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	HTREEITEM hitem = pNMTreeView->itemNew.hItem;
    CVmeViewUpdateHint hint;
    hint.m_iType = 0;
    hint.m_htreeitem = hitem;
    GetDocument()->UpdateAllViews(this,  0, &hint);
	*pResult = 0;
}
