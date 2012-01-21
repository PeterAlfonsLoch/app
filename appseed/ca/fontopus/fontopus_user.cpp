#include "StdAfx.h"


namespace fontopus
{


   user::user(::ca::application * papp) :
      ca(papp)
   {

      m_ppresence       = NULL;
      m_phttpcookies    = new ::http::cookies();
      m_pifs            = NULL;

   }

   user::~user()
   {
      if(m_phttpcookies != NULL)
         delete m_phttpcookies;
   }

   void user::start_veiev_synch()
   {
      gen::signal_object * psignal = new gen::signal_object();
      gen::emit(get_app(), this, &user::on_end_veiev_synch, this, &user::veiev_synch, psignal);
   }


   bool user::initialize()
   {

      Application.defer_initialize_user_presence();

      return true;

   }

   bool user::create_ifs()
   {

      if(get_app()->is_system()
      || get_app()->is_session()
      || get_app()->is_cube()
      || get_app()->is_bergedge())
         return false;


      if(m_strLogin == carlosgustavocecynlundgren
      || m_strLogin == camilosasuketsumanuma)
         return false;

      
      if(m_pifs != NULL)
      {
         return true;
      }

      m_pifs = Session.m_pifs;

      return true;

   }

   void user::veiev_synch(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      int iRestart = 0;
restart:
      if(iRestart >= 10)
         return;
      string strPath;
      var rec = Application.db().veiev_post().last();
      rec.propset().set_app(get_app());
      rec.propset().remove_by_name("message");
      strPath = "http://europe001.veiev.api.laborserver.net/get?" + rec.propset().get_http_post();
      gen::property_set post(get_app());
      gen::property_set headers(get_app());
      gen::property_set set(get_app());
      set["interactive_user"] = true;
      string str;
      Application.http().get(strPath, str, post, headers, set);
      str.trim();
      if(str.has_char())
      {
         xml::document doc(get_app());
         doc.load(str);
         xml::node & node = *doc.get_root();
         string strThread;
         if(node.m_strName == "messages" && node.get_children_count() > 0)
         {
            for(int i = 0; i < node.get_children_count(); i++)
            {
               xml::node * pnodeMessage = node.child_at(i);
               string strSender;
               string strBody;
               xml::node * pnodeSender = pnodeMessage->get_child("sender");
               if(pnodeSender != NULL)
                  strSender = pnodeSender->m_strValue;
//               int iLength = strSender.get_length();
               xml::node * pnodeBody = pnodeMessage->get_child("body");
               if(pnodeBody != NULL)
               {
                  strBody = pnodeBody->m_strValue;
                  if(pnodeMessage->m_strName == "message")
                  {
                     strBody = pnodeBody->m_strValue;
                     pnodeBody->attrs()["message"] = strBody;
                     Application.db().veiev_post().write(pnodeBody->attrs());
                  }
               }
            }
            iRestart++;
            goto restart;
         }
      }


   }

   void user::on_end_veiev_synch(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }

   string user::get_sessid(const char * pszText, bool bInteractive)
   {
      if(pszText == NULL)
      {
         pszText = "https://fontopus.com/";
      }
      string strText(pszText);
      if(strText.is_empty())
      {
         strText = "https://fontopus.com/";
      }
      strText = System.url().get_server(strText);
      if(strText.is_empty())
         strText = pszText;
      string strSessId = m_sessionidmap[strText];
      if(strSessId.has_char())
         return strSessId;
      class validate authuser(get_app(), "system\\user\\authenticate.xhtml", true, bInteractive);
      user * puser = authuser.get_user(pszText);
      if(puser == NULL)
         strSessId = "not_auth";
      else
      {
         strSessId = puser->m_strFontopusServerSessId;
         if(puser->m_strRequestingServer != strText)
            strSessId = "not_auth";
         else if(strSessId.is_empty())
            strSessId = "not_auth";
         delete puser;
      }
      m_sessionidmap[strText] = strSessId;
      return strSessId;
    }

   void user::set_sessid(const char * pszSessid, const char * pszText)
   {
      if(pszText == NULL)
      {
         pszText = "https://fontopus.com/";
      }
      string strText(pszText);
      if(strText.is_empty())
      {
         strText = "https://fontopus.com/";
      }
      strText = System.url().get_server(strText);
      m_sessionidmap[strText] = pszSessid;
   }


} // namespace fontopus


