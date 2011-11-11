#include "StdAfx.h"


namespace mediaplaylist
{

   tree_view::tree_view(::ca::application * papp) :
      ca(papp),
      ex1::tree(papp),
      user::tree(papp),
      mediaplaylist::tree_data(papp),
      mediaplaylist::tree_base(papp),
      data_container(papp),
      ::userbase::view(papp),
      ::user::scroll_view(papp),
      ex1::tree_data(papp),
      ::ca::data(papp)
   {
      ::ca::data_container::m_spdata = this;
      m_etranslucency = TranslucencyPresent;

   }

   tree_view::~tree_view()
   {
   }


   void tree_view::OnDraw(::ca::graphics * pdc)
   {
      UNREFERENCED_PARAMETER(pdc);
   }


   void tree_view::install_message_handling(::user::win::message::dispatch * pinterface)
   {
      ::userbase::view::install_message_handling(pinterface);
      ::mediaplaylist::tree_base::install_message_handling(pinterface);
      IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &tree_view::_001OnCreate);
      IGUI_WIN_MSG_LINK(WM_TIMER, pinterface, this, &tree_view::_001OnTimer);
   }

   void tree_view::_001OnCreate(gen::signal_object * pobj)
   {
      pobj->previous();
      if(pobj->m_bRet)
         return;
      SetTimer(12345, 1000, NULL);
   }


   void tree_view::_001OnTimer(gen::signal_object * pobj)
   {
      SCAST_PTR(::user::win::message::timer, ptimer, pobj)

      if(ptimer->m_nIDEvent == 12345)
      {
         //KillTimer(12345);
         //System.pop3().start();
      }
   }

   void tree_view::_001OnOpenItem(::ex1::tree_item * pitem)
   {
      UNREFERENCED_PARAMETER(pitem);
      /*::mediaplaylist::tree_item * pitemdata = (::mediaplaylist::tree_item *) pitem->m_pitemdata;
      if(Application.mediaplaylist::application::m_pmaillist == NULL)
      {
         create_context cc;
         cc.m_pCurrentDoc = get_document();
         cc.m_typeinfoNewView = ::ca::get_type_info < right_view > ();
         create_view(::ca::get_type_info < right_view > (), get_document(), GetParent(), 101);
      }
      if(Application.mediaplaylist::application::m_pmaillist == NULL)
         return;
      ::cube::mediaplaylist::document * pdocument = dynamic_cast < ::cube::mediaplaylist::document * > (get_document());
      if(pdocument != NULL && pdocument->m_pholderMailList != NULL)
      {
         if(pdocument->m_pholderMailList->m_uiptraHold.get_size() > 0)
         {
            pdocument->m_pholderMailList->m_uiptraHold[0]->ShowWindow(SW_HIDE);
         }
         pdocument->m_pholderMailList->hold(Application.mediaplaylist::application::m_prightview);
         pdocument->m_pholderMailList->layout();
      }
      else if(Application.mediaplaylist::application::m_pmainview == NULL)
      {
         Application.hold(Application.mediaplaylist::application::m_prightview);
      }
      else
      {
         Application.mediaplaylist::application::m_pmainview->get_pane_window(1)->ShowWindow(SW_HIDE);
         Application.mediaplaylist::application::m_pmainview->SetPane(1, Application.mediaplaylist::application::m_prightview, false);
         Application.mediaplaylist::application::m_pmainview->layout();
      }

      pitemdata->m_paccount->m_pop3.start();

      get_document()->set_account(pitemdata->m_paccount);

      Application.mediaplaylist::application::m_pmaillist->open_folder(pitemdata->m_strFolder);*/
   }

   void tree_view::_001OnItemExpand(::ex1::tree_item * pdataitem)
   {
      UNREFERENCED_PARAMETER(pdataitem);
      /*::mediaplaylist::tree_item * pitem = (::mediaplaylist::tree_item *) pdataitem;

      if(pitem->m_iIdentation == 0)
      {
         Application.mediaplaylist::application::m_pmainview->get_pane_window(1)->ShowWindow(SW_HIDE);
         Application.mediaplaylist::application::m_pmainview->SetPane(1, Application.mediaplaylist::application::m_prightpaneview, false);
         Application.mediaplaylist::application::m_pmainview->layout();
      }*/

   }

   document * tree_view::get_document()
   {
      return dynamic_cast < document * > (::userbase::view::get_document());
   }


   void tree_view::on_update(::view * pSender, LPARAM lHint, ::radix::object* pHint)
   {
      UNREFERENCED_PARAMETER(pSender);
      UNREFERENCED_PARAMETER(lHint);
      UNREFERENCED_PARAMETER(pHint);
      get_base_item()->delete_descendants();
      create_tree(&get_document()->m_xmlnode);
   }

} // namespace mediaplaylist


