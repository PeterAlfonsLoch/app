#include "StdAfx.h"

namespace netnodecfg
{

   netnode::netnode(application * papp) :
      ca(papp),
      ip_enum(papp)
   {
      m_papp = papp;
      m_ptemplatePane = new ::userbase::single_document_template(
         papp,
         "system/form",
         &typeid(form_document),
         &typeid(simple_frame_window),
         &typeid(userex::pane_tab_view));
   }

   netnode::~netnode()
   {
   }

   void netnode::set_configuration()
   {
      ip_enum::enumerate();
      form_document * pdoc = dynamic_cast < form_document * > (m_ptemplatePane->open_document_file(NULL, TRUE, System.m_puiInitialPlaceHolderContainer));
      userex::pane_tab_view * pview = pdoc->get_typed_view < userex::pane_tab_view > ();
      pview->set_create_view(this);
      HWND hwndDesktop = ::GetDesktopWindow();
      rect rectOpen;
      ::GetWindowRect(hwndDesktop, rectOpen);
      /*int iWidth = rectOpen.width();
      int iHeight = rectOpen.width();
      rectOpen.deflate(iWidth / 5, iHeight / 5);
      /*pview->GetParentFrame()->SetWindowPos(ZORDER_TOP, rectOpen.left,
         rectOpen.top,
         rectOpen.width(), rectOpen.height(), SWP_SHOWWINDOW);*/
      m_ptabview = pview;
      pview->add_tab("netnode configuration", 1);
      pview->set_cur_tab_by_id(1);
      pview->GetTopLevelFrame()->RunModalLoop();
   }

   void netnode::on_create_view(view_data * pviewdata)
   {
      switch(pviewdata->m_id)
      {
      case 1:
         {
            m_pdocServer = System.create_form(this, m_ptabview);
            if(m_pdocServer != NULL)
            {
               m_pviewServer = m_pdocServer->get_typed_view < form_view > ();
               m_pviewServer->m_pcallback = this;

               string strIpEnum = System.file().time_square();

               string str;
               string strHtml;
               strHtml = "<html><head></head><body>";
               strHtml += "<h1>netnode configuation</h1>";
               strHtml += "<h2>HTTP</h2>";
               stringa stra;
               string strCheck;
               stra = System.db().data_load("netnode", ::database::id(), ::database::id()); 
               for(int i = 0; i < m_straIp.get_size(); i++)
               {
                  if(stra.contains(m_straIp[i]))
                     strCheck = "checked";
                  else
                     strCheck = "unchecked";

                  str.Format("<input type=\"checkbox\" id=\"check%d\" value=\"%s\"/>%s<br /><br />", i, strCheck, m_straIp[i]);
                  strHtml += str;
               }
               strHtml += "<h2>HTTPS</h2>";
               stra.remove_all();
               stra = System.db().data_load("netnodes", ::database::id(), ::database::id()); 
               for(int i = 0; i < m_straIp.get_size(); i++)
               {
                  if(stra.contains(m_straIp[i]))
                     strCheck = "checked";
                  else
                     strCheck = "unchecked";


                  string strCert = System.db().data_load("netnodec", m_straIp[i], ::database::id()); 

                  str.Format("<input type=\"checkbox\" id=\"scheck%d\" value=\"%s\"/>%s<input type=\"text\" id=\"cert%d\" value=\"%s\"/><br /><br />", i, strCheck, m_straIp[i], i, strCert);
                  strHtml += str;
               }
               strHtml += "<input type=\"button\" id=\"submit\" value=\"Fechar\"/>";
               strHtml += "</body></html>";

               System.file().put_contents(strIpEnum, strHtml);


               m_pviewServer->get_html_data()->open_document(strIpEnum);
               pviewdata->m_pdoc = m_pdocServer;
               pviewdata->m_pwnd = m_pviewServer->GetParentFrame();

            }
         }
         break;
      }
   }



   bool netnode::BaseOnControlEvent(::user::form * pview, ::user::control_event * pevent)
   {
      UNREFERENCED_PARAMETER(pview);
      if(pevent->m_eevent == ::user::event_button_clicked)
      {
         if(pevent->m_puie->m_id == "submit")
         {
            string str;
            stringa straSubmit;
            for(int i = 0; i < m_straIp.get_size(); i++)
            {
               str.Format("check%d", i);
               ::user::interaction * pguie = m_pviewServer->GetChildById(str);
               ::user::check_interface * pcheck = dynamic_cast < ::user::check_interface * > (pguie);
               if(pcheck->_001GetCheck() == check::checked)
               {
                  straSubmit.add(m_straIp[i]);
               }
            }
            System.db().data_save("netnode", ::database::id(), ::database::id(), straSubmit);
            straSubmit.remove_all();
            for(int i = 0; i < m_straIp.get_size(); i++)
            {
               str.Format("scheck%d", i);
               ::user::interaction * pguie = m_pviewServer->GetChildById(str);
               ::user::check_interface * pcheck = dynamic_cast < ::user::check_interface * > (pguie);
               if(pcheck->_001GetCheck() == check::checked)
               {
                  straSubmit.add(m_straIp[i]);
               }
               string strCert;
               str.Format("cert%d", i);
               pguie = m_pviewServer->GetChildById(str);
               ::text_interface * ptext = dynamic_cast < ::text_interface * > (pguie);
               ptext->_001GetText(strCert);
               System.db().data_save("netnodec", m_straIp[i], ::database::id(), strCert);
            }
            System.db().data_save("netnodes", ::database::id(), ::database::id(), straSubmit);
            m_pviewServer->GetTopLevelParent()->EndModalLoop(IDOK);
            m_pviewServer->GetTopLevelParent()->ShowWindow(SW_HIDE);
         }
      }
      return false;
   }


   void netnode::OnBeforeNavigate2(html::data * pdata, const char * lpszUrl, DWORD nFlags, const char * lpszTargetFrameName, byte_array& baPostedData, const char * lpszHeaders, BOOL* pbCancel)
   {
      UNREFERENCED_PARAMETER(nFlags);
      UNREFERENCED_PARAMETER(lpszTargetFrameName);
      UNREFERENCED_PARAMETER(baPostedData);
      UNREFERENCED_PARAMETER(lpszHeaders);
      string str(lpszUrl);
      if(gen::str::begins_eat(str, "netnodecfg://"))
      {
         m_pviewServer->GetTopLevelParent()->EndModalLoop(IDOK);
         m_pviewServer->GetTopLevelParent()->ShowWindow(SW_HIDE);
         *pbCancel = TRUE;
      }
   }

   BOOL netnode::EnumCallbackFunction(int nAdapter, const in_addr& address)
   {
      UNREFERENCED_PARAMETER(nAdapter);
      string strIpAddress = inet_ntoa(address);
      m_straIp.add(strIpAddress);
      return TRUE;
   }


} // namespace netnodecfg
