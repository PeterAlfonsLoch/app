#include "StdAfx.h"

namespace mail
{

   main_view::main_view(::ca::application * papp) :
      ca(papp),
      ::userbase::split_layout(papp),
      ::userbase::view(papp),
      ::userbase::split_view(papp),
      place_holder_container(papp)
   {
   }

   void main_view::_001InstallMessageHandling(::user::win::message::dispatch * pinterface)
   {
      ::userbase::split_view::_001InstallMessageHandling(pinterface);
      IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &main_view::_001OnCreate);
   }

   void main_view::_001OnCreate(gen::signal_object * pobj)
   {
      pobj->previous();
      if(pobj->m_bRet)
         return;
      System.m_pmainview = this;
      SetPaneCount(2);
      SetSplitOrientation(orientation_vertical);
      set_position_rate(0, 0.2);
      create_context cc;

      cc.m_pCurrentDoc = get_document();
      cc.m_typeinfoNewView = &typeid(tree);
      ::user::interaction* pwnd = create_view(typeid(tree), get_document(), this, 100);
      SetPane(0, pwnd, false);
      tree * ptree = dynamic_cast < tree * > (pwnd);
      ptree->create_list(ptree->get_base_item());


      cc.m_pCurrentDoc = get_document();
      cc.m_typeinfoNewView = typeid(right_view);
      pwnd = create_view(typeid(right_pane_view), get_document(), this, 101);
      SetPane(1, pwnd, false);
      layout();
      SetTimer(123, 1000, NULL);
   }

   document * main_view::get_document()
   {
      return dynamic_cast < document * > (::userbase::split_view::get_document());
   }

   void main_view::_001OnTimer(gen::signal_object * pobj)
   {
      SCAST_PTR(::user::win::message::timer, ptimer, pobj);
      if(ptimer->m_nIDEvent == 123)
      {
         System.TimerStep();
      }
   }


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
      cc.m_typeinfoNewView =  &typeid(mail::list);
      ::user::interaction* pwnd = create_view(typeid(mail::list), get_document(), this, 100);
      SetPane(0, pwnd, false);

//      list * plist = dynamic_cast < list * > (pwnd);
      cc.m_pCurrentDoc = get_document();
      cc.m_typeinfoNewView =  &typeid(mail::right_pane_view);
      pwnd = create_view(typeid(mail::right_pane_view), get_document(), this, 100);
      SetPane(1, pwnd, false);
      layout();
      System.m_prightview = this;
   }

   document * right_view::get_document()
   {
      return dynamic_cast < document * > (::userbase::split_view::get_document());
   }

} // namespace mail