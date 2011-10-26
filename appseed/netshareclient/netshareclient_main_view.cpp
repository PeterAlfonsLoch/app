#include "StdAfx.h"

namespace netshareclient
{

   main_view::main_view(::ca::application * papp) :
      ca(papp),
      ::userbase::split_layout(papp),
      ::userbase::view(papp),
      ::userbase::split_view(papp),
      place_holder_container(papp)
   {
   }

   void main_view::install_message_handling(::user::win::message::dispatch * pinterface)
   {
      ::userbase::split_view::install_message_handling(pinterface);
      IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &main_view::_001OnCreate);
   }

   void main_view::_001OnCreate(gen::signal_object * pobj)
   {
      pobj->previous();
      if(pobj->m_bRet)
         return;
//      application * papp = dynamic_cast < application * > (get_app());
      //papp->m_pmainview = this;
      SetPaneCount(2);
      SetSplitOrientation(orientation_vertical);
      set_position_rate(0, 0.2);
//      create_context cc;

  //    cc.m_pCurrentDoc = get_document();
    //  cc.m_typeinfoNewView = ::ca::get_type_info < tree > ();
      ::user::interaction* pwnd = create_view(::ca::get_type_info < tree > (), get_document(), this, 100);
      SetPane(0, pwnd, false);
      tree * ptree = dynamic_cast < tree * > (pwnd);
      ptree->create_list(ptree->get_base_item());


//      cc.m_pCurrentDoc = get_document();
  //    cc.m_typeinfoNewView = ::ca::get_type_info < list > ();
      pwnd = create_view(::ca::get_type_info < list > (), get_document(), this, 101);
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
         //Application.TimerStep();
      }
   }

   void main_view::on_update(::view * pSender, LPARAM lHint, ::radix::object* pHint)
   {
      UNREFERENCED_PARAMETER(pSender);
      UNREFERENCED_PARAMETER(pHint);
      if(lHint == document::hint_netshare)
      {
         string strAddress(get_document()->m_strAddress);
         bool bNew = false;
         if(m_mapView[strAddress] == NULL)
         {
            m_mapView.set_at(strAddress, dynamic_cast < netshareclient::view * > (create_view(::ca::get_type_info < netshareclient::view > (), get_document(), this, 102)));
            bNew = true;
         }
         if(m_mapView[strAddress] != NULL)
         {
            SetPane(1, m_mapView[strAddress], false);
            layout();
         }
         if(bNew)
         {
            m_mapView[strAddress]->netshare(get_document()->m_strAddress);
         }
      }
   }

} // namespace netshareclient