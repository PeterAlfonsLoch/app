#include "StdAfx.h"

simple_tree_view::simple_tree_view(::ax::application * papp) :
   ax(papp),
   data_container(papp),
   ::userbase::view(papp),
   ::user::scroll_view(papp),
   ex1::tree(papp),
   user::tree(papp)
{
}

simple_tree_view::~simple_tree_view()
{
}

void simple_tree_view::install_message_handling(::gen::message::dispatch * pinterface)
{
   ::userbase::view::install_message_handling(pinterface);
   ::user::tree::install_message_handling(pinterface);
   IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &simple_tree_view::_001OnCreate);
}




#ifdef _DEBUG
void simple_tree_view::assert_valid() const
{
   ::userbase::view::assert_valid();
}

void simple_tree_view::dump(dump_context & dumpcontext) const
{
   ::userbase::view::dump(dumpcontext);
}
#endif //_DEBUG


void simple_tree_view::_001OnCreate(gen::signal_object * pobj)
{
   SCAST_PTR(gen::message::create, pcreate, pobj);
   pcreate->previous();

/*   if(!ex1::tree_data::initialize())
   {
      pcreate->set_lresult(0);
      pcreate->m_bRet = true;
      return;
   }*/

   if(!ex1::tree::initialize())
   {
      pcreate->set_lresult(0);
      pcreate->m_bRet = true;
      return;
   }

}

