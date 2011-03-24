#include "StdAfx.h"

namespace veiev
{



   right_split_view::right_split_view(::ca::application * papp ) :
      ca(papp),
      ::userbase::split_layout(papp),
      ::userbase::view(papp),
      ::userbase::split_view(papp),
      place_holder_container(papp)
   {
   }

   void right_split_view::_001InstallMessageHandling(::user::win::message::dispatch * pinterface)
   {
      ::userbase::split_view::_001InstallMessageHandling(pinterface);
      IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &right_split_view::_001OnCreate);

   }


   void right_split_view::_001OnCreate(gen::signal_object * pobj)
   {
      pobj->previous();
      if(pobj->m_bRet)
         return;
      
      SetPaneCount(2);
      SetSplitOrientation(orientation_horizontal);
      set_position_rate(0, 0.2);
      ::user::interaction* pwnd = create_view(typeid(simple_list_view), get_document(), this, 100);
      SetPane(0, pwnd, false);
      m_plistview = dynamic_cast < simple_list_view * > (pwnd);

      pwnd = create_view(typeid(veiev::view), get_document(), this, 101);
      SetPane(1, pwnd, false);
      layout();
      m_pview = dynamic_cast < veiev::view * > (pwnd);
   }

   document * right_split_view::get_document()
   {
      return dynamic_cast < document * > (::userbase::split_view::get_document());
   }

} // namespace veiev