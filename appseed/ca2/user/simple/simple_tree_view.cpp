#include "framework.h"


simple_tree_view::simple_tree_view(sp(::ca2::application) papp) :
   ca2(papp),
   
   ::user::scroll_view(papp),
   user::tree(papp)
{
}

simple_tree_view::~simple_tree_view()
{
}

void simple_tree_view::install_message_handling(::ca2::message::dispatch * pinterface)
{
   ::user::view::install_message_handling(pinterface);
   ::user::tree::install_message_handling(pinterface);
   IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &simple_tree_view::_001OnCreate);
}




#ifdef DEBUG
void simple_tree_view::assert_valid() const
{
   ::user::view::assert_valid();
}

void simple_tree_view::dump(dump_context & dumpcontext) const
{
   ::user::view::dump(dumpcontext);
}
#endif //DEBUG


void simple_tree_view::_001OnCreate(::ca2::signal_object * pobj)
{

   SCAST_PTR(::ca2::message::create, pcreate, pobj);

   pcreate->previous();


}



