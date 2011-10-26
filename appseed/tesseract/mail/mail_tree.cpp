#include "StdAfx.h"


namespace tesseract
{

   namespace mail
   {

   tree::tree(::ca::application * papp) :
      ca(papp),
      data_container(papp),
      ::userbase::view(papp),
      ::user::scroll_view(papp),
      ::ex1::tree(papp),
      ::user::tree(papp),
      ::mail::tree_data(papp),
      ::mail::tree_interface(papp),
      ex1::tree_data(papp),
      ::ca::data(papp)
   {
      ::ca::data_container::m_spdata = this;

   }

   tree::~tree()
   {
   }


   void tree::OnDraw(::ca::graphics * pdc)
   {
      UNREFERENCED_PARAMETER(pdc);
   }


   void tree::install_message_handling(::user::win::message::dispatch * pinterface)
   {
      ::userbase::view::install_message_handling(pinterface);
      ::mail::tree_interface::install_message_handling(pinterface);
      IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &tree::_001OnCreate);
      IGUI_WIN_MSG_LINK(WM_TIMER, pinterface, this, &tree::_001OnTimer);
   }

   void tree::_001OnCreate(gen::signal_object * pobj)
   {
      pobj->previous();
      if(pobj->m_bRet)
         return;
      Application.m_pmailtree = this;
      SetTimer(12345, 1000, NULL);
   }


   void tree::_001OnTimer(gen::signal_object * pobj)
   {
      SCAST_PTR(::user::win::message::timer, ptimer, pobj)

      if(ptimer->m_nIDEvent == 12345)
      {
         //KillTimer(12345);
         //System.pop3().start();
      }
   }

   void tree::create_list(ex1::tree_item * pitemParent)
   {
      if(pitemParent == NULL)
         pitemParent = get_base_item();

      m_pitem = pitemParent;

      for(int i = 0; i <  Application.m_accounta.get_size(); i++)
      {
         ::mail::account & acc               = Application.m_accounta[i];

         ::mail::tree_item * pitemAccount    = new ::mail::tree_item;
         pitemAccount->m_strName             = acc.m_strEmail;
         pitemAccount->m_iIdentation         = 0;
         pitemAccount->m_strFolder           = "";
         pitemAccount->m_paccount            = &acc;

         ex1::tree_item * pitem              = insert_item(pitemAccount, ex1::RelativeLastChild, pitemParent);
         if(pitem != NULL)
         {
            ::mail::tree_item * pitemBox     = new ::mail::tree_item;
            pitemBox->m_strName              = "Caixa de Entrada";
            pitemBox->m_iIdentation          = 1;
            pitemBox->m_strFolder            = "inbox";
            pitemBox->m_paccount             = &acc;
            insert_item(pitemBox, ex1::RelativeLastChild, pitem);
         }
      }
   }

   void tree::_001OnOpenItem(::ex1::tree_item * pitem)
   {
      ::mail::tree_item * pitemdata = (::mail::tree_item *) pitem->m_pitemdata;
      if(Application.mail::application::m_pmaillist == NULL)
      {
/*         create_context_sp cacc(get_app());
         stack < ::user::create_context > cc(cacc->m_user);
         cc->userm_pCurrentDoc = get_document();
         cc->m_typeinfoNewView = ::ca::get_type_info < right_view > ();*/
         create_view(::ca::get_type_info < right_view > (), get_document(), GetParent(), 101);
      }
      if(Application.mail::application::m_pmaillist == NULL)
         return;
      ::tesseract::mail::document * pdocument = dynamic_cast < ::tesseract::mail::document * > (get_document());
      if(pdocument != NULL && pdocument->m_pholderMailList != NULL)
      {
         if(pdocument->m_pholderMailList->m_uiptraHold.get_size() > 0)
         {
            pdocument->m_pholderMailList->m_uiptraHold[0]->ShowWindow(SW_HIDE);
         }
         pdocument->m_pholderMailList->hold(Application.mail::application::m_prightview);
         pdocument->m_pholderMailList->layout();
      }
      else if(Application.mail::application::m_pmainview == NULL)
      {
         Application.hold(Application.mail::application::m_prightview);
      }
      else
      {
         Application.mail::application::m_pmainview->get_pane_window(1)->ShowWindow(SW_HIDE);
         Application.mail::application::m_pmainview->SetPane(1, Application.mail::application::m_prightview, false);
         Application.mail::application::m_pmainview->layout();
      }

      pitemdata->m_paccount->m_pop3.start();

      get_document()->set_account(pitemdata->m_paccount);

      Application.mail::application::m_pmaillist->open_folder(pitemdata->m_strFolder);
   }

   void tree::_001OnItemExpand(::ex1::tree_item * pdataitem)
   {
      ::mail::tree_item * pitem = (::mail::tree_item *) pdataitem;

      if(pitem->m_iIdentation == 0)
      {
         Application.mail::application::m_pmainview->get_pane_window(1)->ShowWindow(SW_HIDE);
         Application.mail::application::m_pmainview->SetPane(1, Application.mail::application::m_prightpaneview, false);
         Application.mail::application::m_pmainview->layout();
      }

   }

   document * tree::get_document()
   {
      return dynamic_cast < document * > (::userbase::view::get_document());
   }

   } // namespace mail


} // namespace tesseract


