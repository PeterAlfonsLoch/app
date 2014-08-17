#include "framework.h"


namespace userpresence
{


   presence::presence(sp(::base::application) papp) :
      element(papp)
   {
      m_iShortStatusWayTag = status_online;
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

      int iStatus = (int) m_iShortStatusWayTag;
      if(::get_tick_count() - m_dwLastActivity < ((5000) * 4))
      {
         iStatus = status_online;
      }
      /*else if(::get_tick_count() - m_dwLastActivity < ((5000) * 10))
      {
         m_iShortStatusWayTag = status_away;
      }*/
      else
      {
         iStatus = status_offline;
      }

      if(iStatus == m_iShortStatusWayTag && (::get_tick_count() - m_dwLastPulse) <((5000) * 2))
         return;

      m_iShortStatusWayTag = iStatus;

      pulse_user_presence();

   }


   void presence::pulse_user_presence()
   {

      m_dwLastPulse = ::get_tick_count();

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
      System.url().string_set(strUrl, "short_status", ::str::from(m_iShortStatusWayTag));
      System.url().string_set(strUrl, "long_status", m_strLongStatus);

      property_set set(get_app());

      Application.http().get(strUrl, set);

   }


} // namespace userpresence



