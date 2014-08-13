#include "framework.h"


MetaControlBox::MetaControlBox(sp(::base::application) papp) :
element(papp),
::user::interaction(papp),
::user::uinteraction::frame::control_box(papp)
{
   
   m_crBackground = ARGB(204,84,208,77);

}


MetaControlBox::~MetaControlBox()
{

}


void MetaControlBox::_001OnDraw(::draw2d::graphics * pdc)
{

   rect rectClient;

   GetClientRect(rectClient);

   if (rectClient.area() <= 0)
      return;

   pdc->set_alpha_mode(::draw2d::alpha_mode_blend);

   pdc->FillSolidRect(rectClient, m_crBackground);

}


void MetaControlBox::_001OnShowWindow(signal_details * pobj)
{

   UNREFERENCED_PARAMETER(pobj);

}

void MetaControlBox::_001OnLButtonDown(signal_details * pobj)
{

   UNREFERENCED_PARAMETER(pobj);

}

void MetaControlBox::_001OnLButtonUp(signal_details * pobj)
{

   UNREFERENCED_PARAMETER(pobj);

   RedrawWindow();

}



void MetaControlBox::_001OnTimer(signal_details * pobj)
{
//   SCAST_PTR(::message::timer, ptimer, pobj)
   UNREFERENCED_PARAMETER(pobj);


}


void MetaControlBox::install_message_handling(::message::dispatch *pinterface)
{
   
   ::user::uinteraction::frame::control_box::install_message_handling(pinterface);

   IGUI_WIN_MSG_LINK(WM_SHOWWINDOW, pinterface, this, &MetaControlBox::_001OnShowWindow);
   IGUI_WIN_MSG_LINK(WM_LBUTTONDOWN, pinterface, this, &MetaControlBox::_001OnLButtonDown);
   IGUI_WIN_MSG_LINK(WM_LBUTTONUP, pinterface, this, &MetaControlBox::_001OnLButtonUp);
   IGUI_WIN_MSG_LINK(WM_SIZE, pinterface, this, &MetaControlBox::_001OnSize);
   IGUI_WIN_MSG_LINK(WM_TIMER, pinterface, this, &MetaControlBox::_001OnTimer);

}



