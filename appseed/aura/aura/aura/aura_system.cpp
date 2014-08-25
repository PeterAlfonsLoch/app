#include "framework.h"


#ifdef LINUX

#include <fcntl.h>
#include <unistd.h>


#define __USE_GNU
#include <link.h>


#include <ctype.h>
#include <sys/stat.h>
#endif

void dappy(const char * psz);


namespace aura
{


   class ::id system::idEmpty;
   class ::id_space * system::s_pidspace = NULL;


   system::system(sp(::aura::application) papp)
   {
      
#ifdef MATTER_CACHE_FROM_HTTP_SERVER

      m_bMatterFromHttpCache = true;

#else

      m_bMatterFromHttpCache = false;

#endif


      set_app(this);
      m_nSafetyPoolSize          = 512;        // default size

      m_pmath                    = canew(math::math(this));
      m_pgeometry                = canew(geometry::geometry(this));
      m_phtml = NULL;


      m_paurasystem = this;

      if(papp == NULL)
      {

         oprop("parent_system") = (sp(element)) NULL;

      }
      else
      {

         oprop("parent_system") = papp->m_paurasystem;

      }

      m_peengine = NULL;


      m_pmachineeventcentral = NULL;

      //::ca::application::m_file.set_app(this);
      //::ca::application::m_dir.set_app(this);

      string strId;
      //strId = m_strAppName;
      //strId += ::str::has_char(m_strAppId, ".");
      //strId += ::str::has_char(m_strBaseSupportId, ".");


      strId = "ca2log";


      xxdebug_box("Going to start Log","Just before initialize log",0);

      // log starts here
      if(!initialize_log(strId))
      {
         xxdebug_box("Could not initialize log","Failed to initialize log",0);
         throw "failed to initialize log";
      }


      /*
      if(psystemParent == NULL)
      {

      m_peengine                                = new ::exception::engine(this);

      }
      else
      {

      m_peengine                                = psystemParent->m_peengine;

      }
      */


      //use_base_ca2_allocator();


      m_pfactory = new class base_factory(this);
      m_pfactory->set_app(this);

      m_pfactory->creatable_large < ::file::simple_binary_buffer >(type_info < ::file::binary_buffer >());
      m_pfactory->creatable_large < ::file::string_buffer >();

      factory().cloneable_large < stringa >();
      factory().cloneable_large < ::primitive::memory >();
      factory().cloneable_large < int_array >();

      __node_aura_factory_exchange(this);

      thread::s_bAllocReady = true;

      m_pxml = canew(::xml::departament(this));

      m_pxml->construct(this);

      if(!m_pxml->initialize1())
         throw simple_exception(this,"failed to construct system m_pxml->initialize1()");

      if(!m_pxml->initialize())
         throw simple_exception(this,"failed to construct system m_pxml->initialize()");

      m_spmutexUserAppData = canew(mutex(get_app(),false,"Local\\ca2.UserAppData"));
      
      m_spmutexSystemAppData = canew(mutex(get_app(),false,"Local\\ca2.SystemAppData"));

      m_spmutexFactory = canew(mutex(get_app()));

      m_bGudoNetCache = true;

      m_pthreadimpl.alloc(allocer());

      m_pthreadimpl->m_pthread = this;

   }


   void system::construct(const char * pszAppId)
   {

      ::aura::application::construct(pszAppId);

   }


   system::~system()
   {

   }


   base_factory & system::factory()
   {

      return *m_pfactory;

   }


   ::exception::engine & system::eengine()
   {

      return *m_peengine;

   }


   bool system::process_initialize()
   {




      m_peengine = new ::exception::engine(this);

      m_pfactory->cloneable_large < create_context >();
      m_pfactory->cloneable_large < application_bias >();
      m_pfactory->cloneable_large < command_line >();
      m_pfactory->cloneable_large < manual_reset_event >();
      m_pfactory->cloneable_large < mutex >();
      m_pfactory->cloneable_large < event >();

      if(!::aura::application::process_initialize())
         return false;

      m_spos.alloc(allocer());


      if(!set_main_init_data(m_pinitmaindata))
         return false;


      if(m_pmachineeventcentral == NULL)
      {

         m_pmachineeventcentral = new ::machine_event_central(this);
         if(!m_pmachineeventcentral->initialize())
            return false;
         if(m_pmachineeventcentral->is_close_application())
            return false;

      }


      return true;

   }


   bool system::initialize2()
   {

      if(!::aura::application::initialize2())
         return false;

      return true;

   }


   bool system::initialize_instance()
   {

      m_pfactory->enable_simple_factory_request();

      if(!::aura::application::initialize_instance())
         return false;

      return true;

   }


   bool system::finalize()
   {

      __wait_threading_count_except(this,::millis((5000) * 77));

      bool bOk = false;


      try
      {

         bOk = ::aura::application::finalize();

      }
      catch(...)
      {

         bOk = false;

      }

      return bOk;

   }


   int32_t system::exit_instance()
   {

      __wait_threading_count(::millis((5000) * 8));

      try
      {


         /*      try
         {
         if(m_plemonarray != NULL)
         {
         delete m_plemonarray;
         }
         }
         catch(...)
         {
         }
         m_plemonarray = NULL;
         */


         m_pmath.release();

         m_pgeometry.release();

      }
      catch(...)
      {

         m_iReturnCode = -86;

      }


      for(int i = 0; i < m_serviceptra.get_size(); i++)
      {

         try
         {

            m_serviceptra(i)->Stop(0);

         }
         catch(...)
         {

         }

      }


      for(int i = 0; i < m_serviceptra.get_size(); i++)
      {
         try
         {
            m_serviceptra(i)->Stop((5000) * 2);
         }
         catch(...)
         {
         }
      }

      m_serviceptra.remove_all();

      try
      {
         if(m_pfactory != NULL)
         {

            m_pfactory->enable_simple_factory_request(false);

            m_pfactory.release();

         }

      }
      catch(...)
      {
         TRACE("system::exit_instance: Potentially catastrophical error : error disabling simple factory request");
      }


      int32_t iRet = 0;


      try
      {

         iRet = ::aura::application::exit_instance();

      }
      catch(...)
      {

      }


      try
      {

         m_spos.release();

      }
      catch(...)
      {

      }


      try
      {

         if(m_pmachineeventcentral != NULL)
         {

            m_pmachineeventcentral->set_run(false);

         }

      }
      catch(...)
      {

      }



      m_plog.release();



      {

         synch_lock sl(m_spmutexFactory);

         m_typemap.remove_all();

         m_typemap.release();

      }



      ::aura::application::exit_instance();

#ifdef METROWIN
      m_pdevicecontext = nullptr;

      m_pmutexDc.release();
#endif



      if(m_peengine != NULL)
      {

         delete m_peengine;

         m_peengine = NULL;

      }


      return iRet;

   }


   UINT system::os_post_to_all_threads(UINT uiMessage,WPARAM wparam,lparam lparam)
   {

      post_to_all_threads(uiMessage,wparam,lparam);

      return 0;

   }

   sp(element) system::clone()
   {
      // by the time, it is not possible to clone a system
      return NULL;
   }



   void system::discard_to_factory(sp(element) pca)
   {

      if(m_pfactory == NULL)
         return;

      m_pfactory->discard(pca);

   }



   void system::wait_twf()
   {

   }

   bool system::is_system()
   {

      return true;

   }






   int32_t system::_001OnDebugReport(int32_t i1,const char * psz1,int32_t i2,const char * psz2,const char * psz3,va_list args)
   {

      return _debug_logging_report(i1,psz1,i2,psz2,psz3,args);

   }



   int32_t system::_debug_logging_report(int32_t iReportType, const char * pszFileName, int32_t iLineNumber, const char * pszModuleName, const char * pszFormat,va_list list)
   {

      if(m_plog == NULL || !m_plog->m_bExtendedLog)
      {

         return ::aura::SimpleDebugReport(iReportType,pszFileName,iLineNumber,pszModuleName,pszFormat,list);

      }

      string str;

      if(pszFileName != NULL || pszModuleName != NULL)
      {

         stringa stra;

         if(pszFileName != NULL)
            stra.add(pszFileName);

         if(pszModuleName != NULL)
            stra.add(pszFileName);

         str += stra.implode(", ");

         str += ": ";

      }

      string str2;

      if(pszFormat != NULL)
      {

//         if(list != NULL)
         {

            str2.FormatV(pszFormat,list);

         }
    //     else
         {

  //          str2 = pszFormat;

         }

      }

      str = str + str2;

      string strPrint(str);

      strPrint.replace("%","%%");

      if(m_plog != NULL)
      {

         m_plog->print(strPrint);

      }

      if(iReportType == _CRT_ASSERT)
      {

         return 1;

      }
      else
      {

         return 0;

      }

   }




   bool system::assert_failed_line(const char * lpszFileName,int32_t iLine)
   {
      UNREFERENCED_PARAMETER(lpszFileName);
      UNREFERENCED_PARAMETER(iLine);
      return false;
   }


   bool system::on_assert_failed_line(const char * lpszFileName,int32_t iLine)
   {
      UNREFERENCED_PARAMETER(lpszFileName);
      UNREFERENCED_PARAMETER(iLine);
      return true;
   }




   sp(element) system::on_alloc(sp(::aura::application) papp,sp(type) info)
   {
      /*string str;
      str.Format("Could not alloc %s", info.name());
      simple_message_box(str);*/
      sp(element) pobj = m_pfactory->create(papp,info);
      if(pobj != NULL)
         return pobj;
      on_allocation_error(papp,info);
      return NULL;
   }

   sp(element) system::alloc(sp(::aura::application) papp,sp(type) info)
   {
      return on_alloc(papp,info);
   }

   sp(element) system::alloc(sp(::aura::application) papp,const std_type_info & info)
   {
      return on_alloc(papp,canew(type(info)));
   }

   void system::on_allocation_error(sp(::aura::application) papp,sp(type) info)
   {
      UNREFERENCED_PARAMETER(papp);
      UNREFERENCED_PARAMETER(info);
   }

   sp(element) system::alloc(sp(::aura::application) papp,const class id & idType)
   {
      return on_alloc(papp,get_type_info(idType));
   }


   sp(type) system::get_type_info(const ::std_type_info & info)
   {

      synch_lock sl(m_spmutexFactory);

#ifdef WINDOWS
      sp(type) & typeinfo = m_typemap[info.raw_name()];
#else
      sp(type) & typeinfo = m_typemap[info.name()];
#endif

      if(typeinfo.is_null())
         typeinfo = canew(type(info));

      return typeinfo;

   }


   ::xml::departament & system::xml()
   {
      return *m_pxml;
   }



   class ::str::base64 & system::base64()
   {

      return m_base64;

   }



   ::aura::log & system::log()
   {
      return *m_plog;
   }




   machine_event_central & system::machine_event_central()
   {
      return *m_pmachineeventcentral;
   }


   sp(::aura::session) system::query_session(index iEdge)
   {

      return NULL;

   }


   ::aura::os & system::os()
   {

      return *m_spos;

   }


   spa(::aura::session) & system::basesessionptra()
   {

      return m_basesessionptra;

   }

   bool system::initialize_log(const char * pszId)
   {
      if(m_plog != NULL)
         return true;
      m_plog = new ::aura::log(this);
      m_plog->set_extended_log();
      m_plog->set_app(this);
      if(!m_plog->initialize(pszId))
      {
         m_plog.release();
         return false;
      }
      //      ::core::trace_v = &::core::system_log_trace_v;
      return true;
   }






   void system::appa_load_string_table()
   {

      retry_single_lock rsl(m_pmutex,millis(84),millis(84));

//      for(int32_t i = 0; i < appptra().get_size(); i++)
  //    {
    //     sp(::aura::application) papp = appptra()(i);
      //   papp->load_string_table();
      //}

   }

   void system::appa_set_locale(const char * pszLocale,::action::context actioncontext)
   {

      retry_single_lock rsl(m_pmutex,millis(84),millis(84));

//      for(int32_t i = 0; i < appptra().get_size(); i++)
 //     {
  //       sp(::aura::application) papp = appptra()(i);
  //       papp->set_locale(pszLocale,actioncontext);
  //    }

   }

   void system::appa_set_schema(const char * pszStyle,::action::context actioncontext)
   {

      retry_single_lock rsl(m_pmutex,millis(84),millis(84));

//      for(int32_t i = 0; i < appptra().get_size(); i++)
  //    {
  //       sp(::aura::application) papp = appptra()(i);
  //       papp->set_schema(pszStyle,actioncontext);
  //    }

   }



   bool system::assert_running_global(const char * pszAppName,const char * pszId)
   {
      if(string(pszId).has_char())
      {
         //         HANDLE h = ::OpenMutex(SYNCHRONIZE, FALSE, get_global_id_mutex_name(pszAppName, pszId));
         ::mutex * pmutex = mutex::open_mutex(this,get_global_id_mutex_name(pszAppName,pszId));
         if(pmutex == NULL)
         {

            string strApp = pszAppName;
            strApp += "app.exe";

            string strParameters;
            strParameters = ": global_mutex_id=\"" + string(pszId) + "\"";

#if defined(WINDOWSEX) || defined(LINUX) || defined(APPLEOS)

            simple_shell_launcher launcher(NULL,NULL,dir().path(get_module_folder(),strApp),strParameters,NULL,SW_SHOW);

            launcher.execute();

#else

            throw todo(get_app());

#endif

            return false;
         }
         else
         {
            delete pmutex;
         }
         return true;
      }
      else
      {
         //HANDLE h = ::OpenMutex(SYNCHRONIZE, FALSE, get_global_mutex_name(pszAppName));
         ::mutex * pmutex = mutex::open_mutex(this,get_global_mutex_name(pszAppName));
         if(pmutex == NULL)
         {
            string strApp = pszAppName;
            strApp += "app.exe";

#if defined(METROWIN)

            throw todo(get_app());

#else

            simple_shell_launcher launcher(NULL,NULL,dir().path(get_module_folder(),strApp),NULL,NULL,SW_SHOW);

            launcher.execute();

#endif

            return false;
         }
         else
         {
            //::CloseHandle(h);
            delete pmutex;
         }
         return true;
      }
   }

   bool system::assert_running_local(const char * pszAppName,const char * pszId)
   {
      string strAppName(pszAppName);
      string strId(pszId);
      if(strId.has_char())
      {
         //HANDLE h = ::OpenMutex(SYNCHRONIZE, FALSE, get_local_id_mutex_name(pszAppName, strId));
         ::mutex * pmutex = mutex::open_mutex(this,get_local_id_mutex_name(pszAppName,strId));
         if(pmutex == NULL)
         {
            string strApp;
            strApp = "app.exe";
            string strParameters;
            strParameters = ": app=" + strAppName + " local_mutex_id=\"" + strId + "\"";

#ifdef METROWIN

            throw todo(get_app());

#else

            simple_shell_launcher launcher(NULL,NULL,dir().path(get_ca2_module_folder(),strApp),strParameters,NULL,SW_SHOW);

            launcher.execute();

#endif

            return false;
         }
         else
         {
            //::CloseHandle(h);
            delete pmutex;
         }
         return true;
      }
      else
      {
         //         HANDLE h = ::OpenMutex(SYNCHRONIZE, FALSE, get_local_mutex_name(pszAppName));
         ::mutex * pmutex = mutex::open_mutex(this,get_local_mutex_name(pszAppName));
         if(pmutex == NULL)
         {
            string strApp;
            strApp = "app.exe";
            string strParameters;
            strParameters = ": app=" + strAppName;

#ifdef METROWIN

            throw todo(get_app());

#else

            simple_shell_launcher launcher(NULL,NULL,dir().path(get_ca2_module_folder(),strApp),strParameters,NULL,SW_SHOW);

            launcher.execute();

#endif

            return false;
         }
         else
         {
            //::CloseHandle(h);
            delete pmutex;
         }
         return true;
      }
   }










   ::count system::get_application_count()
   {

      ::count c = 0;

      try
      {

         for(index iBaseSession = 0; iBaseSession < m_basesessionptra.get_count(); iBaseSession++)
         {

            try
            {

               c += m_basesessionptra[iBaseSession].appptra().get_count();

            }
            catch(...)
            {

            }

         }

      }
      catch(...)
      {

      }

      return c;

   }


   application_ptra system::get_appptra()
   {

      application_ptra appptra;

      try
      {

         for(index iBaseSession = 0; iBaseSession < m_basesessionptra.get_count(); iBaseSession++)
         {

            try
            {

               appptra += m_basesessionptra[iBaseSession].appptra();

            }
            catch(...)
            {

            }

         }

      }
      catch(...)
      {


      }

      return appptra;

   }


   string system::get_ca2_module_folder()
   {

      single_lock sl(m_pmutex,true);

      return m_strCa2ModuleFolder;

   }


   string system::get_ca2_module_file_path()
   {

      string strModuleFileName;

#ifdef WINDOWSEX

      wchar_t lpszModuleFilePath[MAX_PATH + 1];

      if(GetModuleFileNameW(::GetModuleHandleA("core.dll"),lpszModuleFilePath,MAX_PATH + 1))
      {

         strModuleFileName = lpszModuleFilePath;

      }

#elif defined(METROWIN)

      throw todo(this);

#else

#ifdef LINUX

      {

         void * handle = dlopen("core.so",0);

         if(handle == NULL)
            return "";

         link_map * plm;

         dlinfo(handle,RTLD_DI_LINKMAP,&plm);

         strModuleFileName = plm->l_name;

         dlclose(handle);

         //         m_strCa2ModuleFolder = dir::name(strModuleFileName);

      }

#else

      {

         char * pszCurDir = getcwd(NULL,0);

         string strCurDir = pszCurDir;

         free(pszCurDir);

         if(Application.file_exists(::dir_path(strCurDir,"core.dylib")))
         {
            m_strCa2ModuleFolder = strCurDir;
            goto finishedCa2Module;
         }


         if(Application.file_exists(::dir_path(m_strModuleFolder,"core.dylib")))
         {
            m_strCa2ModuleFolder = m_strModuleFolder;
            goto finishedCa2Module;
         }

         strModuleFileName = Application.dir().pathfind(getenv("LD_LIBRARY_PATH"),"core.dylib","rfs"); // readable - normal file - non zero sized

      }

   finishedCa2Module:;

#endif

#endif

      return strModuleFileName;


   }


   string system::get_module_folder()
   {

      return m_strModuleFolder;

   }


   string system::get_module_file_path()
   {

#ifdef WINDOWSEX

      wchar_t lpszModuleFilePath[MAX_PATH + 1];

      GetModuleFileNameW(NULL,lpszModuleFilePath,MAX_PATH + 1);

      string strModuleFileName(lpszModuleFilePath);

      return strModuleFileName;

#elif defined(METROWIN)

      return "m_app.exe";

#else

      char * lpszModuleFilePath = br_find_exe_dir("app");

      if(lpszModuleFilePath == NULL)
         return "";

      string strModuleFileName(lpszModuleFilePath);

      free(lpszModuleFilePath);

      return strModuleFileName;

#endif

   }


   string system::get_module_title()
   {

      return file_title(get_module_file_path());

   }


   string system::get_module_name()
   {

      return file_name(get_module_file_path());

   }

   colorertake5::ParserFactory & system::parser_factory()
   {

      if(m_pparserfactory == NULL)
      {

         m_pparserfactory = new colorertake5::ParserFactory(this);

      }

      return *m_pparserfactory;

   }


   string system::dir_appmatter_locator(sp(::aura::application) papp)
   {

      throw not_implemented(get_app());

   }


   ::user::interaction * system::get_focus_guie()
   {

      return NULL;

   }

} // namespace aura






uint32_t _thread_proc_start_system(void * p)
{

   ::aura::system * psystem = (::aura::system *)p;

   return psystem->main();

}

CLASS_DECL_AURA void __start_system(::aura::system * psystem)
{

   ::create_thread(NULL,0,&_thread_proc_start_system,(LPVOID)psystem,0,0);

}

