#include "StdAfx.h"


simple_combo_box::simple_combo_box()
{
}

simple_combo_box::~simple_combo_box()
{
}


 // BEGIN_MESSAGE_MAP(simple_combo_box, ::userbase::combo_box)
   //{{AFX_MSG_MAP(simple_combo_box)
// xxx   ON_WM_ERASEBKGND()
   //}}AFX_MSG_MAP
 // END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// simple_combo_box message handlers

void simple_combo_box::_001OnDraw(::ax::graphics *pdc)
{
   ::userbase::combo_box::_001OnDraw(pdc);
/*   BOOL bWin4 = afxData.bWin4;
   _AfxFillPSOnStack();
   ::CallWindowProc(
      *GetSuperWndProcAddr(),
      get_handle(), (bWin4 ? WM_PRINT : WM_PAINT),
      (WPARAM)(pdc->get_handle1()),
      (LPARAM)(bWin4 ? PRF_CHILDREN | PRF_CLIENT : 0));*/
//   BOOL bWin4 = afxData.bWin4;
//   _AfxFillPSOnStack();
/* trans   ::CallWindowProc(
      *GetSuperWndProcAddr(),
      //xxxm_hWnd, (bWin4 ? WM_PRINT : WM_PAINT),
      get_handle(), WM_PRINT,
      (WPARAM)(pdc->get_handle1()),
      //xxx(LPARAM)(bWin4 ? PRF_CHILDREN | PRF_CLIENT : 0));
      PRF_CHILDREN | PRF_CLIENT); */
}

BOOL simple_combo_box::OnEraseBkgnd(::ax::graphics * pgraphics) 
{
   UNREFERENCED_PARAMETER(pgraphics);
   return TRUE;
}


void simple_combo_box::pre_subclass_window() 
{
   PreSubClassWindow();   
   
// trans   ::userbase::combo_box::pre_subclass_window();
}
