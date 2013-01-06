#include "framework.h"


namespace cube2
{


   application::application()
   {


   }

   application::~application()
   {


   }

   bool application::initialize()
   {

      m_dwAlive = ::get_tick_count();

      if(!cube1::application::initialize())
         return false;

      ensure_app_interest();

      return true;
   }


#ifdef WINDOWSEX

   BOOL CALLBACK application::GetAppsEnumWindowsProc(oswindow oswindow, LPARAM lParam)
   {
      application * papp = (application *) lParam;
      uint32_t dwptr;
      if(!::SendMessageTimeout(oswindow, WM_APP + 2000, 1, 0, SMTO_BLOCK, 10, (PDWORD_PTR) &dwptr) || dwptr != 2)
      {
         return TRUE;
      }
      if(!::SendMessageTimeout(oswindow, WM_APP + 2000, 2, 0, SMTO_BLOCK, 10, (PDWORD_PTR) &dwptr) || dwptr != 4)
      {
         return TRUE;
      }
      if(!::SendMessageTimeout(oswindow, WM_APP + 2000, 4, 0, SMTO_BLOCK, 10, (PDWORD_PTR) &dwptr) || dwptr != 5)
      {
         return TRUE;
      }
      if(!::SendMessageTimeout(oswindow, WM_APP + 2000, 5, 0, SMTO_BLOCK, 10, (PDWORD_PTR) &dwptr) || dwptr != 8)
      {
         return TRUE;
      }
      if(!::SendMessageTimeout(oswindow, WM_APP + 2000, 8, 0, SMTO_BLOCK, 10, (PDWORD_PTR) &dwptr) || dwptr != 11)
      {
         return TRUE;
      }
      if(!::SendMessageTimeout(oswindow, WM_APP + 2000, 11, 0, SMTO_BLOCK, 10, (PDWORD_PTR) &dwptr) || dwptr != 23)
      {
         return TRUE;
      }
      if(!::SendMessageTimeout(oswindow, WM_APP + 2000, 23, 0, SMTO_BLOCK, 10, (PDWORD_PTR) &dwptr) || dwptr != 33)
      {
         return TRUE;
      }
      if(::SendMessageTimeout(oswindow, WM_APP + 2000, 33, 0, SMTO_BLOCK, 10, (PDWORD_PTR) &dwptr))
      {
         if(dwptr == 1)
         {
            if(papp->m_straAppInterest.find_first("command") >= 0)
               papp->m_mapAppInterest["command"] = oswindow;
         }
         else if(dwptr == 67)
         {
            if(papp->m_straAppInterest.find_first("winactionarea") >= 0)
               papp->m_mapAppInterest["winactionarea"] = oswindow;
         }
         else if(dwptr == 68)
         {
            if(papp->m_straAppInterest.find_first("winutil") >= 0)
               papp->m_mapAppInterest["winutil"] = oswindow;
         }
         else if(dwptr == 69)
         {
            if(papp->m_straAppInterest.find_first("windesk") >= 0)
               papp->m_mapAppInterest["windesk"] = oswindow;
         }
      }

      return TRUE;

   }

#endif


   void application::update_app_interest()
   {

#ifdef WINDOWSEX

      EnumWindows(GetAppsEnumWindowsProc, (LPARAM) (application *) (this));

#else

      throw todo(get_app());

#endif

   }

   void application::ensure_app_interest()
   {

#ifndef METROWIN

      for(int32_t i = 0; i < m_straAppInterest.get_count(); i++)
      {
         if(m_straAppInterest[i] != m_strAppName && !::IsWindow(m_mapAppInterest[m_straAppInterest[i]]))
         {
            System.assert_running_local(m_straAppInterest[i]);
         }
      }

#else

      //throw todo(get_app());

#endif

   }

   oswindow application::get_ca2_app_wnd(const char * psz)
   {
      return m_mapAppInterest[psz];
   }

   bool application::initialize_instance()
   {

      if(!::cube1::application::initialize_instance())
         return false;
      if(m_psession != NULL && m_psession->m_pbergedge != NULL)
      {
         Session.m_pappCurrent = this;
      }
      return true;
   }




   void application::on_exclusive_instance_local_conflict()
   {
      m_straAppInterest.add(m_strAppName);
      update_app_interest();
      oswindow oswindow = get_ca2_app_wnd(m_strAppName);
      if(oswindow != NULL)
      {
#ifndef METROWIN
         ::ShowWindow(oswindow, SW_RESTORE);
#endif
      }
   }

   int32_t application::send_simple_command(const char * psz, void * osdataSender)
   {
      string strApp;
      stringa stra;
      stra.add_tokens(psz, "::", true);
      if(stra.get_size() > 0)
      {
         strApp = stra[0];
         oswindow oswindow = get_ca2_app_wnd(strApp);
         if(oswindow != NULL)
         {
            return send_simple_command((void *) oswindow, psz, osdataSender);
         }
      }
      return -1;
   }

   int32_t application::send_simple_command(void * osdata, const char * psz, void * osdataSender)
   {
#ifdef WINDOWSEX
      ::oswindow oswindow = (::oswindow) osdata;
      if(!::IsWindow(oswindow))
         return -1;
      COPYDATASTRUCT cds;
      memset(&cds, 0, sizeof(cds));
      cds.dwData = 198477;
      cds.cbData = (uint32_t) strlen(psz);
      cds.lpData = (PVOID) psz;
      return (int32_t) SendMessage(oswindow, WM_COPYDATA, (WPARAM) osdataSender, (LPARAM) &cds);
#else
      throw todo(get_app());
#endif
   }

   void application::request(::ca::create_context * pcreatecontext)
   {
      ::cube1::application::request(pcreatecontext);
   }


} //namespace cube2
