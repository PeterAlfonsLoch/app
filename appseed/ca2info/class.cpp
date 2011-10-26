#include "StdAfx.h"

namespace ca2info
{

   ca2info_class::ca2info_class(::ca::application * papp) :
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

   ca2info_class::~ca2info_class()
   {
   }

   void ca2info_class::perform()
   {
      ip_enum::enumerate();
      form_document * pdoc = dynamic_cast < form_document * > (m_ptemplatePane->open_document_file(::ca::create_context_sp()));
      userex::pane_tab_view * pview = dynamic_cast < userex::pane_tab_view * > (pdoc->get_view());
      pview->set_view_creator(this);
      rect rectOpen;
      System.get_screen_rect(rectOpen);
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

   void ca2info_class::on_create_view(::user::view_creator_data * pcreatordata)
   {
      switch(pcreatordata->m_id)
      {
      case 1:
         {
         }
         break;
      case 2:
         {
         }
         break;
      }
   }



   bool ca2info_class::BaseOnControlEvent(::user::form * pview, ::user::control_event * pevent)
  {
     UNREFERENCED_PARAMETER(pview);
   /*if(pevent->m_eevent == ::user::event_set_check
   && pevent->m_bUser)
   {
      string strStatus = pevent->m_puie->m_id;
      if(gen::str::begins_eat(strStatus, "check_"))
      {
         ::user::check_box * pcheck = dynamic_cast < ::user::check_box * > (pevent->m_puie);
         if(pcheck->_001GetCheck() == check::checked)
         {
            string strRet;
            gen::property_set headers;
            System.http().ms_get("http://ca2info.api.veriterse.net/set?value=" + strStatus,
               strRet, gen::property_set(), headers, System.user().get_user()); 
         }
         m_pviewServer->SetTimer(12522, 5, NULL);
         
      }*/
/*   }
   else*/
     if(pevent->m_eevent == ::user::event_timer)
   {
      if(pevent->m_uiEvent == 12521)
      {
         update_view();
      }
      else if(pevent->m_uiEvent == 12522)
      {
         m_pviewServer->KillTimer(12522);
         update_view();
      }
   }
   return false;
}


   void ca2info_class::OnBeforeNavigate2(html::data * pdata, var & varUrl, DWORD nFlags, const char * lpszTargetFrameName, byte_array& baPostedData, const char * lpszHeaders, BOOL* pbCancel)
   {
      UNREFERENCED_PARAMETER(pdata);
      UNREFERENCED_PARAMETER(nFlags);
      UNREFERENCED_PARAMETER(lpszTargetFrameName);
      UNREFERENCED_PARAMETER(baPostedData);
      UNREFERENCED_PARAMETER(lpszHeaders);
      string str(varUrl);
      if(gen::str::begins_eat(str, "ca2info_class://"))
      {
         m_pviewServer->GetTopLevelParent()->EndModalLoop(IDOK);
         m_pviewServer->GetTopLevelParent()->ShowWindow(SW_HIDE);
         *pbCancel = TRUE;
      }
   }

   BOOL ca2info_class::EnumCallbackFunction(int nAdapter, const in_addr& address)
   {
      UNREFERENCED_PARAMETER(nAdapter);
      string strIpAddress = inet_ntoa(address);
      m_straIp.add(strIpAddress);
      return TRUE;
   }

   void ca2info_class::update_view()
   {
      string str;
      string strHtml;
      strHtml = "<html><head></head><body>";
      strHtml += "<h1>ca2info</h1>";
//      stringa & straStatus = m_straStatus;
      string strStatus;
      string strVersionShift;
      string strVersionPath = System.dir().module();
      System.file().path().eat_end_level(strVersionPath, 2, "\\");
      if(System.dir().name(strVersionPath).CompareNoCase("stage") == 0)
      {
         strVersionShift = "stage";
      }
      else
      {
         strVersionShift = "basis";
      }

      
      string strBuildAvailable;
      try
      {
         if(!System.http().get("http://spaignition.api.veriterse.net/query?node=build&version=" + strVersionShift, strBuildAvailable))
            strBuildAvailable = "Failed to get build from server spaignition.api.veriterse.net";
      }
      catch(...)
      {
         strBuildAvailable = "Failed to get build from server spaignition.api.veriterse.net";
      }
      string strBuild = Application.file().as_string(System.dir().path(strVersionPath, "app\\build.txt"));

      strHtml += "<span style=\"color: #aaaaaa;\">";
      strHtml += "version:";
      strHtml += "</span>";
      strHtml += "<br/>";
      strHtml += strVersionShift;
      strHtml += "<br/>";
      strHtml += "<br/>";
      strHtml += "<span style=\"color: #aaaaaa;\">";
      strHtml += "installed build number:";
      strHtml += "</span>";
      strHtml += "<br/>";
      strHtml += strBuild;
      strHtml += "<br/>";
      strHtml += "<br/>";
      strHtml += "<span style=\"color: #aaaaaa;\">";
      strHtml += "available build number:";
      strHtml += "</span>";
      strHtml += "<br/>";
      strHtml += strBuildAvailable;
      strHtml += "<br/>";
      strHtml += "<br/>";

      strHtml += "</body></html>";

      Application.file().put_contents(m_strViewPath, strHtml);
      m_pdocServer->open_document(m_strViewPath);
   }

} // namespace ca2info_class
