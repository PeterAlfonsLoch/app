#include "StdAfx.h"

namespace netshareclient
{

   bergedge::bergedge(application * papp) :
      ca(papp)
   {
      m_papp = papp;
      m_ptemplatePane = new ::userbase::single_document_template(
         papp,
         "system/form",
         &typeid(form_document),
         &typeid(simple_frame_window),
         &typeid(userex::pane_tab_view));
   }

   bergedge::~bergedge()
   {
      
   }

   string bergedge::get_server()
   {
      form_document * pdoc = dynamic_cast < form_document * > (m_ptemplatePane->open_document_file(NULL, TRUE, Application.m_puiInitialPlaceHolderContainer));
      userex::pane_tab_view * pview = dynamic_cast < userex::pane_tab_view * > (pdoc->get_view());
      pview->set_create_view(this);
      rect rectOpen;
      Application.get_screen_rect(rectOpen);
      int iWidth = rectOpen.width();
      int iHeight = rectOpen.width();
      rectOpen.deflate(iWidth / 3, iHeight / 3);
      pview->GetParentFrame()->SetWindowPos(ZORDER_TOP, rectOpen.left,
         rectOpen.top,
         rectOpen.width(), rectOpen.height(), SWP_SHOWWINDOW);
      m_ptabview = pview;
      pview->add_tab("netshareclient", 1);
      pview->GetParentFrame()->RedrawWindow();
      pview->set_cur_tab_by_id(1);
      return m_strServer;
   }

   void bergedge::on_create_view(view_data * pviewdata)
   {
      switch(pviewdata->m_id)
      {
      case 1:
         {
            m_pdocServer = Application.create_form(this, m_ptabview);
            if(m_pdocServer != NULL)
            {
               m_pviewServer = dynamic_cast < form_view * > (m_pdocServer->get_view());
               m_pviewServer->m_pcallback = this;
               
               m_pviewServer->get_html_data()->open_document("https://fontopus.com/ca2api/i2com/select_netshareserver");
               pviewdata->m_pdoc = m_pdocServer;
               pviewdata->m_pwnd = m_pviewServer->GetParentFrame();
            }
         }
         break;
      case 2:
         {
         }
         break;
      }
   }

   bool bergedge::BaseOnControlEvent(::user::form * pview, ::user::control_event * pevent)
   {
      if(pevent->m_eevent == ::user::event_button_clicked)
      {
         if(pevent->m_puie->m_id == "submit")
         {
            ::user::interaction * pguie = m_pviewServer->GetChildByName("server");
            text_interface * ptext = dynamic_cast < text_interface * > (pguie);
            ptext->_001GetText(m_strServer);
           // m_ptabview->GetTopLevelParent()->EndModalLoop(IDOK);
            //m_ptabview->GetParentFrame()->ShowWindow(SW_HIDE);
            m_ptemplatePane->close_all_documents(false);
         }
      }
      return false;
   }

   void bergedge::OnBeforeNavigate2(html::data * pdata, const char * lpszUrl, DWORD nFlags, const char * lpszTargetFrameName, byte_array& baPostedData, const char * lpszHeaders, BOOL* pbCancel)
   {
      string str(lpszUrl);
      if(gen::str::begins_eat(str, "http://netshare.bergedge.com/?"))
      {
         gen::property_set set(get_app());
         set.parse_url_query(str);
         m_strServer = set["uri"];
         //m_ptabview->GetTopLevelParent()->EndModalLoop(IDOK);
         //m_ptabview->GetParentFrame()->ShowWindow(SW_HIDE);

         netshareclient::application * papp = dynamic_cast < netshareclient::application * > (get_app());
         document * pdoc = dynamic_cast < document * > (papp->m_pdoctemplate->open_document_file(NULL, TRUE, Application.m_puiInitialPlaceHolderContainer));
         view * pview = pdoc->get_typed_view < view > ();
         pview->m_strServer = m_strServer;
         pview->m_pthread = new netshareclient::thread(get_app());
         pview->m_pthread->m_tunnel.m_pview = pview;
         pview->m_pthread->m_tunnel.m_parea = pview->m_parea;
         pview->m_pthread->m_tunnel.m_strUrl = "https://" + pview->m_strServer + "/";
         pview->m_pthread->m_tunnel.m_host = pview->m_strServer;
         pview->m_pthread->m_tunnel.m_port = 443;
         pview->GetTopLevelFrame()->ShowWindow(SW_SHOW);
         pview->m_pthread->Begin();

         m_pviewServer->GetTypedParent < simple_frame_window >()->PostMessage(WM_CLOSE);

         *pbCancel = TRUE;
      }
   }

} // namespace netshareclient
