#include "StdAfx.h"

namespace veriview
{


a_view::a_view(::ca::application * papp) :
   ca(papp),
   ::userbase::split_layout(papp),
   ::userbase::view(papp),
   ::userbase::split_view(papp),
   place_holder_container(papp)
{
}

a_view::~a_view()
{
}

#ifdef _DEBUG
void a_view::assert_valid() const
{
   ::userbase::split_view::assert_valid();
}

void a_view::dump(dump_context & dumpcontext) const
{
   ::userbase::split_view::dump(dumpcontext);
}

#endif //_DEBUG


void a_view::on_update(::view * pSender, LPARAM lHint, ::radix::object* phint) 
{

   UNREFERENCED_PARAMETER(pSender);
   UNREFERENCED_PARAMETER(lHint);
   UNREFERENCED_PARAMETER(phint);
   
}

void a_view::CreateViews()
{
   SetPaneCount(2);

   SetSplitOrientation(orientation_horizontal);
  
   set_position(0, 20);

   

   create_context cc;
   cc.m_pCurrentDoc = get_document();
   cc.m_typeinfoNewView =  &typeid(address_view);
   cc.m_pCurrentFrame = this;

   address_view * ptopview = dynamic_cast < address_view * > (create_view(&cc, this, 100));
   if(ptopview == NULL)
   {
      System.simple_message_box(NULL, "Could not create address bar ::view");
   }
   SetPane(0, ptopview, true);
   get_document()->m_paddressview = ptopview;

   cc.m_pCurrentDoc = get_document();
   cc.m_typeinfoNewView =  &typeid(pane_view);

   pane_view * ppaneview = dynamic_cast < pane_view * > (create_view(&cc, this, 100));
   if(ppaneview == NULL)
   {
      System.simple_message_box(NULL, "Could not create pane tab ::view");
   }
   SetPane(1, ppaneview, true);
   get_document()->m_ppaneview = ppaneview;
  
   layout();

}

main_document * a_view::get_document()
{
   return dynamic_cast < main_document * > (::view::get_document());
}

void a_view::_001InstallMessageHandling(::user::win::message::dispatch * pinterface)
{
   ::userbase::split_view::_001InstallMessageHandling(pinterface);
   IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &a_view::_001OnCreate);
}

void a_view::_001OnCreate(gen::signal_object * pobj)
{
   pobj->previous();
   CreateViews();
}

} // namespace veriview