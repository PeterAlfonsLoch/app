//#include "framework.h"


simple_list_view::simple_list_view(::aura::application * papp) :
   object(papp)
{

}


simple_list_view::~simple_list_view()
{

}


void simple_list_view::install_message_handling(::message::dispatch * pinterface)
{
   
   BASE_TYPE::install_message_handling(pinterface);
   
}



/////////////////////////////////////////////////////////////////////////////
// simple_list_view drawing

void simple_list_view::OnDraw(::draw2d::graphics * pgraphics)
{
   UNREFERENCED_PARAMETER(pgraphics);
   ASSERT(FALSE);
}

void simple_list_view::assert_valid() const
{
   ::user::impact::assert_valid();
}

void simple_list_view::dump(dump_context & dumpcontext) const
{
   ::user::impact::dump(dumpcontext);
}

bool simple_list_view::pre_create_window(::user::create_struct& cs)
{
   cs.style |= WS_CLIPCHILDREN;

   return ::user::impact::pre_create_window(cs);
}


sp(::user::interaction) simple_list_view::OnDrawInterfaceGetWnd()
{
   return this;
}

