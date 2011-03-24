#include "StdAfx.h"

// 日歩路主 - Carlos Gustavo Cecyn Lundgren, Thank you!!

namespace netshareclient
{

   tree::tree(::ca::application * papp) :
      ca(papp),
      ::ca::data_container(papp),
      ::userbase::view(papp),
      ::user::scroll_view(papp),
      ::ex1::tree(papp),
      ::user::tree(papp),
      ::netshareclient::tree_data(papp),
      ::netshareclient::tree_interface(papp),
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
      netshareclient::tree_interface::_001InstallMessageHandling(pinterface);
      IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &tree::_001OnCreate);
      IGUI_WIN_MSG_LINK(WM_TIMER, pinterface, this, &tree::_001OnTimer);
   }

   void tree::_001OnCreate(gen::signal_object * pobj)
   {
      pobj->previous();
      if(pobj->m_bRet)
         return;
      application * papp = dynamic_cast < application * > (get_app());
      papp->m_pnetshareclienttree = this;
      SetTimer(12345, 1000, NULL);
   }


   void tree::_001OnTimer(gen::signal_object * pobj)
   {
	UNREFERENCED_PARAMETER(pobj);
   }

   void tree::create_list(ex1::tree_item * pitemParent)
   {
      if(pitemParent == NULL)
         pitemParent = get_base_item();

      m_pitem = pitemParent;

      for(int i = 0; i <  System.userset().get_size(); i++)
      {
         ::fontopus::user * pprofile = System.userset()[i];

         tree_item * pitemAccount      = new netshareclient::tree_item;
         pitemAccount->m_strLogin       = pprofile->m_strLogin;
         pitemAccount->m_iIdentation   = 0;
         pitemAccount->m_strFolder     = "";
         pitemAccount->m_pprofile      = pprofile;


         ex1::tree_item * pitem = insert_item(pitemAccount, ex1::RelativeLastChild, pitemParent);
         xml::node node(get_app());
         if(node.load(System.http().get("http://netshareclient.api.veriterse.net/query?query=server_list&login=" + pprofile->m_strLogin)))
         {
            for(int i = 0; i < node.get_children_count(); i++)
            {
               xml::node * pnodeServer = node.child_at(i);
               if(pitem != NULL)
               {
                  tree_item * pitemBox          = new netshareclient::tree_item;
                  pitemBox->m_strAddress           = pnodeServer->attr("address");
                  pitemBox->m_iIdentation       = 1;
                  pitemBox->m_strFolder         = "inbox";
                  pitemBox->m_pprofile          = pprofile;
                  insert_item(pitemBox, ex1::RelativeLastChild, pitem);
               }
            }
         }
      }
   }

   void tree::_001OnOpenItem(::ex1::tree_item * pitem)
   {
      tree_item * pitemdata = (tree_item *) pitem->m_pitemdata;
      application * papp = dynamic_cast < application * > (get_app());
      if(pitemdata->m_strAddress.has_char())
      {
         get_document()->netshare(pitemdata->m_strAddress);
      }
      if(papp->m_pnetshareclientlist == NULL)
      {
         create_context cc;
         cc.m_pCurrentDoc = get_document();
         cc.m_typeinfoNewView = typeid(list);
         create_view(typeid(list), get_document(), GetParent(), 101);
      }
      if(papp->m_pnetshareclientlist == NULL)
         return;
      ::netshareclient::document * pdocument = dynamic_cast < netshareclient::document * > (get_document());
      if(pdocument != NULL && pdocument->m_pholderNetshareclientList != NULL)
      {
         if(pdocument->m_pholderNetshareclientList->m_uiptraHold.get_size() > 0)
         {
            pdocument->m_pholderNetshareclientList->m_uiptraHold[0]->ShowWindow(SW_HIDE);
         }
         pdocument->m_pholderNetshareclientList->hold(papp->netshareclient::application::m_prightview);
         pdocument->m_pholderNetshareclientList->layout();
      }
      else if(papp->netshareclient::application::m_pmainview == NULL)
      {
         Application.hold(papp->netshareclient::application::m_prightview);
      }
      else
      {
         papp->netshareclient::application::m_pmainview->get_pane_window(1)->ShowWindow(SW_HIDE);
         papp->netshareclient::application::m_pmainview->SetPane(1, papp->::netshareclient::application::m_prightview, false);
         papp->netshareclient::application::m_pmainview->layout();
      }

      pitemdata->m_pprofile->start_veiev_synch();

      //      get_document()->set_profile(pitemdata->m_pprofile);

      if(pitemdata->m_strLogin.has_char())
      {
         papp->m_pnetshareclientlist->open_profile(pitemdata->m_strLogin);
      }

   }

   void tree::_001OnItemExpand(::ex1::tree_item * pdataitem)
   {
      tree_item * pitem = (tree_item *) pdataitem;
      application * papp = dynamic_cast < application * > (get_app());
      if(pitem->m_iIdentation == 0 && papp->m_pmainview != NULL)
      {
         papp->m_pmainview->get_pane_window(1)->ShowWindow(SW_HIDE);
         papp->m_pmainview->SetPane(1, papp->::netshareclient::application::m_prightpaneview, false);
         papp->m_pmainview->layout();
      }

   }

   document * tree::get_document()
   {
      return dynamic_cast < document * > (::userbase::view::get_document());
   }

} // namespace netshareclient

