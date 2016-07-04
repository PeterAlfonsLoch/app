#include "framework.h"
#include "dynamic_source.h"


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



script::script(::aura::application * papp) :
   ::object(papp),
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



typedef struct tagLOADPARMS32
{
   char * lpEnvAddress;  // address of environment strings
   char * lpCmdLine;     // address of command line
   char * lpCmdShow;     // how to show new program
   uint32_t dwReserved;    // must be zero
} LOADPARMS32;

ds_script::ds_script(::aura::application * papp) :
   ::object(papp),
    script(papp),
    m_evCreationEnabled(papp),
    m_library(papp)
{

   m_lpfnCreateInstance       = NULL;
   m_bShouldBuild             = true;
   m_bShouldCalcTempError     = true;
   m_bHasTempError            = false;
   m_bHasTempOsError          = false;
   m_bUnloading               = false;
   m_evCreationEnabled.SetEvent();



}


bool ds_script::DoesMatchVersion()
{

   if(get_tick_count() - m_dwLastVersionCheck < (5000))
   {
      return m_bLastVersionCheck;
   }

   m_dwLastVersionCheck = get_tick_count();

   synch_lock sl(&m_mutex);

   bool bMatches = false;

   auto ft = get_file_time(m_strSourcePath);

   bMatches = m_ft == ft;

   m_bLastVersionCheck = bMatches;
   return bMatches;
}

bool ds_script::ShouldBuild()
{
   
   synch_lock sl(&m_mutex);

   bool bManagerShouldBuild = m_pmanager->should_build(m_strSourcePath);

   if (bManagerShouldBuild)
   {

      return true;

   }

   return m_bShouldBuild || HasDelayedTempError() || !DoesMatchVersion();

}

void ds_script::on_start_build()
{

   synch_lock sl(&m_mutex);

   m_bShouldCalcTempError     = true;

   m_bShouldBuild             = false;

   m_bHasTempOsError          = false;

   m_memfileError.m_spbuffer->set_length(0);

   m_strError.Empty();

   Unload();

}

bool ds_script::HasTimedOutLastBuild()
{
   synch_lock sl(&m_mutex);
   return (::get_tick_count() - m_dwLastBuildTime) >
          (m_pmanager->m_dwBuildTimeWindow + System.math().RandRange(0, m_pmanager->m_dwBuildTimeRandomWindow));
}

bool ds_script::HasCompileOrLinkError()
{
   synch_lock sl(&m_mutex);

   string str;

   str = m_strError;

   if(str.find(" error(") >= 0)
      return true;
   if(str.find(" error ") >= 0)
      return true;
   if(str.find(" GetLastError ") >= 0)
      return true;
   return false;
}

bool ds_script::HasDelayedTempError()
{

   return HasTempError() && HasTimedOutLastBuild();

}


bool ds_script::HasTempError()
{
   synch_lock sl(&m_mutex);
   // if m_strError is empty, sure there is a error... at least the
   // successfull compilation/linking message ("error message" => m_strError) should exist
   // If it is empty, it is considered a temporary error (due locks or race conditions...)
   if(m_strError.is_empty() || m_bShouldCalcTempError)
   {
      m_bShouldCalcTempError = false;
      m_bHasTempError = CalcHasTempError();
   }
   return m_bHasTempError;
}

bool ds_script::CalcHasTempError()
{

   synch_lock sl(&m_mutex);

   if (m_bHasTempOsError)
      return true;

   string str;

   str = m_strError;

   str.trim();

   if(str.is_empty())
      return true;

   {
      strsize iFind1 = str.find(" C1033:");
      if(iFind1 >= 0)
         return true;
   }
   {
      strsize iFind1 = str.find(" C1083:"); // Permission Denied
      if(iFind1 >= 0)
         return true;
   }
   {
      strsize iFind1 = str.find(" C1041:"); // fatal error C1041: cannot open program database
      if(iFind1 >= 0)
         return true;
   }
   {
      strsize iFind1 = str.find(".dll: does not exist.");
      if(iFind1 >= 0)
      {
         // if dll does not exist
         {
            strsize iFind1 = str.find(" error(");
            strsize iFind2 = str.find(" error ");
            strsize iFind3 = str.find("Linking...");
            // and have compile error (others than the ones above, that are considered temporary as they may be due temporary file locks, for example...).
            if((iFind3 >= 0 && ((iFind1 < iFind3 && iFind1 >= 0) ||
                                (iFind2 < iFind3 && iFind2 >= 0))))
            {
               return false;
            }
         }

      }
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


void ds_script::Load()
{
   synch_lock sl(&m_mutex);
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
      if(HasTempError())
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
      string strStagePath = m_pmanager->get_full_stage_path(m_strScriptPath);


//#ifdef WINDOWS
//         string str1 = m_strScriptPath;
//         string str2 = strStagePath;
//         ::str::ends_eat_ci(str1,".dll");
//         ::str::ends_eat_ci(str2,".dll");
//         str1 += ".pdb";
//         str2 += ".pdb";
//         ::file_copy_dup(str2,str1,true);
//#else
//         //Sleep(584);
//
//#endif
//

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
void ds_script::Unload()
{

   if(m_bUnloading)
      return;

   keep < bool > unloading(&m_bUnloading,true,false,true);

   m_evCreationEnabled.ResetEvent();

   synch_lock sl(&m_mutex);

   if(m_library.is_opened())
   {

      m_library.close();

      string strStagePath = m_pmanager->get_stage_path(m_strScriptPath);
      /*
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
      #endif*/

      m_lpfnCreateInstance = (NET_NODE_CREATE_INSTANCE_PROC) NULL;

   }

}



ds_script::~ds_script()
{
}


script_instance * ds_script::create_instance()
{

   synch_lock sl(&m_mutex);

   if (m_strSourcePath.find_ci("\\applications\\basic\\") > 0)
   {

      TRACE("/applications/basic/");

   }

   check_should_build:

   if(ShouldBuild())
   {
      synch_lock slCompiler(&Application.m_semCompiler);
      Sleep(84);

      try
      {

         ::multithreading::set_priority(::multithreading::priority_highest);

      }
      catch(...)
      {

      }

      string str;

      int32_t iRetry = 0;

      bool bHasTempError = false;

      do
      {

         if (iRetry > 0)
         {

            Sleep(System.math().RandRange(1977, 1977+ 1984));

         }

         m_pmanager->m_pcompiler->compile(this);

         str = m_strError;



         if(iRetry == 0)
         {
            TRACE("Build: %s\n%s\n", m_strName.c_str(), str.c_str());
         }
         else
         {
            TRACE("Retry(%d): %s\nError: %s\n", iRetry, m_strName.c_str(), str.c_str());
         }

         iRetry++;

      }
      while((bHasTempError = HasTempError()) && iRetry < 8);

      m_dwLastBuildTime = ::get_tick_count();

      // Wait for finalization of build
      // or delay in case of error to avoid run conditions due extreme overload.
      //Sleep(pscript->m_pmanager->m_dwBuildTimeWindow +
      // System.math().RandRange(0, pscript->m_pmanager->m_dwBuildTimeRandomWindow));
//         m_bShouldBuild =false;

      m_ft = get_file_time(m_strSourcePath);


      Load();

      Sleep(84);
      // retried at least 8 times, give up any rebuild attemp until file is changed
      m_bShouldBuild = false;

      {
      
         synch_lock sl(&m_pmanager->m_mutexShouldBuild);

         m_pmanager->m_mapShouldBuild[m_strSourcePath] = false;

      }

      // don't bother with sleeps if not compiling even if there are errors

      /*         try
               {

                  ::multithreading::set_priority(::multithreading::priority_normal);

               }
               catch(...)
               {

               }*/

   }
   //else
   //{

   //   if(!m_pmanager->should_build(m_strScriptPath))
   //   {

   //      m_strScriptPath = m_pmanager->get_script_path(m_strName);

   //      Load();

   //   }

   //}

   script_instance * pinstance = NULL;

   if(m_lpfnCreateInstance == NULL)
   {

      return NULL;

   }
   else
   {

      try
      {

         pinstance = m_lpfnCreateInstance(this);

      }
      catch (...)
      {

         //m_bShouldBuild = true;

         //goto check_should_build;

      }

   }

   pinstance->m_pmanager = m_pmanager;

   pinstance->m_dwCreate = get_tick_count();

   return pinstance;
}


sp(::aura::application) ds_script::get_app() const
{
   return m_pmanager->get_app();
}


} // namespace dynamic_source





