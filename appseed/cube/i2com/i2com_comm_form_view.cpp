#include "StdAfx.h"

namespace i2com
{

   comm_form_view::comm_form_view(::ca::application * papp) :
      ca(papp),
      ::user::interaction(papp),
      ::userbase::view(papp),
      ::user::scroll_view(papp),
      ::userbase::scroll_view(papp),
      ::userbase::form_view(papp),
      ::user::form(papp),
      html_form(papp),
      html_form_view(papp),
      form_view(papp),
      ::form_view(papp)
   {
   }
   
   void comm_form_view::_001InstallMessageHandling(::user::win::message::dispatch * pinterface)
   {
      form_view::_001InstallMessageHandling(pinterface);
      IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &comm_form_view::_001OnCreate);
   }

   void comm_form_view::refresh()
   {
      get_html_data()->open_document(System.dir().matter("i2com/square_form.html"));
   }

   void comm_form_view::invite()
   {
      //string strText;
      //_001GetText(strText);
      string strPath;
      strPath = "http://i2com.api.veriterse.net/post";
      strPath = System.url().set(strPath, "topic", "invite");
//      strPath = System.url().set(strPath, "message", System.url().url_encode(strInviteNode));
      strPath = System.url().set(strPath, "sessid", ApplicationUser.m_strSessid);
      strPath = System.url().set(strPath, "recipient", m_pcommview->m_strRecipient);
      string str = Application.http().get(strPath);
      //m_pcommview->m_pm_pstreamview->post(str);
      TRACE0(str);
      _001SetText("");
   }

   bool comm_form_view::BaseOnControlEvent(::user::control_event * pevent)
   {
      if(pevent->m_eevent == ::user::event_button_clicked)
      {
         if(pevent->m_puie->m_id == "invite_button")
         {
            invite();
         }
      }
      return true;
   }

   void comm_form_view::_001OnCreate(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      pobj->previous();
//      SCAST_PTR(::user::win::message::create, pcreate, pobj)
      //refresh();
/*      string filename;
      gen::property_set post;
      gen::property_set headers;
      filename = System.file().time_square();
      System.http().ms_download(
         "http://i2com.api.veriterse.net/contact",
         filename, 
         (dynamic_cast < ::fontopus::user * > (&ApplicationUser))->m_phttpcookies,
         post, headers, &ApplicationUser);
      string strResponse;
      strResponse = Application.file().as_string(filename);
      
      xml::node node(get_app());
      node.Load(strResponse);
      if(node.name == "exception" && node.GetAttrValue("id") == "not_auth")
      {
         string strUrl;
         strUrl = "http://i2com.api.veriterse.net/contact?";
         strUrl += (dynamic_cast < ::fontopus::user * > (&ApplicationUser))->m_strSessid;
         System.http().ms_download(
            strUrl,
            filename, 
            (dynamic_cast < ::fontopus::user * > (&ApplicationUser))->m_phttpcookies,
            post, headers, &ApplicationUser);
         strResponse = Application.file().as_string(filename);
         node.Load(strResponse);
      }
   
      string strFormat;
      if(node.name == "contact")
      {
         string str;
         xml::node nodeUser;
         str = "<html><head></head><body>";
         
         for(int i = 0; i < node.childs.size(); i++)
         {
            string strUrl;
            strUrl.Format("http://i2com.api.veriterse.net/::fontopus::user?id=%s", node.childs[i]->GetAttrValue("id") );
            System.http().ms_download(
               strUrl,
               filename, 
               (dynamic_cast < ::fontopus::user * > (&ApplicationUser))->m_phttpcookies,
               post, headers, &ApplicationUser);
            strResponse = Application.file().as_string(filename);
            nodeUser.Load(strResponse);
            strFormat.Format("<a href=\"i2com://communication?id=%s\">", nodeUser.find("id")->GetAttrValue("value"));
            str += strFormat;
            str += nodeUser.find("name")->GetAttrValue("value");
            str += "</a>";
         }
         str += "</body>";
         System.file().put_contents(filename, str);
         open_document(filename);*/
      //}
   }

} // namespace i2com

