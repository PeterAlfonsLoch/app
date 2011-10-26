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
      m_ppaneview = NULL;
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

   

      address_view * ptopview = create_view < address_view > ();
      if(ptopview == NULL)
      {
         System.simple_message_box(NULL, "Could not create address bar ::view");
      }
      SetPane(0, ptopview, true);
      get_document()->m_paddressview = ptopview;

      m_ppaneview = create_view < pane_view > ();
      if(m_ppaneview == NULL)
      {
         System.simple_message_box(NULL, "Could not create pane tab ::view");
      }
      SetPane(1, m_ppaneview, true);
      get_document()->m_ppaneview = m_ppaneview;
  
      layout();

   }

   main_document * a_view::get_document()
   {
      return dynamic_cast < main_document * > (::view::get_document());
   }

   void a_view::install_message_handling(::user::win::message::dispatch * pinterface)
   {
      ::userbase::split_view::install_message_handling(pinterface);
      IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &a_view::_001OnCreate);
   }

   void a_view::_001OnCreate(gen::signal_object * pobj)
   {
      pobj->previous();
      CreateViews();
   }


} // namespace veriview


