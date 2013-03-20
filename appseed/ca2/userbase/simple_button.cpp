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
}

void simple_button::install_message_handling(::ca::message::dispatch * pinterface)
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

void simple_button::_001OnCtlColor(::ca::signal_object * pobj)
{
   SCAST_PTR(::ca::message::ctl_color, pctlcolor, pobj)
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
   ::ca::client_graphics pdc(this);

   pdc->SelectObject(GetFont());

   string str;
   GetWindowText(str);
   size size = pdc->GetTextExtent(str);

   rect rect(0, 0, 0, 0);
   rect.right = size.cx + 4;
   rect.bottom = size.cy + 4;

   SetWindowPos(0, 0, 0, rect.width(), rect.height(), SWP_NOMOVE);


}

void simple_button::_001OnSetFocus(::ca::signal_object * pobj)
{
   SCAST_PTR(::ca::message::set_focus, psetfocus, pobj)
 //  if(!m_bFocus)
   //{
     // pOldWnd->SetFocus();
   //}
   psetfocus->previous();
}
