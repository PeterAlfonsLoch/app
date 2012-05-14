#include "framework.h"


simple_combo_box::simple_combo_box()
{
}

simple_combo_box::~simple_combo_box()
{
}


 // BEGIN_MESSAGE_MAP(simple_combo_box, ::userbase::combo_box)
   //{{__MSG_MAP(simple_combo_box)
// xxx   ON_WM_ERASEBKGND()
   //}}__MSG_MAP
 // END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// simple_combo_box message handlers

void simple_combo_box::_001OnDraw(::ca::graphics *pdc)
{
   ::userbase::combo_box::_001OnDraw(pdc);
/*   BOOL bWin4 = afxData.bWin4;
   _gen::FillPSOnStack();
   ::CallWindowProc(
      *GetSuperWndProcAddr(),
      get_handle(), (bWin4 ? WM_PRINT : WM_PAINT),
      (WPARAM)(pdc->get_handle1()),
      (LPARAM)(bWin4 ? PRF_CHILDREN | PRF_CLIENT : 0));*/
//   BOOL bWin4 = afxData.bWin4;
//   _gen::FillPSOnStack();
/* trans   ::CallWindowProc(
      *GetSuperWndProcAddr(),
      //xxxm_hWnd, (bWin4 ? WM_PRINT : WM_PAINT),
      get_handle(), WM_PRINT,
      (WPARAM)(pdc->get_handle1()),
      //xxx(LPARAM)(bWin4 ? PRF_CHILDREN | PRF_CLIENT : 0));
      PRF_CHILDREN | PRF_CLIENT); */
}

BOOL simple_combo_box::OnEraseBkgnd(::ca::graphics * pgraphics) 
{
   UNREFERENCED_PARAMETER(pgraphics);
   return TRUE;
}


void simple_combo_box::pre_subclass_window() 
{
   PreSubClassWindow();   
   
// trans   ::userbase::combo_box::pre_subclass_window();
}
