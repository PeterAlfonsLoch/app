#include "stdafx.h"
#include "StaffView.h"


//IMPLEMENT_DYNCREATE(CStaffView, BaseScrollView)

CStaffView::CStaffView(::ca::application * papp) :
   ::ca::ca(papp),
   Ex1VirtualGuieInterface(papp),
   BaseVirtualGuie(papp),
   Ex1ScrollViewInterface(papp),
   BaseScrollView(papp)
{
}

CStaffView::~CStaffView()
{
}

/*
BEGIN_MESSAGE_MAP(CStaffView, BaseScrollView)
	//{{AFX_MSG_MAP(CStaffView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/

/////////////////////////////////////////////////////////////////////////////
// CStaffView drawing

void CStaffView::OnInitialUpdate()
{
	BaseScrollView::OnInitialUpdate();

	class size sizeTotal;
	// TODO: calculate the total size of this view
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
}

void CStaffView::OnDraw(CDC* pDC)
{
}
/////////////////////////////////////////////////////////////////////////////
// CStaffView diagnostics

#ifdef _DEBUG
void CStaffView::AssertValid() const
{
	BaseScrollView::AssertValid();
}

void CStaffView::Dump(CDumpContext& dc) const
{
	BaseScrollView::Dump(dc);
}
#endif //_DEBUG

