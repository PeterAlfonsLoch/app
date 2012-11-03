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

      m_dwAlive = ::GetTickCount();

      if(!cube1::application::initialize())
         return false;

      ensure_app_interest();

      return true;
   }

   BOOL CALLBACK application::GetAppsEnumWindowsProc(oswindow oswindow, LPARAM lParam)
   {
      application * papp = (application *) lParam;
      DWORD dwptr;
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



   void application::update_app_interest()
   {
      EnumWindows(GetAppsEnumWindowsProc, (LPARAM) (application *) (this));
   }

   void application::ensure_app_interest()
   {
      for(int i = 0; i < m_straAppInterest.get_count(); i++)
      {
         if(m_straAppInterest[i] != m_strAppName
            && !::IsWindow(m_mapAppInterest[m_straAppInterest[i]]))
         {
            System.assert_running_local(m_straAppInterest[i]);
         }
      }
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
         ::ShowWindow(oswindow, SW_RESTORE);
      }
   }

   int application::send_simple_command(const char * psz, void * osdataSender)
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

   int application::send_simple_command(void * osdata, const char * psz, void * osdataSender)
   {
      ::oswindow oswindow = (::oswindow) osdata;
      if(!::IsWindow)
         return -1;
      COPYDATASTRUCT cds;
      memset(&cds, 0, sizeof(cds));
      cds.dwData = 198477;
      cds.cbData = (DWORD) strlen(psz);
      cds.lpData = (PVOID) psz;
      return (int) SendMessage(oswindow, WM_COPYDATA, (WPARAM) osdataSender, (LPARAM) &cds);
   }

   void application::request(::ca::create_context * pcreatecontext)
   {
      ::cube1::application::request(pcreatecontext);
   }


} //namespace cube2
