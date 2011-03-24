#include "StdAfx.h"


CXView::CXView(::ca::application * papp) :
   ::ca::ca(papp),
   gcom::backview::WndInterface(papp),
   mediaplay::MediaViewInterface(papp),
   mediaplay::MediaView(papp)
{
}

CXView::~CXView()
{
}



void CXView::_001OnDraw(CDC* pDC)
{
}


#ifdef _DEBUG
void CXView::AssertValid() const
{
	MediaView::AssertValid();
}

void CXView::Dump(CDumpContext& dc) const
{
	MediaView::Dump(dc);
}
#endif //_DEBUG

