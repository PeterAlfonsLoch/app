#include "framework.h"


simple_button::simple_button(::ca::application * papp) :
   ca(papp),
   ::user::button(papp),
   ::userbase::button(papp),
   m_brushBkg(papp)
{
   m_bFocus = true;
   m_bTransparent = true;
   //m_brushBkg->CreateStockObject(NULL_BRUSH);
}

simple_button::~simple_button()
{
}



void simple_button::_001OnDraw(::ca::graphics *pdc)
{
   ::userbase::button::_001OnDraw(pdc);
//   BOOL bWin4 = afxData.bWin4;
   //_gen::FillPSOnStack();
/*   ::CallWindowProc(
      *GetSuperWndProcAddr(),
      get_handle(), (bWin4 ? WM_PRINT : WM_PAINT),
      (WPARAM)(pdc->get_handle1()),
      (LPARAM)(bWin4 ? PRF_CHILDREN | PRF_CLIENT : 0));*/
   /* trans ::CallWindowProc(
      *GetSuperWndProcAddr(),
      get_handle(), WM_PRINT,
      (WPARAM)(pdc->get_handle1()),
      (LPARAM) PRF_CHILDREN | PRF_CLIENT);*/
}

void simple_button::install_message_handling(::gen::message::dispatch * pinterface)
{
   ::userbase::button::install_message_handling(pinterface);
   IGUI_WIN_MSG_LINK(WM_SETFOCUS, pinterface, this, &simple_button::_001OnSetFocus);
   //IGUI_WIN_MSG_LINK(WM_CTLCOLOR + WM_REFLECT_BASE  , this, this, &simple_button::_001OnCtlColor);
}

void simple_button::pre_subclass_window() 
{
   PreSubClassWindow();
   

   // trans ::userbase::button::pre_subclass_window();
}

void simple_button::_001OnCtlColor(gen::signal_object * pobj)
{
   SCAST_PTR(::gen::message::ctl_color, pctlcolor, pobj)
   if(m_bTransparent)
   {
      pctlcolor->m_pdc->SetBkMode(TRANSPARENT);
      pctlcolor->m_hbrush = (HBRUSH) m_brushBkg->get_os_data();
   }
   else
   {
      pctlcolor->m_hbrush = NULL;
   }
}



void simple_button::ResizeToFit()
{
   ::ca::graphics * pdc = GetDC();

   pdc->SelectObject(GetFont());

   string str;
   GetWindowText(str);
   size size = pdc->GetTextExtent(str);

   rect rect(0, 0, 0, 0);
   rect.right = size.cx + 4;
   rect.bottom = size.cy + 4;

   SetWindowPos(NULL, 0, 0, rect.width(), rect.height(), SWP_NOMOVE);

   ReleaseDC(pdc);
}

void simple_button::_001OnSetFocus(gen::signal_object * pobj)
{
   SCAST_PTR(::gen::message::set_focus, psetfocus, pobj)
 //  if(!m_bFocus)
   //{
     // pOldWnd->SetFocus();
   //}
   psetfocus->previous();
}