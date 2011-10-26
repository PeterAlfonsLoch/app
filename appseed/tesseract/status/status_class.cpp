#include "StdAfx.h"

namespace status
{

   status_class::status_class(::ca::application * papp) :
      ca(papp),
      ip_enum(papp)
   {
      m_papp = papp;
      m_ptemplatePane = new ::userbase::single_document_template(
         papp,
         "system/form",
         ::ca::get_type_info < form_document > (),
         ::ca::get_type_info < simple_frame_window > (),
         ::ca::get_type_info < userex::pane_tab_view > ());

      m_straStatus.add("online");
      m_straStatus.add("offline");

   }

   status_class::~status_class()
   {
   }

   void status_class::perform()
   {
      ip_enum::enumerate();
      form_document * pdoc = dynamic_cast < form_document * > (m_ptemplatePane->open_document_file());
      userex::pane_tab_view * pview = pdoc->get_typed_view < userex::pane_tab_view > ();
      pview->set_view_creator(this);
      rect rectOpen;
      HWND hwndDesktop = ::GetDesktopWindow();
      ::GetWindowRect(hwndDesktop, rectOpen);
      int iWidth = rectOpen.width();
      int iHeight = rectOpen.width();
      rectOpen.deflate(iWidth / 5, iHeight / 5);
      pview->GetParentFrame()->SetWindowPos(ZORDER_TOP, rectOpen.left,
         rectOpen.top,
         rectOpen.width(), rectOpen.height(), SWP_SHOWWINDOW);
      m_ptabview = pview;
      pview->add_tab("votagus login", 1);
      pview->add_tab("network", 2);
      pview->set_cur_tab_by_id(1);
   }

   void status_class::on_create_view(::user::view_creator_data * pcreatordata)
   {
      switch(pcreatordata->m_id)
      {
      case 1:
         {
            m_pdocServer = System.create_form(this, m_ptabview);
            if(m_pdocServer != NULL)
            {
               m_pviewServer = m_pdocServer->get_typed_view < form_view > ();
               m_pviewServer->m_pcallback = dynamic_cast < ::user::form_callback * > (this);

               m_strViewPath = System.file().time_square();

               //string strUsername;
               //string strPassword;
               //primitive::memory strUsernameEncrypt;
               //primitive::memory strPasswordEncrypt;
               string strSection;
               strSection.Format("license_auth");
               string strDir;
               strDir = Application.dir().usersystemappdata(Application.dir().default_os_user_path_prefix(), strSection);
               //               bool bOk = false;
               /*               System.dir().mk(strDir);
               ex1::filesp spfile(get_app());
               spfile->open(System.dir().path(strDir, "00001"), ::ex1::file::type_binary | ::ex1::file::mode_read_write);
               if(spfile->IsOpened())
               {
               strUsernameEncrypt.FullLoad(spfile);
               spfile->close();
               }
               spfile->open(System.dir().path(strDir, "00002"), ::ex1::file::type_binary | ::ex1::file::mode_read_write);
               if(spfile->IsOpened())
               {
               strPasswordEncrypt.FullLoad(spfile);
               spfile->close();
               }
               if(strUsernameEncrypt.get_size() > 0)
               {
               primitive::memory strUsernameDecrypt;
               primitive::memory strPasswordDecrypt;
               System.crypt().decrypt(strUsernameDecrypt, strUsernameEncrypt);
               System.crypt().decrypt(strPasswordDecrypt, strPasswordEncrypt);
               strUsernameDecrypt.ToAsc(strUsername);
               strPasswordDecrypt.ToAsc(strPassword);*/
               m_pviewServer->get_html_data()->m_puser = &ApplicationUser;
               //m_pviewServer->m_pcontainer->m_strUser = strUsername;
               //m_pviewServer->m_pcontainer->m_strPassword = strPassword;
               update_view();
               m_pviewServer->SetTimer(12521, 5000, NULL);
               pcreatordata->m_pdoc = m_pdocServer;
               pcreatordata->m_pwnd = m_pviewServer->GetParentFrame();

               //}
            }
         }
         break;
      case 2:
         {
         }
         break;
      }
   }



   bool status_class::BaseOnControlEvent(::user::form * pview, ::user::control_event * pevent)
   {
      UNREFERENCED_PARAMETER(pview);
      if(pevent->m_eevent == ::user::event_set_check
         && pevent->m_bUser)
      {
         string strStatus = pevent->m_puie->m_id;
         if(gen::str::begins_eat(strStatus, "check_"))
         {
            ::user::check_box * pcheck = dynamic_cast < ::user::check_box * > (pevent->m_puie);
            if(pcheck->_001GetCheck() == check::checked)
            {
               string strRet;
               gen::property_set post;
               gen::property_set headers;
               gen::property_set set;
               Application.http().get("http://status.api.veriterse.net/set?value=" + strStatus, strRet, post, headers, set, NULL, &ApplicationUser); 
            }
            m_pviewServer->SetTimer(12522, 5, NULL);

         }
      }
      else if(pevent->m_eevent == ::user::event_timer)
      {
         if(pevent->m_uiEvent == 12521)
         {
            m_pviewServer->KillTimer(12521);
            update_view();
            m_pviewServer->SetTimer(12521, 5000, NULL);
         }
         else if(pevent->m_uiEvent == 12522)
         {
            m_pviewServer->KillTimer(12522);
            update_view();
         }
      }
      return false;
   }


   void status_class::OnBeforeNavigate2(html::data * pdata, var & varFile, DWORD nFlags, const char * lpszTargetFrameName, byte_array& baPostedData, const char * lpszHeaders, BOOL* pbCancel)
   {
      UNREFERENCED_PARAMETER(pdata);
      UNREFERENCED_PARAMETER(nFlags);
      UNREFERENCED_PARAMETER(lpszTargetFrameName);
      UNREFERENCED_PARAMETER(baPostedData);
      UNREFERENCED_PARAMETER(lpszHeaders);
      string str(varFile);
      if(gen::str::begins_eat(str, "status_class://"))
      {
         m_pviewServer->GetTopLevelParent()->EndModalLoop(IDOK);
         m_pviewServer->GetTopLevelParent()->ShowWindow(SW_HIDE);
         *pbCancel = TRUE;
      }
   }

   BOOL status_class::EnumCallbackFunction(int nAdapter, const in_addr& address)
   {
      UNREFERENCED_PARAMETER(nAdapter);
      string strIpAddress = inet_ntoa(address);
      m_straIp.add(strIpAddress);
      return TRUE;
   }

   void status_class::update_view()
   {
      string str;
      string strHtml;
      strHtml = "<html><head></head><body>";
      strHtml += "<h1>status</h1>";
      stringa & straStatus = m_straStatus;
      string strStatus;
      gen::property_set headers;
      gen::property_set post;
      gen::property_set set;
      Application.http().get("http://status.api.veriterse.net/get", strStatus, post, headers, set, NULL, &ApplicationUser);
      string strCheck;
      for(int i = 0; i < straStatus.get_size(); i++)
      {
         if(!strcasecmp(straStatus[i], strStatus))
            strCheck = "checked";
         else
            strCheck = "unchecked";

         str.Format("<input type=\"checkbox\" id=\"check_%s\" value=\"%s\"/>%s<br /><br />", straStatus[i], strCheck, straStatus[i]);
         strHtml += str;
      }
      strHtml += "</body></html>";

      Application.file().put_contents(m_strViewPath, strHtml);
      m_pdocServer->open_document(m_strViewPath);
   }

   string status_class::get_status(var user)
   {
      string strStatus;
      gen::property_set headers;
      gen::property_set post;
      gen::property_set set;
      Application.http().get("http://status.api.veriterse.net/get?user=" + user.get_string(), strStatus,
         post, headers, set, NULL, &ApplicationUser);
      return strStatus;
   }

} // namespace status_class
