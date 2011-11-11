#include "StdAfx.h"


namespace mediaplaylist
{


   view::view(::ca::application * papp) :
      ca(papp),
      userbase::view(papp),
      user::place_holder_container(papp),
      userbase::split_layout(papp),
      userbase::split_view(papp)
   {
      m_dataid = "view";
   }

   view::~view()
   {
   }

   void view::install_message_handling(::user::win::message::dispatch * pdispatch)
   {
      ::userbase::split_view::install_message_handling(pdispatch);
      IGUI_WIN_MSG_LINK(WM_CREATE, pdispatch, this, &view::_001OnCreate);
   }

   #ifdef _DEBUG
   void view::assert_valid() const
   {
      ::userbase::split_view::assert_valid();
   }

   void view::dump(dump_context & dumpcontext) const
   {
      ::userbase::split_view::dump(dumpcontext);
   }
   #endif //_DEBUG

   void view::on_update(::view * pSender, LPARAM lHint, ::radix::object* pHint) 
   {
      UNREFERENCED_PARAMETER(pSender);
      UNREFERENCED_PARAMETER(lHint);
      UNREFERENCED_PARAMETER(pHint);
   }

   ::mediaplaylist::document * view::get_document()
   {
      return dynamic_cast < ::mediaplaylist::document * > (::view::get_document());
   }

   void view::_001OnCreate(gen::signal_object * pobj)
   {
      
      pobj->previous();

      SetSplitOrientation(userbase::split_layout::orientation_vertical);

      SetPaneCount(2);

      

      SetPane(0, create_view < mediaplaylist::tree_view > (), false);
      SetPane(1, create_view < mediaplaylist::list_view > (), false);

      set_position_rate(0, 0.33);

      m_splitbara[0].m_dwMaxPosition = 284;
      

   }

} // namespace mediaplaylist