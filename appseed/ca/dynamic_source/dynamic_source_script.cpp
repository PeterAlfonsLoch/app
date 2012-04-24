#include "StdAfx.h"

#if defined(LINUX)
#include <dlfcn.h>
#endif


namespace dynamic_source
{



   script::script(::ca::application * papp) :
      ca(papp)
   {
   }
   
   script::~script()
   {
   }

   void script::run(script_instance * pinstance)
   {
      pinstance->run();
   }



   typedef struct tagLOADPARMS32 {
     char * lpEnvAddress;  // address of environment strings
     char * lpCmdLine;     // address of command line
     char * lpCmdShow;     // how to show new program
     DWORD dwReserved;    // must be zero
   } LOADPARMS32;

   ds_script::ds_script(::ca::application * papp) :
      ca(papp),
      script(papp),
      m_memfileError(papp)
   {
      m_lpfnCreateInstance    = NULL;
      m_bShouldBuild          = true;
      m_bCalcHasTempError     = false;
      m_evCreationEnabled.SetEvent();
   }

   bool ds_script::DoesMatchVersion()
   {
      single_lock sl(&m_mutex, TRUE);
      struct stat64 st;
      memset(&st, 0, sizeof(st));
//         memset(&ftAccess, 0, sizeof(__time_t));
//         memset(&ftModified, 0, sizeof(__time_t));
//         HANDLE h = ::CreateFile(m_strSourcePath, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
      stat64(m_strSourcePath, &st);
//         ::CloseHandle(h);
      bool bMatches = memcmp(&st.st_ctime, &m_ftCreation, sizeof(__time_t)) == 0
          && memcmp(&m_ftModified, &st.st_mtime, sizeof(__time_t)) == 0;
      return bMatches;
   }

   bool ds_script::ShouldBuild()
   {
      single_lock sl(&m_mutex, TRUE);
      return  m_bShouldBuild || (HasTempError() &&
         HasTimedOutLastBuild())
          || !DoesMatchVersion();

   }

   void ds_script::on_start_build()
   {
      single_lock sl(&m_mutex, TRUE);
      // Unload library in the context of manager thread
      //m_pmanager->m_pmessagewindow->SendMessage(WM_APP + 13, 13, (LPARAM) this);
      Unload(false);
      m_bCalcHasTempError = false;
      m_bShouldBuild = false;
      m_memfileError.Truncate(0);
   }

   bool ds_script::HasTimedOutLastBuild()
   {
      single_lock sl(&m_mutex, TRUE);
      return (::GetTickCount() - m_dwLastBuildTime) >
         (m_pmanager->m_dwBuildTimeWindow + System.math().RandRange(0, m_pmanager->m_dwBuildTimeRandomWindow));
   }

   bool ds_script::HasCompileOrLinkError()
   {
      single_lock sl(&m_mutex, TRUE);
      string str;
      m_memfileError.seek_to_begin();
      m_memfileError.to_string(str);
      if(str.find(" error(") >= 0)
         return true;
      if(str.find(" error ") >= 0)
         return true;
      if(str.find(" GetLastError ") >= 0)
         return true;
      return false;
   }

   bool ds_script::HasTempError(bool bLock)
   {
      single_lock sl(&m_mutex, bLock ? TRUE : FALSE);
      if(!m_bCalcHasTempError)
      {
         m_bHasTempError = CalcHasTempError(false);
         m_bCalcHasTempError = true;
      }
      return m_bHasTempError;
   }

   bool ds_script::CalcHasTempError(bool bLock)
   {
      single_lock sl(&m_mutex, bLock ? TRUE : FALSE);
      string str;
      m_memfileError.seek_to_begin();
      m_memfileError.to_string(str);
      {
         strsize iFind1 = str.find(".dll: does not exist.");
         if(iFind1 >= 0)
         {
            // if dll does not exist
            {
               strsize iFind1 = str.find(" error(");
               strsize iFind2 = str.find(" error ");
               strsize iFind3 = str.find("Linking...");
               // and have compile error
               if((iFind3 >= 0 && ((iFind1 < iFind3 && iFind1 >= 0) ||
                  (iFind2 < iFind3 && iFind2 >= 0))))
               {
                  return false;
               }
            }

         }
      }
      {
         strsize iFind1 = str.find("fatal error C1033:");
         if(iFind1 >= 0)
            return true;
      }
      {
         strsize iFind1 = str.find("fatal error C1083:");
         if(iFind1 >= 0)
            return true;
      }
      {
         strsize iFind1 = str.find("warning LNK4099:");
         if(iFind1 >= 0)
            return true;
      }
      {
         strsize iFind1 = str.find("fatal error LNK1168:");
         if(iFind1 >= 0)
            return true;
      }
      {
         strsize iFind1 = str.find(" error(");
         strsize iFind2 = str.find(" error ");
         strsize iFind3 = str.find("Linking...");
         if(iFind3 >= 0 && (iFind1 > iFind3 || iFind2 > iFind3))
         {
            return true;
         }
      }
      if(str.find(" GetLastError ") >= 0)
         return true;
      return false;
   }


   void ds_script::Load(bool bLock)
   {
      single_lock sl(&m_mutex, bLock ? TRUE : FALSE);
      m_strScriptPath.replace("/", "\\");
      //::OutputDebugString(m_strScriptPath);
      if(!Application.file().exists(m_strScriptPath))
      {
         if(HasTempError(false))
         {
            m_memfileError << m_strScriptPath << ": does not exist because of \"temp\" error.";
         }
         else
         {
            m_memfileError << m_strScriptPath << ": does not exist.";
         }
         m_lpfnCreateInstance = NULL;
         return;
      }
      if(m_library.is_closed())
      {
         //if(m_strScriptPath.find("transactions") >= 0)
         //{
           // AfxDebugBreak();
         //}
         m_library.open(m_strScriptPath);
         if(m_library.is_closed())
         {
            DWORD dwMessageId = GetLastError();
            if(dwMessageId == 0x139)
            {
               AfxDebugBreak();
            }
            LPTSTR lpBuffer;
            TRACE("Error Message Id: %d\n", dwMessageId);
            FormatMessage(
               FORMAT_MESSAGE_ALLOCATE_BUFFER |
               FORMAT_MESSAGE_FROM_SYSTEM,
               NULL,
               dwMessageId,
               0,
               (LPTSTR) &lpBuffer,
               1,
               NULL);
            string str;
            str.Format("%d : ", ::GetLastError());
            m_memfileError << m_strScriptPath << " : LoadLibrary, GetLastError "  << str;

            if(lpBuffer != NULL)
            {
               m_memfileError << lpBuffer;
#ifdef WINDOWS
               LocalFree(lpBuffer);
#endif
            }
         }
      }
      m_lpfnCreateInstance = m_library.get < NET_NODE_CREATE_INSTANCE_PROC > ("create_dynamic_source_ds_script_instance");
      if(m_lpfnCreateInstance != NULL)
      {
         m_evCreationEnabled.SetEvent();
      }
   }
   void ds_script::Unload(bool bLock)
   {
      m_evCreationEnabled.ResetEvent();
      single_lock sl(&m_mutex);
      if(bLock)
      {
         sl.lock(minutes(0.5));
      }
      while(m_scriptinstanceptra.get_size())
      {
         if(bLock)
         {
            sl.unlock();
            sl.lock(minutes(0.5));
         }
         for(int i = 0; i < m_scriptinstanceptra.get_size();)
         {
            if(GetTickCount() > (m_scriptinstanceptra[i]->m_dwCreate + 30 * 1000))
            {
               m_scriptinstanceptra.remove_at(i);
            }
            else
            {
               i++;
            }
         }
      }
      if(bLock)
      {
         sl.unlock();
         sl.lock();
      }
      if(m_library.is_opened())
      {
         m_library.close();

#ifdef WINDOWS
         HMODULE hmodule = ::GetModuleHandleW(gen::international::utf8_to_unicode("\\\\?\\" + m_strScriptPath));
         BOOL b = ::GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, gen::international::utf8_to_unicode("\\\\?\\" + m_strScriptPath), &hmodule);
         if(hmodule != NULL && !::FreeLibrary(hmodule))
         {
            DWORD dwError = ::GetLastError();
            TRACE("ds_script::GetModuleHandle return BOOL(%d) Unload Error close Handle %s %d\r\n", b, m_strScriptPath, dwError);
         }
         string strPdb;
         strPdb = m_strScriptPath;
         gen::str::ends_eat_ci(strPdb, ".dll");
         strPdb += ".pdb";
         hmodule = ::GetModuleHandleW(gen::international::utf8_to_unicode(strPdb));
         if(hmodule != NULL && !::FreeLibrary(hmodule))
         {
            DWORD dwError = ::GetLastError();
            TRACE("ds_script::Unload Error close Handle %s %d\r\n", strPdb, dwError);
         }
#else
         void * p = dlopen(m_strScriptPath, RTLD_NOLOAD);
         if(p != NULL && !dlclose(p))
         {
            TRACE("ds_script::%s Unload Error\r\n", m_strScriptPath.c_str());
         }
#endif

         m_lpfnCreateInstance = (NET_NODE_CREATE_INSTANCE_PROC) NULL;
      }
   }



   ds_script::~ds_script(void)
   {
   }


   script_instance * ds_script::create_instance()
   {
      single_lock slCreationEnabled(&m_evCreationEnabled);
      if(!slCreationEnabled.lock(minutes(0.7)))
      {
         m_bShouldBuild = true;
      }
      single_lock sl(&m_mutex);
      if(!sl.lock(minutes(1)))
         return NULL;
      if(ShouldBuild())
      {
         string str;
         int iRetry = 0;
         do
         {
            // unload should be much more safe Unload(false);
            m_pmanager->m_pcompiler->compile(this);
            Load(false);
            m_memfileError.seek_to_begin();
            m_memfileError.to_string(str);
            if(iRetry == 0)
            {
               TRACE("Build: %s\n%s\n", m_strName.c_str(), str.c_str());
            }
            else
            {
               TRACE("Retry(%d): %s\nError: %s\n", iRetry, m_strName.c_str(), str.c_str());
            }
            iRetry++;
         } while(HasTempError() && iRetry < 8);
         // retried at least 8 times, give up any rebuild attemp until file is changed
         m_bShouldBuild = false;
         m_bCalcHasTempError = true;
         m_bHasTempError = false;
         // don't bother with sleeps if not compiling even if there are errors
         m_evCreationEnabled.SetEvent();
      }

      script_instance * pinstance;
      if(m_lpfnCreateInstance == NULL)
      {
         pinstance = new script_instance(this);
      }
      else
      {
         pinstance = m_lpfnCreateInstance(this);
      }
      pinstance->m_dwCreate = GetTickCount();
      m_scriptinstanceptra.add(pinstance);
      return pinstance;
   }


   ::ca::application * ds_script::get_app() const
   {
      return m_pmanager->get_app();
   }


} // namespace dynamic_source


