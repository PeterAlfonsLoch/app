#include "StdAfx.h"
#include "simple_tab_control.h"


simple_tab_control::simple_tab_control(::ca::application * papp):
   ca(papp),
   ::user::interaction(papp),
   ::user::tab(papp),
   place_holder_container(papp)
{
}

simple_tab_control::~simple_tab_control()
{
}




void simple_tab_control::_001OnDraw(::ca::graphics *pdc)
{
//   BOOL bWin4 = afxData.bWin4;
/*   ::CallWindowProc(
      *GetSuperWndProcAddr(),
      //xxxm_hWnd, (bWin4 ? WM_PRINT : WM_PAINT),
      get_handle(), WM_PRINT,
      (WPARAM)(pdc->get_handle1()),
      //xxx(LPARAM)(bWin4 ? PRF_CHILDREN | PRF_CLIENT : 0));
      PRF_CHILDREN | PRF_CLIENT);*/
   ::user::tab::_001OnDraw(pdc);
}

void simple_tab_control::pre_subclass_window() 
{
   _001BaseWndInterfaceMap();

   ::user::interaction::pre_subclass_window();
}

void simple_tab_control::_001OnNcDraw(::ca::graphics *pdc)
{
   rect rectClient;

   ::user::interaction::GetClientRect(rectClient);

   pdc->FillSolidRect(rectClient, GetSysColor(COLOR_3DFACE));
   /*class imaging & imaging = System.imaging();
   imaging.color_blend(
      pdc,
      rectClient.left,
      rectClient.top,
      rectClient.width(),
      rectClient.height(),
      RGB(127, 127, 120),
      127);*/

   /*::CallWindowProc(
      *GetSuperWndProcAddr(),
      get_handle(), 
      WM_NCPAINT,
      (WPARAM)(pdc->get_handle1()),
      0);*/
   ::user::tab::_001OnDraw(pdc);
}

BOOL simple_tab_control::OnEraseBkgnd(::ca::graphics * pgraphics) 
{
   UNREFERENCED_PARAMETER(pgraphics);
   return TRUE;   
}


void simple_tab_control::_001InstallMessageHandling(::user::win::message::dispatch * pinterface)
{
   ::user::interaction::_001InstallMessageHandling(pinterface);
   ::user::window_interface::_001InstallMessageHandling(pinterface);
}