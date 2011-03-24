// vmcView.cpp : implementation of the CVmcView class
//

#include "stdafx.h"
#include "../vmsp/resource.h"
#include "vmcApp.h"

#include "vmcDoc.h"
#include "vmcView.h"

/*
BEGIN_MESSAGE_MAP(CVmcView, BaseView)
	//{{AFX_MSG_MAP(CVmcView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	ON_WM_DESTROY()
	ON_WM_SETFOCUS()
	ON_WM_SIZE()
	ON_COMMAND(ID_OLE_INSERT_NEW, OnInsertObject)
	ON_COMMAND(ID_CANCEL_EDIT_CNTR, OnCancelEditCntr)
	ON_COMMAND(ID_CANCEL_EDIT_SRVR, OnCancelEditSrvr)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, BaseView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, BaseView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, BaseView::OnFilePrintPreview)
END_MESSAGE_MAP()
*/

/////////////////////////////////////////////////////////////////////////////
// CVmcView construction/destruction

CVmcView::CVmcView(::ca::application * papp)
{
}

CVmcView::~CVmcView()
{
}

BOOL CVmcView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return BaseView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CVmcView drawing

void CVmcView::OnDraw(CDC* pDC)
{
	CVmcDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

void CVmcView::OnInitialUpdate()
{
	BaseView::OnInitialUpdate();


	
}

/////////////////////////////////////////////////////////////////////////////
// CVmcView printing

BOOL CVmcView::OnPreparePrinting(CPrintInfo* pInfo)
{
	if (!BaseView::DoPreparePrinting(pInfo))
		return FALSE;
	
	return TRUE;
}

void CVmcView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CVmcView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CVmcView::OnPrint(CDC* pDC, CPrintInfo* pInfo)
{
}

void CVmcView::OnDestroy()
{
}



void CVmcView::OnSize(UINT nType, int cx, int cy)
{
	BaseView::OnSize(nType, cx, cy);
}


#ifdef _DEBUG
void CVmcView::AssertValid() const
{
	BaseView::AssertValid();
}

void CVmcView::Dump(CDumpContext& dc) const
{
	BaseView::Dump(dc);
}

CVmcDoc* CVmcView::GetDocument() // non-debug version is inline
{
   ASSERT(base < CVmcDoc > ::bases(m_pDocument));
	return (CVmcDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CVmcView message handlers
