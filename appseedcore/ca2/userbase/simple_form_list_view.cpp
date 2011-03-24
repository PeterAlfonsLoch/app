#include "StdAfx.h"

simple_form_list_view::simple_form_list_view(::ca::application * papp) :
   ca(papp),
   ::user::interaction(papp), 
   ::user::form(papp), 
   ::user::form_list(papp),
   ::userbase::form_list(papp),
   m_headerctrl(papp),
   m_scrollbarVert(papp),
   m_scrollbarHorz(papp),
   ::userbase::view(papp),
   ::user::scroll_view(papp),
   ::user::list(papp)
{
   m_pheaderctrl     = &m_headerctrl;
   m_pheaderctrl->SetBaseListCtrlInterface(this);
   m_pscrollbarVert  = &m_scrollbarVert;
   m_pscrollbarHorz  = &m_scrollbarHorz;

}

simple_form_list_view::~simple_form_list_view()
{
}

void simple_form_list_view::_001InstallMessageHandling(::user::win::message::dispatch * pinterface)
{
   ::userbase::view::_001InstallMessageHandling(pinterface);
   ::user::form_list::_001InstallMessageHandling(pinterface);
}



#ifdef _DEBUG
void simple_form_list_view::assert_valid() const
{
   ::userbase::view::assert_valid();
}

void simple_form_list_view::dump(dump_context & dumpcontext) const
{
   ::userbase::view::dump(dumpcontext);
}
#endif //_DEBUG

BOOL simple_form_list_view::PreCreateWindow(CREATESTRUCT& cs) 
{
   
   cs.style |= WS_CLIPCHILDREN;
   
   return ::userbase::view::PreCreateWindow(cs);
}

