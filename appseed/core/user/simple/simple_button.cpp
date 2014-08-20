#include "framework.h"


simple_button::simple_button(sp(::axis::application) papp) :
   element(papp),
   
   ::user::button(papp),
   m_brushBkg(allocer())
{
   m_bFocus = true;
   m_bTransparent = true;
   //m_brushBkg->CreateStockObject(NULL_BRUSH);
}

simple_button::~simple_button()
{
}



void simple_button::_001OnDraw(::draw2d::graphics *pdc)
{
   ::user::button::_001OnDraw(pdc);
}

void simple_button::install_message_handling(::message::dispatch * pinterface)
{
   ::user::button::install_message_handling(pinterface);
   IGUI_WIN_MSG_LINK(WM_SETFOCUS, pinterface, this, &simple_button::_001OnSetFocus);
   //IGUI_WIN_MSG_LINK(WM_CTLCOLOR + WM_REFLECT_BASE  , this, this, &simple_button::_001OnCtlColor);
}

void simple_button::pre_subclass_window()
{
   PreSubClassWindow();


   // trans ::user::button::pre_subclass_window();
}

void simple_button::_001OnCtlColor(signal_details * pobj)
{
   SCAST_PTR(::message::ctl_color, pctlcolor, pobj)
   if(m_bTransparent)
   {
//      pctlcolor->m_pdc->SetBkMode(TRANSPARENT);
      pctlcolor->m_hbrush = (HBRUSH) m_brushBkg->get_os_data();
   }
   else
   {
      pctlcolor->m_hbrush = NULL;
   }
}



void simple_button::ResizeToFit()
{

   ::draw2d::memory_graphics pdc(allocer());

   select_font(pdc);

   string str;
   GetWindowText(str);
   size size = pdc->GetTextExtent(str);

   rect rect(0, 0, 0, 0);
   rect.right = size.cx + 4;
   rect.bottom = size.cy + 4;

   SetWindowPos(0, 0, 0, rect.width(), rect.height(), SWP_NOMOVE);


}

void simple_button::_001OnSetFocus(signal_details * pobj)
{
   SCAST_PTR(::message::set_focus, psetfocus, pobj)
 //  if(!m_bFocus)
   //{
     // pOldWnd->SetFocus();
   //}
   psetfocus->previous();
}
