#include "StdAfx.h"

namespace ca84
{

   application::application()
   {
      //m_straAppInterest.add("windesk");
      //m_straAppInterest.add("verifile");
//      m_prunapp = NULL;
        m_bClientOnly = false;


   }

   application::~application()
   {
   }

   bool application::initialize()
   {
      if(!ca77::application::initialize())
         return false;

      if(!GetAudioWaveCentral().Initialize(this))
      {
         TRACE("Could not initialize Audio Wave Central");
      }

      ensure_app_interest();

      return true;
   }

   BOOL CALLBACK application::GetAppsEnumWindowsProc(      
       HWND hwnd,
       LPARAM lParam)
   {
      application * papp = (application *) lParam;
      DWORD dwptr;
      if(!::SendMessageTimeout(hwnd, WM_APP + 2000, 1, 0, SMTO_BLOCK, 10, (PDWORD_PTR) &dwptr) || dwptr != 2)
      {
         return TRUE;
      }
      if(!::SendMessageTimeout(hwnd, WM_APP + 2000, 2, 0, SMTO_BLOCK, 10, (PDWORD_PTR) &dwptr) || dwptr != 4)
      {
         return TRUE;
      }
      if(!::SendMessageTimeout(hwnd, WM_APP + 2000, 4, 0, SMTO_BLOCK, 10, (PDWORD_PTR) &dwptr) || dwptr != 5)
      {
         return TRUE;
      }
      if(!::SendMessageTimeout(hwnd, WM_APP + 2000, 5, 0, SMTO_BLOCK, 10, (PDWORD_PTR) &dwptr) || dwptr != 8)
      {
         return TRUE;
      }
      if(!::SendMessageTimeout(hwnd, WM_APP + 2000, 8, 0, SMTO_BLOCK, 10, (PDWORD_PTR) &dwptr) || dwptr != 11)
      {
         return TRUE;
      }
      if(!::SendMessageTimeout(hwnd, WM_APP + 2000, 11, 0, SMTO_BLOCK, 10, (PDWORD_PTR) &dwptr) || dwptr != 23)
      {
         return TRUE;
      }
      if(!::SendMessageTimeout(hwnd, WM_APP + 2000, 23, 0, SMTO_BLOCK, 10, (PDWORD_PTR) &dwptr) || dwptr != 33)
      {
         return TRUE;
      }
      if(::SendMessageTimeout(hwnd, WM_APP + 2000, 33, 0, SMTO_BLOCK, 10, (PDWORD_PTR) &dwptr))
      {
         if(dwptr == 1)
         {
            if(papp->m_straAppInterest.find_first("command") >= 0)
               papp->m_mapAppInterest["command"] = hwnd;
         }
         else if(dwptr == 67)
         {
            if(papp->m_straAppInterest.find_first("winactionarea") >= 0)
               papp->m_mapAppInterest["winactionarea"] = hwnd;
         }
         else if(dwptr == 68)
         {
            if(papp->m_straAppInterest.find_first("winutil") >= 0)
               papp->m_mapAppInterest["winutil"] = hwnd;
         }
         else if(dwptr == 69)
         {
            if(papp->m_straAppInterest.find_first("windesk") >= 0)
               papp->m_mapAppInterest["windesk"] = hwnd;
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

   HWND application::get_ca2_app_wnd(const char * psz)
   {
      return m_mapAppInterest[psz];
   }

   bool application::initialize_instance()
   {
      if(!::ca77::application::initialize_instance())
         return false;
      if(!pre_process_command_line())
         return false;
      System.register_bergedge_application(this);
      return true;
   }

   bool application::pre_process_command_line()
   {
      if(command_line().m_varQuery.has_property("install"))
      {
         if(::ca84::application::on_install())
         {
            if(on_install())
            {
               string strId = m_strId;
               if(strId.is_empty())
                  strId = m_strAppName;
               if(command_line().m_varQuery.has_property("app") && strId == command_line().m_varQuery["app"])
               {
                  System.install().remove_spa_start(strId);
                  System.install().add_app_install(strId);
               }
               else if(command_line().m_varQuery.has_property("bergedge_start") && strId == command_line().m_varQuery["bergedge_start"])
               {
                  System.install().remove_spa_start(strId);
                  System.install().add_app_install(strId);
               }
               else if(m_strInstallToken.has_char())
               {
                  System.install().remove_spa_start(m_strInstallToken);
                  System.install().add_app_install(m_strInstallToken);
               }
            }
            else
            {
               return false;
            }
         }
         return true;
      }
      else if(command_line().m_varQuery.has_property("uninstall"))
      {
         if(::ca84::application::on_uninstall())
         {
            if(on_uninstall())
            {
               System.install().remove_spa_start(m_strInstallToken);
            }
            else
            {
               return false;
            }
         }
         return true;
      }
      return true;
   }

   bool application::on_install()
   {
      return true;
   }

   bool application::on_uninstall()
   {
      return true;
   }

   void application::on_exclusive_instance_local_conflict()
   {
      m_straAppInterest.add(m_strAppName);
      update_app_interest();
      HWND hwnd = get_ca2_app_wnd(m_strAppName);
      if(hwnd != NULL)
      {
         ::ShowWindow(hwnd, SW_RESTORE);
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
         HWND hwnd = get_ca2_app_wnd(strApp);
         if(hwnd != NULL)
         {
            return send_simple_command((void *) hwnd, psz, osdataSender);
         }
      }
      return -1;
   }

   int application::send_simple_command(void * osdata, const char * psz, void * osdataSender)
   {
      HWND hwnd = (HWND) osdata;
      if(!::IsWindow(hwnd))
         return -1;
      COPYDATASTRUCT cds;
      memset(&cds, 0, sizeof(cds));
      cds.dwData = 198477;
      cds.cbData = strlen(psz);
      cds.lpData = (PVOID) psz;
      return SendMessage(hwnd, WM_COPYDATA, (WPARAM) (HWND) osdataSender, (LPARAM) &cds);
   }

   void application::request(var & varFile, var & varQuery)
   {
      if(varQuery.has_property("client_only"))
      {
         m_bClientOnly = true;
      }
      else
      {
         m_bClientOnly = false;
      }
      ::ca77::application::request(varFile, varQuery);
   }


} //namespace ca84