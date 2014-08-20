#include "framework.h"


simple_tree_view::simple_tree_view(sp(::axis::application) papp) :
   element(papp),
   
   ::user::scroll_view(papp),
   user::tree(papp)
{
}

simple_tree_view::~simple_tree_view()
{
}

void simple_tree_view::install_message_handling(::message::dispatch * pinterface)
{
   ::user::impact::install_message_handling(pinterface);
   ::user::tree::install_message_handling(pinterface);
   IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &simple_tree_view::_001OnCreate);
}




#ifdef DEBUG
void simple_tree_view::assert_valid() const
{
   ::user::impact::assert_valid();
}

void simple_tree_view::dump(dump_context & dumpcontext) const
{
   ::user::impact::dump(dumpcontext);
}
#endif //DEBUG


void simple_tree_view::_001OnCreate(signal_details * pobj)
{

   SCAST_PTR(::message::create, pcreate, pobj);

   pcreate->previous();


}



