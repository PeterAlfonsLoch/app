#include "StdAfx.h"

namespace fontopus
{

   user::user(::ca::application * papp) :
      ca(papp)
   {
      m_ppresence = NULL;
      m_phttpcookies = new ::http::cookies();
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

   void user::veiev_synch(gen::signal_object * pobj)
   {
      int iRestart = 0;
restart:
      if(iRestart >= 10)
         return;
      string strPath;
      var rec = System.db().veiev_post().last();
      rec.propset().set_app(get_app());
      rec.propset().remove_by_name("message");
      strPath = "http://veiev.api.veriterse.net/get?" + string("sessid=") + ApplicationUser.m_strSessid + "&" + rec.propset().get_http_post();
      string str = Application.http().get(strPath);
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
                     System.db().veiev_post().write(pnodeBody->attrs());
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
   }



} // namespace fontopus


