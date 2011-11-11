#include "StdAfx.h"

simple_tab_view::simple_tab_view(::ca::application * papp) :
   ca(papp),
   ::userbase::view(papp),
   ::user::interaction(papp), 
   ::user::tab(papp),
   place_holder_container(papp)
{
   m_pguie = this;
}

simple_tab_view::~simple_tab_view()
{
}


// simple_tab_view diagnostics

#ifdef _DEBUG
void simple_tab_view::assert_valid() const
{
   ::userbase::view::assert_valid();
}

#ifndef _WIN32_WCE
void simple_tab_view::dump(dump_context & dumpcontext) const
{
   ::userbase::view::dump(dumpcontext);
}
#endif
#endif //_DEBUG

void simple_tab_view::layout()
{
   ::user::tab::layout();
}








void simple_tab_view::GetClientRect(LPRECT lprect)
{
   ::userbase::view::GetClientRect(lprect);
}


void simple_tab_view::_001OnCreate(gen::signal_object * pobj)
{
   SCAST_PTR(::user::win::message::create, pcreate, pobj)
   if(pcreate->previous())
      return;
   
   if(!::user::control::create(this, 1))
   {
      pcreate->set_lresult(-1);
      return;
   }
}

void simple_tab_view::_001OnDraw(::ca::graphics * pdc)
{
   ::user::tab::_001OnDraw(pdc);
}

void simple_tab_view::install_message_handling(::user::win::message::dispatch * pinterface)
{
   ::userbase::view::install_message_handling(pinterface);
   ::user::tab::install_message_handling(pinterface);
}


void simple_tab_view::_001OnLButtonUp(gen::signal_object * pobj)
{
   SCAST_PTR(::user::win::message::mouse, pmouse, pobj)
   ::user::tab::_001OnLButtonUp(pobj);
   if(pmouse->m_bRet)
      return;
 // trans  virtual_user_interface::_001OnLButtonUp(pobj);
   if(pmouse->m_bRet)
      return;
}

void simple_tab_view::_001OnMouseMove(gen::signal_object * pobj)
{
   SCAST_PTR(::user::win::message::mouse, pmouse, pobj)
   ::user::tab::_001OnMouseMove(pobj);
   if(pmouse->m_bRet)
      return;
// trans   virtual_user_interface::_001OnMouseMove(pobj);
   if(pmouse->m_bRet)
      return;
}

void simple_tab_view::_001OnMouseLeave(gen::signal_object * pobj)
{
   SCAST_PTR(::user::win::message::mouse, pmouse, pobj)
   ::user::tab::_001OnMouseLeave(pobj);
   if(pmouse->m_bRet)
      return;
// trans   virtual_user_interface::_001OnMouseLeave(pobj);
   if(pmouse->m_bRet)
      return;
}
