#include "framework.h"


simple_tab_view::simple_tab_view(sp(::base::application) papp) :
   element(papp),
   ::user::interaction(papp), 
   ::user::tab(papp),
   place_holder_container(papp)
{
}


simple_tab_view::~simple_tab_view()
{
}


// simple_tab_view diagnostics

#ifdef DEBUG
void simple_tab_view::assert_valid() const
{
   ::user::impact::assert_valid();
}

#ifndef _WIN32_WCE
void simple_tab_view::dump(dump_context & dumpcontext) const
{
   ::user::impact::dump(dumpcontext);
}
#endif
#endif //DEBUG

void simple_tab_view::layout()
{
   ::user::tab::layout();
}








void simple_tab_view::GetClientRect(LPRECT lprect)
{
   ::user::impact::GetClientRect(lprect);
}


void simple_tab_view::_001OnCreate(signal_details * pobj)
{
   SCAST_PTR(::message::create, pcreate, pobj)
   if(pcreate->previous())
      return;
   
   if(!::user::control::create(this, 1))
   {
      pcreate->set_lresult(-1);
      return;
   }
}

void simple_tab_view::_001OnDraw(::draw2d::graphics * pdc)
{
   ::user::tab::_001OnDraw(pdc);
}

void simple_tab_view::install_message_handling(::message::dispatch * pinterface)
{
   ::user::impact::install_message_handling(pinterface);
   ::user::tab::install_message_handling(pinterface);
}


void simple_tab_view::_001OnLButtonUp(signal_details * pobj)
{
   SCAST_PTR(::message::mouse, pmouse, pobj)
   ::user::tab::_001OnLButtonUp(pobj);
   if(pmouse->m_bRet)
      return;
 // trans  ::user::interaction_child::_001OnLButtonUp(pobj);
   if(pmouse->m_bRet)
      return;
}

void simple_tab_view::_001OnMouseMove(signal_details * pobj)
{
   SCAST_PTR(::message::mouse, pmouse, pobj)
   ::user::tab::_001OnMouseMove(pobj);
   if(pmouse->m_bRet)
      return;
// trans   ::user::interaction_child::_001OnMouseMove(pobj);
   if(pmouse->m_bRet)
      return;
}

void simple_tab_view::_001OnMouseLeave(signal_details * pobj)
{
   SCAST_PTR(::message::mouse, pmouse, pobj)
   ::user::tab::_001OnMouseLeave(pobj);
   if(pmouse->m_bRet)
      return;
// trans   ::user::interaction_child::_001OnMouseLeave(pobj);
   if(pmouse->m_bRet)
      return;
}
