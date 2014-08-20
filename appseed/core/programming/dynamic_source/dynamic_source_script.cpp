#include "framework.h"

#if defined(LINUX) || defined(APPLEOS)
#if defined(APPLEOS)

#ifndef APPLEOS
#define _DARWIN_C_SOURCE
#endif

#endif
#include <dlfcn.h>
#include <sys/stat.h>
#endif


namespace dynamic_source
{



   script::script(sp(::axis::application) papp) :
      element(papp),
      m_memfileError(papp),
      m_mutex(papp)
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
     uint32_t dwReserved;    // must be zero
   } LOADPARMS32;

   ds_script::ds_script(sp(::axis::application) papp) :
      element(papp),
      script(papp),
      m_evCreationEnabled(papp),
      m_library(papp)
   {
      m_lpfnCreateInstance    = NULL;
      m_bShouldBuild          = true;
      m_bCalcHasTempError     = false;
      m_evCreationEnabled.SetEvent();
   }

   string ds_script::get_stage_path()
   {
      string strPath = m_strScriptPath;

      strPath.replace(":/", ".");
      strPath.replace(":\\", ".");
      strPath.replace("/", ".");
      strPath.replace("\\", ".");
#ifdef WINDOWS
      return System.dir().path("C:\\netnode\\stage\\x64\\", strPath);
#else
::str::begins_eat(strPath, ".");
      return System.dir().path("/core/stage/x86/", "lib" + strPath);
#endif

   }

   bool ds_script::DoesMatchVersion()
   {

      if(get_tick_count() - m_dwLastVersionCheck < (5000))
      {
         return m_bLastVersionCheck;
      }

      m_dwLastVersionCheck = get_tick_count();

      single_lock sl(&m_mutex, TRUE);

      bool bMatches = false;

#ifdef WINDOWSEX
      FILETIME ftCreation;
      FILETIME ftModified;
      memset(&ftCreation, 0, sizeof(FILETIME));
      //memset(&ftAccess, 0, sizeof(FILETIME));
      memset(&ftModified, 0, sizeof(FILETIME));
      HANDLE h = create_file(m_strSourcePath, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
      try
      {
         bMatches = GetFileTime(h, &ftCreation, NULL, &ftModified) != FALSE;
         if(bMatches)
         {
            bMatches = memcmp(&m_ftCreation, &ftCreation, sizeof(FILETIME)) == 0
                    && memcmp(&m_ftModified, &ftModified, sizeof(FILETIME)) == 0;
         }
      }
      catch(...)
      {
      }
      ::CloseHandle(h);

#elif defined(METROWIN)

      FILETIME ftCreation;
      FILETIME ftModified;
      memset(&ftCreation, 0, sizeof(FILETIME));
      //memset(&ftAccess, 0, sizeof(FILETIME));
      memset(&ftModified, 0, sizeof(FILETIME));
      ::Windows::Storage::StorageFile ^ h = get_os_file(m_strSourcePath, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
      try
      {
         bMatches = get_file_time(h, &ftCreation, NULL, &ftModified) != FALSE;
         if(bMatches)
         {
            bMatches = memcmp(&m_ftCreation, &ftCreation, sizeof(FILETIME)) == 0
                    && memcmp(&m_ftModified, &ftModified, sizeof(FILETIME)) == 0;
         }
      }
      catch(...)
      {
      }
//      ::CloseHandle(h);

#else

      struct ::stat st;

      memset(&st, 0, sizeof(st));

//         memset(&ftAccess, 0, sizeof(__time_t));
//         memset(&ftModified, 0, sizeof(__time_t));
//         HANDLE h = ::CreateFile(m_strSourcePath, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

      stat(m_strSourcePath, &st);
//         ::CloseHandle(h);
      bMatches = memcmp(&st.st_ctime, &m_ftCreation, sizeof(__time_t)) == 0 && memcmp(&m_ftModified, &st.st_mtime, sizeof(__time_t)) == 0;
#endif
      m_bLastVersionCheck = bMatches;
      return bMatches;
   }

   bool ds_script::ShouldBuild()
   {
      single_lock sl(&m_mutex, TRUE);
      return  m_bShouldBuild || (HasTempError() 
         // && HasTimedOutLastBuild()
         )
          || !DoesMatchVersion();

   }

   void ds_script::on_start_build()
   {
      
      single_lock sl(&m_mutex, TRUE);
      
      // Unload library in the context of manager thread
      
      //m_pmanager->m_pmessagewindow->SendMessage(WM_APP + 13, 13, (LPARAM) this);
      
      Unload(false);
      
      m_bCalcHasTempError  = false;
      
      m_bShouldBuild       = false;
      
      m_bHasTempOsError    = false;

      m_memfileError.m_spbuffer->set_length(0);

   }

   bool ds_script::HasTimedOutLastBuild()
   {
      single_lock sl(&m_mutex, TRUE);
      return (::get_tick_count() - m_dwLastBuildTime) >
         (m_pmanager->m_dwBuildTimeWindow + System.math().RandRange(0, m_pmanager->m_dwBuildTimeRandomWindow));
   }

   bool ds_script::HasCompileOrLinkError()
   {
      single_lock sl(&m_mutex, TRUE);
      string str;
      m_memfileError.seek_to_begin();
      str = m_memfileError.to_string();
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

      if (m_bHasTempOsError)
         return true;

      string str;
      m_memfileError.seek_to_begin();
      str = m_memfileError.to_string();
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
      #ifdef WINDOWS

      m_strScriptPath.replace("/", "\\");
      #else
      /*int iRetry = 5;
      while(!Application.file().exists(m_strScriptPath) && iRetry > 0)
      {

          Sleep(584);
          iRetry--;
      }*/
      #endif
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
           // debug_break();
         //}
         //::SetDllDirectory("C:\\netnode\\stage\\x64");
         string strStagePath = get_stage_path();
         //::file_copy_dup(strStagePath, m_strScriptPath, false);
         #ifdef WINDOWS
         string str1 = m_strScriptPath;
         string str2 = strStagePath;
         ::str::ends_eat_ci(str1, ".dll");
         ::str::ends_eat_ci(str2, ".dll");
         str1 += ".pdb";
         str2 += ".pdb";
         ::file_copy_dup(str2, str1, true);
         #else
             //Sleep(584);

        #endif
         ::file_copy_dup(strStagePath, m_strScriptPath, true);

         m_library.open(strStagePath);
         if(m_library.is_closed())
         {
             #ifdef LINUX
             const char * psz = dlerror();
             #endif
            uint32_t dwMessageId = GetLastError();
            if(dwMessageId == 0x139)
            {
               debug_break();
            }
            TRACE("Error Message Id: %d\n", dwMessageId);
            string strError = get_system_error_message(::GetLastError());
            string str;
            str.Format("%d - ", ::GetLastError());
            m_memfileError << strStagePath << " : LoadLibrary, GetLastError : " << str << strError;
         }
      }
      m_lpfnCreateInstance = m_library.get < NET_NODE_CREATE_INSTANCE_PROC > ("create_dynamic_source_script_instance");
      if(m_lpfnCreateInstance == NULL)
      {
          TRACE("create_dynamic_source_script_instance error");
      }
      //
      //else
      //{
        // m_evCreationEnabled.SetEvent();
      //}
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
         for(int32_t i = 0; i < m_scriptinstanceptra.get_size();)
         {
            if(get_tick_count() > (m_scriptinstanceptra[i].m_dwCreate + 30 * 1000))
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

         string strStagePath = get_stage_path();

#ifdef WINDOWSEX

         HMODULE hmodule = ::GetModuleHandleW(::str::international::utf8_to_unicode("\\\\?\\" + strStagePath));
         bool b = ::GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, ::str::international::utf8_to_unicode("\\\\?\\" + strStagePath), &hmodule) != FALSE;
         if(hmodule != NULL && !::FreeLibrary(hmodule))
         {
            uint32_t dwError = ::GetLastError();
            TRACE("ds_script::GetModuleHandle return bool(%d) Unload Error close Handle %s %d\r\n", b, strStagePath, dwError);
         }
         string strPdb;
         strPdb = strStagePath;
         ::str::ends_eat_ci(strPdb, ".dll");
         strPdb += ".pdb";
         b = ::GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, ::str::international::utf8_to_unicode("\\\\?\\" + strPdb), &hmodule) != FALSE;
         if(hmodule != NULL && !::FreeLibrary(hmodule))
         {
            uint32_t dwError = ::GetLastError();
            TRACE("ds_script::Unload Error close Handle %s %d\r\n", strPdb, dwError);
         }

#elif defined(METROWIN)

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



   ds_script::~ds_script()
   {
   }


   script_instance * ds_script::create_instance()
   {
      single_lock sl(&m_mutex);
      if(!sl.lock(minutes(2)))
         return NULL;
      if(ShouldBuild())
      {

         try
         {

            ::base::set_thread_priority(::axis::scheduling_priority_highest);

         }
         catch(...)
         {

         }

         string str;
         int32_t iRetry = 0;
         do
         {

            if (iRetry > 0)
            {

               Sleep(1000);

            }

            m_pmanager->m_pcompiler->compile(this);

            m_memfileError.seek_to_begin();

            str = m_memfileError.to_string();

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

         Load(false);
         // retried at least 8 times, give up any rebuild attemp until file is changed
         m_bShouldBuild = false;
         m_bCalcHasTempError = true;
         m_bHasTempError = false;

         // don't bother with sleeps if not compiling even if there are errors

         try
         {

            ::base::set_thread_priority(::axis::scheduling_priority_normal);

         }
         catch(...)
         {

         }

      }

      script_instance * pinstance;
      if(m_lpfnCreateInstance == NULL)
      {
         pinstance = canew(script_instance(this));
      }
      else
      {
         pinstance = m_lpfnCreateInstance(this);
      }
      pinstance->m_dwCreate = get_tick_count();

      return pinstance;
   }


   sp(::axis::application) ds_script::get_app() const
   {
      return m_pmanager->get_app();
   }


} // namespace dynamic_source


