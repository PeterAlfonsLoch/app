#include "StdAfx.h"

namespace veiev
{

   right_view::right_view(::ca::application * papp ) :
      ca(papp),
      ::userbase::split_layout(papp),
      ::userbase::view(papp),
      ::userbase::split_view(papp),
      place_holder_container(papp)
   {
   }

   void right_view::_001InstallMessageHandling(::user::win::message::dispatch * pinterface)
   {
      ::userbase::split_view::_001InstallMessageHandling(pinterface);
      IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &right_view::_001OnCreate);

   }


   void right_view::_001OnCreate(gen::signal_object * pobj)
   {
      pobj->previous();
      if(pobj->m_bRet)
         return;
      
      SetPaneCount(2);
      SetSplitOrientation(orientation_horizontal);
      set_position_rate(0, 0.2);
      create_context cc;
      cc.m_pCurrentDoc = get_document();
      cc.m_typeinfoNewView =  &typeid(veiev::list);
      ::user::interaction* pwnd = create_view(typeid(veiev::list), get_document(), this, 100);
      SetPane(0, pwnd, false);
      set_position_rate(0, 0.5);

//      list * plist = dynamic_cast < list * > (pwnd);
      cc.m_pCurrentDoc = get_document();
      cc.m_typeinfoNewView =  &typeid(veiev::right_pane_view);
      pwnd = create_view(typeid(veiev::right_pane_view), get_document(), this, 100);
      SetPane(1, pwnd, false);
      layout();
      application * papp = dynamic_cast < application * > (get_app());
      papp->::veiev::application::m_prightview = this;
   }

   document * right_view::get_document()
   {
      return dynamic_cast < document * > (::userbase::split_view::get_document());
   }

} // namespace veiev