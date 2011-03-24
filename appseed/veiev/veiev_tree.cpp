#include "StdAfx.h"

namespace veiev
{

   tree::tree(::ca::application * papp) :
      ca(papp),
      ::ca::data_container(papp),
      ::userbase::view(papp),
      ::user::scroll_view(papp),
      ::ex1::tree(papp),
      ::user::tree(papp),
      ::veiev::tree_data(papp),
      ::veiev::tree_interface(papp),
      m_scrollbarHorz(papp),
      m_scrollbarVert(papp),
      ex1::tree_data(papp),
      ::ca::data(papp)
   {
      m_pscrollbarHorz = &m_scrollbarHorz;
      m_pscrollbarVert = &m_scrollbarVert;
      m_pdata = this;

   }

   tree::~tree()
   {
   }


   void tree::OnDraw(::ca::graphics * pdc)
   {
      UNREFERENCED_PARAMETER(pdc);
   }


   void tree::_001InstallMessageHandling(::user::win::message::dispatch * pinterface)
   {
      ::userbase::view::_001InstallMessageHandling(pinterface);
      veiev::tree_interface::_001InstallMessageHandling(pinterface);
      IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &tree::_001OnCreate);
      IGUI_WIN_MSG_LINK(WM_TIMER, pinterface, this, &tree::_001OnTimer);
   }

   void tree::_001OnCreate(gen::signal_object * pobj)
   {
      pobj->previous();
      if(pobj->m_bRet)
         return;
      application * papp = dynamic_cast < application * > (get_app());
      papp->m_pveievtree = this;
      SetTimer(12345, 1000, NULL);
   }


   void tree::_001OnTimer(gen::signal_object * pobj)
   {
      SCAST_PTR(::user::win::message::timer, ptimer, pobj)

      if(ptimer->m_nIDEvent == 12345)
      {
         //KillTimer(12345);
         //Application.pop3().start();
      }
   }

   void tree::create_list(ex1::tree_item * pitemParent)
   {
      if(pitemParent == NULL)
         pitemParent = get_base_item();

      m_pitem = pitemParent;

      for(int i = 0; i <  System.userset().get_size(); i++)
      {
         ::fontopus::user * pprofile = System.userset()[i];

         tree_item * pitemAccount      = new veiev::tree_item;
         pitemAccount->m_strName       = pprofile->m_strLogin;
         pitemAccount->m_iIdentation   = 0;
         pitemAccount->m_strFolder     = "";
         pitemAccount->m_pprofile      = pprofile;

         ex1::tree_item * pitem = insert_item(pitemAccount, ex1::RelativeLastChild, pitemParent);
         if(pitem != NULL)
         {
            tree_item * pitemBox          = new veiev::tree_item;
            pitemBox->m_strName           = "Caixa de Entrada";
            pitemBox->m_iIdentation       = 1;
            pitemBox->m_strFolder         = "inbox";
            pitemBox->m_pprofile          = pprofile;
            insert_item(pitemBox, ex1::RelativeLastChild, pitem);
         }
      }
   }

   void tree::_001OnOpenItem(::ex1::tree_item * pitem)
   {
      tree_item * pitemdata = (tree_item *) pitem->m_pitemdata;
      application * papp = dynamic_cast < application * > (get_app());
      if(papp->m_pveievlist == NULL)
      {
         create_context cc;
         cc.m_pCurrentDoc = get_document();
         cc.m_typeinfoNewView = typeid(right_view);
         create_view(typeid(right_view), get_document(), GetParent(), 101);
      }
      if(papp->m_pveievlist == NULL)
         return;
      ::veiev::document * pdocument = dynamic_cast < veiev::document * > (get_document());
      if(pdocument != NULL && pdocument->m_pholderVeievList != NULL)
      {
         if(pdocument->m_pholderVeievList->m_uiptraHold.get_size() > 0)
         {
            pdocument->m_pholderVeievList->m_uiptraHold[0]->ShowWindow(SW_HIDE);
         }
         pdocument->m_pholderVeievList->hold(papp->veiev::application::m_prightview);
         pdocument->m_pholderVeievList->layout();
      }
      else if(papp->veiev::application::m_pmainview == NULL)
      {
         Application.hold(papp->veiev::application::m_prightview);
      }
      else
      {
         papp->veiev::application::m_pmainview->get_pane_window(1)->ShowWindow(SW_HIDE);
         papp->veiev::application::m_pmainview->SetPane(1, papp->::veiev::application::m_prightview, false);
         papp->veiev::application::m_pmainview->layout();
      }

      pitemdata->m_pprofile->start_veiev_synch();

      get_document()->set_profile(pitemdata->m_pprofile);

      papp->m_pveievlist->open_folder(pitemdata->m_strFolder);
   }

   void tree::_001OnItemExpand(::ex1::tree_item * pdataitem)
   {
      tree_item * pitem = (tree_item *) pdataitem;
      application * papp = dynamic_cast < application * > (get_app());
      if(pitem->m_iIdentation == 0)
      {
         papp->m_pmainview->get_pane_window(1)->ShowWindow(SW_HIDE);
         papp->m_pmainview->SetPane(1, papp->::veiev::application::m_prightpaneview, false);
         papp->m_pmainview->layout();
      }

   }

   document * tree::get_document()
   {
      return dynamic_cast < document * > (::userbase::view::get_document());
   }

} // namespace veiev
