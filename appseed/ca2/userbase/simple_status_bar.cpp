#include "StdAfx.h"


simple_status_bar::simple_status_bar(::ca::application * papp) :
   ca(papp)
{

}

simple_status_bar::~simple_status_bar()
{
}

/*
 // BEGIN_MESSAGE_MAP(simple_status_bar, ::userbase::status_bar)
   //{{AFX_MSG_MAP(simple_status_bar)
   ON_WM_ERASEBKGND()
   //}}AFX_MSG_MAP
 // END_MESSAGE_MAP()
*/

/////////////////////////////////////////////////////////////////////////////
// simple_status_bar message handlers


/*
BOOL simple_status_bar::OnEraseBkgnd(::ca::graphics * pgraphics) 
{
   return TRUE;
}
*/

void simple_status_bar::_001OnDraw(::ca::graphics *pdc)
{
   return;
   rect rectClient;

   GetClientRect(rectClient);

   class imaging & imaging = System.imaging();
   imaging.color_blend(
      pdc,
      rectClient.left,
      rectClient.top,
      rectClient.width(),
      rectClient.height(),
      GetSysColor(COLOR_3DFACE),
      208);

   
//xxx   BOOL bWin4 = afxData.bWin4;
   /*::CallWindowProc(
      *GetSuperWndProcAddr(),
      get_handle(), (bWin4 ? WM_PRINT : WM_PAINT),
      (WPARAM)(pdc->get_handle1()),
      (LPARAM)(bWin4 ? PRF_CHILDREN | PRF_CLIENT : 0));*/
   /* trans ::CallWindowProc(
      *GetSuperWndProcAddr(),
      get_handle(), WM_PRINT,
      (WPARAM)(pdc->get_handle1()),
      (LPARAM) ( PRF_CHILDREN | PRF_CLIENT )); */

}

