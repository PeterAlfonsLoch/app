#include "StdAfx.h"
#include "CDBrowseView.h"

#include "CDDeviceListView.h"
#include "CDContentListView.h"


CDBrowseView::CDBrowseView(::ca::application * papp) :
   ca(papp),
   ::userbase::split_layout(papp),
   ::userbase::view(papp),
   ::userbase::split_view(papp),
   place_holder_container(papp)
{
}

CDBrowseView::~CDBrowseView()
{
}



 // BEGIN_MESSAGE_MAP(CDBrowseView, ::userbase::split_view)
   //{{AFX_MSG_MAP(CDBrowseView)
//   ON_WM_CREATE()
//   ON_WM_SHOWWINDOW()
   //}}AFX_MSG_MAP
 // END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDBrowseView message handlers

int CDBrowseView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
/*   if (::userbase::split_view::OnCreate(lpCreateStruct) == -1)
      return -1;*/
   
   SetPaneCount(2);
   SetSplitOrientation(orientation_vertical);
   /*Initialize(
      GetParent(),
        0,
      2,
      CSplitLayout::orientation_vertical);*/


   ::userbase::document * pdoc = get_document();
//   simple_frame_window * pframe = GetParentFrame();

   /*if(!CreateView(0, &typeid(CDDeviceListView)), pdoc, pframe)
   {
      return -1;
   }
   if(!CreateView(1, &typeid(CCDContentListView)), pdoc, pframe)
   {
      return -1;
   }*/

   set_position_rate(0, 0.2);
   
   return 0;
}

void CDBrowseView::OnShowWindow(BOOL bShow, UINT nStatus) 
{
//   ::userbase::split_view::OnShowWindow(bShow, nStatus);
   
   SetVisible(bShow != 0);
   
}
