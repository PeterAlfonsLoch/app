#include "StdAfx.h"

namespace ca5
{

   namespace user
   {

      presence::presence(::ca::application * papp) :
         ca(papp)
      {
         m_iShortStatusCynceTag = status_online;
      }
      
      presence::~presence()
      {
      }

      void presence::report_activity()
      {
         m_dwLastActivity = ::GetTickCount();
      }

      void presence::defer_pulse_user_presence()
      {
         if(::GetTickCount() - m_dwLastActivity < ((1984 + 1977) * 11))
         {
            pulse_user_presence();
         }
      }


      void presence::pulse_user_presence()
      {
         
         if(System.m_strAppName == "netnode" || System.m_strAppName == "simpledbcfg")
            return;

         string strHost = Application.file().as_string(System.dir().appdata("database\\text\\last_good_known_fontopus_com.txt"));
         stringa straRequestingServer;
         straRequestingServer.add("fontopus.com");
         straRequestingServer.add("fontopus.eu");
         straRequestingServer.add("fontopus.asia");
         if(!straRequestingServer.contains_ci(strHost))
         {
            strHost = "fontopus.com";
         }

         string strUrl = "https://" + strHost + "/ca2api/i2com/pulse_user_presence";
         System.url().set(strUrl, "short_status", gen::str::i64toa(m_iShortStatusCynceTag));
         System.url().set(strUrl, "long_status", m_strLongStatus);
         Application.http().get(strUrl);
      }


   } // namespace user

} // namespace ca5