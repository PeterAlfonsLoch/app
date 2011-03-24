#include "StdAfx.h"

simple_edit::simple_edit(::ca::application * papp) :
   ca(papp),
   data_container(papp),
   ::user::interaction(papp),
   ::user::scroll_view(papp),
   colorertake5::base_editor(papp),
   ::user::edit_plain_text(papp),
   ::userbase::edit_plain_text(papp),
   ex1::tree(papp),
   ::ca::data_listener(papp)
{

}

simple_edit::~simple_edit()
{
}


void simple_edit::_001OnDraw(::ca::graphics *pdc)
{
   ::userbase::edit_plain_text::_001OnDraw(pdc);
   /*BOOL bWin4 = afxData.bWin4;
   ::CallWindowProc(
      *GetSuperWndProcAddr(),
      get_handle(), (bWin4 ? WM_PRINT : WM_PAINT),
      (WPARAM)(pdc->get_handle1()),
      (LPARAM)(bWin4 ? PRF_CHILDREN | PRF_CLIENT : 0));*/
//   BOOL bWin4 = afxData.bWin4;
/* trans   ::CallWindowProc(
      *GetSuperWndProcAddr(),
      //xxxm_hWnd, (bWin4 ? WM_PRINT : WM_PAINT),
      get_handle(), WM_PRINT,
      (WPARAM)(pdc->get_handle1()),
      //xxx(LPARAM)(bWin4 ? PRF_CHILDREN | PRF_CLIENT : 0));
      PRF_CHILDREN | PRF_CLIENT); */
}

void simple_edit::_001OnNcDraw(::ca::graphics *pdc)
{
   ::userbase::edit_plain_text::_001OnDraw(pdc);
/*   BOOL bWin4 = afxData.bWin4;
   ::CallWindowProc(
      *GetSuperWndProcAddr(),
      get_handle(), (bWin4 ? WM_PRINT : WM_PAINT),
      (WPARAM)(pdc->get_handle1()),
      (LPARAM)(bWin4 ? PRF_NONCLIENT : 0));*/
/* trans   ::CallWindowProc(
      *GetSuperWndProcAddr(),
      get_handle(), WM_PRINT,
      (WPARAM)(pdc->get_handle1()),
      PRF_NONCLIENT); */
}


BOOL simple_edit::OnEraseBkgnd(::ca::graphics * pgraphics) 
{
   UNREFERENCED_PARAMETER(pgraphics);
   return TRUE;   
}

void simple_edit::pre_subclass_window() 
{
   // trans ::user::interaction::pre_subclass_window();
   PreSubClassWindow();   

   
}

void simple_edit::_001InstallMessageHandling(::user::win::message::dispatch * pinterface)
{
   ::userbase::edit_plain_text::_001InstallMessageHandling(pinterface);
}