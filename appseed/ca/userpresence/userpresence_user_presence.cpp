#include "framework.h"


namespace userpresence
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
      m_dwLastActivity = ::get_tick_count();
   }

   void presence::defer_pulse_user_presence()
   {
      if(::get_tick_count() - m_dwLastActivity < ((1984 + 1977) * 2))
      {
         m_iShortStatusCynceTag = status_online;
      }
      /*else if(::get_tick_count() - m_dwLastActivity < ((1984 + 1977) * 10))
      {
         m_iShortStatusCynceTag = status_away;
      }*/
      else
      {
         m_iShortStatusCynceTag = status_offline;
      }

      pulse_user_presence();

   }


   void presence::pulse_user_presence()
   {

      if(System.m_strAppName == "netnode" || System.m_strAppName == "simpledbcfg")
         return;

      string strHost = Application.file().as_string(System.dir().appdata("database\\text\\last_good_known_fontopus_com.txt"));
      stringa straRequestingServer;
      straRequestingServer.add("api.ca2.cc");
      straRequestingServer.add("eu-api.ca2.cc");
      straRequestingServer.add("asia-api.ca2.cc");
      if(!straRequestingServer.contains_ci(strHost))
      {
         strHost = "api.ca2.cc";
      }

      string strUrl = "https://" + strHost + "/i2com/pulse_user_presence";
      System.url().set(strUrl, "short_status", gen::str::from(m_iShortStatusCynceTag));
      System.url().set(strUrl, "long_status", m_strLongStatus);
      Application.http().get(strUrl);
   }


} // namespace ca5



