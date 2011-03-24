// DupView.cpp : implementation of the DupView class
//

#include "stdafx.h"
#include "util_dup.h"

#include "DupDoc.h"
#include "DupView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// DupView

IMPLEMENT_DYNCREATE(DupView, CView)

BEGIN_MESSAGE_MAP(DupView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// DupView construction/destruction

DupView::DupView()
{
	// TODO: add construction code here

}

DupView::~DupView()
{
}

BOOL DupView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// DupView drawing

void DupView::OnDraw(CDC* /*pDC*/)
{
	DupDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// DupView printing

BOOL DupView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void DupView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void DupView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// DupView diagnostics

#ifdef _DEBUG
void DupView::AssertValid() const
{
	CView::AssertValid();
}

void DupView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

DupDoc* DupView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(DupDoc)));
	return (DupDoc*)m_pDocument;
}
#endif //_DEBUG


// DupView message handlers

LRESULT DupView::WindowProc(UINT message, WPARAM wparam, LPARAM lparam)
{
   LRESULT lresult;

   if(_vmsgenWindowInterfaceWindowProc(message, wparam, lparam, lresult))
      return lresult;

   return __super::WindowProc(message, wparam, lparam);
}


void DupView::_001InsertColumns()
{
 	Column column;

   int iCount = 0;

   int i;

	column.m_iWidth               = 500;
	column.m_iSubItem             = i;
   //column.m_bIcon                = true;
   column.m_sizeIcon.cx          = 16;
   column.m_sizeIcon.cy          = 16;
   //column.m_iControl             = iControl;
//   column.m_datakey.SetValue(_vms::FILE_MANAGER_ID_FILE_NAME);
   column.m_bEditOnSecondClick   = true;
   //column.m_pil                  = _shell::g_imageset.GetImageList();
	_001AddColumn(column);

}
