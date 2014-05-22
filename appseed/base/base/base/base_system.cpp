#include "framework.h"


namespace base
{


   class ::id system::idEmpty;
   class ::id_space * system::s_pidspace = NULL;


   system::system(sp(::base::application) papp):
      m_urldepartament(this),
      //m_mutexDelete(this),
      m_httpsystem(this),
      m_net(this)
      //m_mutex(this),
#ifndef METROWIN
      //m_processsection(this),
#endif
      //m_visual(this),
      ,m_libraryDraw2d(this)
   {


      m_psimpleui = NULL;

#if defined(METROWIN) || defined(APPLE_IOS)
      m_posdata = new os_data();
#endif

      set_app(this);

      m_pbasesystem = this;

      if(papp == NULL)
      {

         oprop("parent_system") = (sp(element)) NULL;

      }
      else
      {

         oprop("parent_system") = papp->m_pbasesystem;

      }



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

      m_spinstall = new ::install::install(this);


#ifdef WINDOWS
      m_pmutexDc = NULL;
      m_pdevicecontext = NULL;
#endif


      //Ex1OnFactoryExchange();

      //m_spfilesystem.create(allocer());


      /*   {

            draw2d_gdiplus::factory_exchange factoryexchange(this);

            }*/

      m_pxml = canew(::xml::departament(this));

      m_pxml->construct(this);

      if(!m_pxml->initialize1())
         throw simple_exception(this,"failed to construct system");

      if(!m_pxml->initialize())
         throw simple_exception(this,"failed to construct system");


      m_compress.set_app(this);


   }


   void system::construct()
   {

      ::base::application::construct();




   }
   base_factory & system::factory()
   {
      return *m_pfactory;
   }


   ::exception::engine & system::eengine()
   {

      static ::exception::engine s_eengine(NULL);

      return s_eengine;

   }


   bool system::process_initialize()
   {

      m_pfactory->cloneable_large < create_context >();
      m_pfactory->cloneable_large < application_bias >();
      m_pfactory->cloneable_large < command_line >();
      m_pfactory->cloneable_large < manual_reset_event >();
      m_pfactory->cloneable_large < mutex >();
      m_pfactory->cloneable_large < event >();

      if(!::base::application::process_initialize())
         return false;

      m_spos.create(allocer());

      m_spfile.create(allocer());

      m_spdir.create(allocer());

      if(!m_spdir->initialize())
         return false;

      m_spcrypto.create(allocer());

      if(!m_spcrypto.is_set())
         return false;

      return true;

   }




   bool system::initialize_instance()
   {

      m_pfactory->enable_simple_factory_request();

      if(!::base::application::initialize_instance())
         return false;

      return true;

   }


   int32_t system::exit_instance()
   {

      ::base::application::exit_instance();

#ifdef WINDOWS

      m_pdevicecontext = nullptr;

      m_pmutexDc.release();

#endif

      return 0;

   }


   UINT system::os_post_to_all_threads(UINT uiMessage,WPARAM wparam,lparam lparam)
   {

      throw interface_only_exception(this);

      return -1;

   }

   sp(element) system::clone()
   {
      // by the time, it is not possible to clone a system
      return NULL;
   }

   sp(element) system::clone(sp(element) pobj)
   {
      return System.factory().base_clone(pobj);
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




   sp(element) system::on_alloc(sp(::base::application) papp,sp(type) info)
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

   sp(element) system::alloc(sp(::base::application) papp,sp(type) info)
   {
      return on_alloc(papp,info);
   }

   sp(element) system::alloc(sp(::base::application) papp,const std_type_info & info)
   {
      return on_alloc(papp,canew(type(info)));
   }

   void system::on_allocation_error(sp(::base::application) papp,sp(type) info)
   {
      UNREFERENCED_PARAMETER(papp);
      UNREFERENCED_PARAMETER(info);
   }

   sp(element) system::alloc(sp(::base::application) papp,const class id & idType)
   {
      return on_alloc(papp,get_type_info(idType));
   }


   sp(type) system::get_type_info(const ::std_type_info & info)
   {

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





   ::sockets::net & system::net()
   {
      return m_net;
   }



   class ::crypto::crypto & system::crypto()
   {
      return *m_spcrypto;
   }



   ::datetime::departament & system::datetime()
   {
      return *m_pdatetime;
   }



   sp(::user::window_draw) system::get_twf()
   {

      return m_ptwf;

   }

   ::base::log & system::log()
   {
      return *m_plog;
   }




   ::fontopus::user_set & system::userset()
   {
      return m_userset;
   }



   ::base::compress & system::compress()
   {
      return m_compress;
   }



   machine_event_central & system::machine_event_central()
   {
      return *m_pmachineeventcentral;
   }


   ::user::str & system::str()
   {

      return *m_puserstr;

   }


   sp(::user::object) system::place_hold(sp(::user::interaction) pui)
   {


      //if(m_pcubeInterface != NULL)
      //{
      // return m_pcubeInterface->hold(pui);
      //}

      return NULL;

   }


   sp(::base_session) system::query_session(index iEdge)
   {

      return NULL;

   }


   ::base::os & system::os()
   {

      return *m_spos;

   }




   bool system::initialize_log(const char * pszId)
   {
      if(m_plog != NULL)
         return true;
      m_plog = new ::base::log(this);
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


   application_ptra & system::appptra()
   {
      return m_appptra;
   }




   void system::appa_load_string_table()
   {

      retry_single_lock rsl(m_pmutex,millis(84),millis(84));

      for(int32_t i = 0; i < appptra().get_size(); i++)
      {
         sp(::base::application) papp = appptra()(i);
         papp->load_string_table();
      }

   }

   void system::appa_set_locale(const char * pszLocale,::action::context actioncontext)
   {

      retry_single_lock rsl(m_pmutex,millis(84),millis(84));

      for(int32_t i = 0; i < appptra().get_size(); i++)
      {
         sp(::base::application) papp = appptra()(i);
         papp->set_locale(pszLocale,actioncontext);
      }

   }

   void system::appa_set_schema(const char * pszStyle,::action::context actioncontext)
   {

      retry_single_lock rsl(m_pmutex,millis(84),millis(84));

      for(int32_t i = 0; i < appptra().get_size(); i++)
      {
         sp(::base::application) papp = appptra()(i);
         papp->set_schema(pszStyle,actioncontext);
      }

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







   bool system::create_twf()
   {
      if(m_ptwf != NULL)
         return true;
      m_ptwf = alloc(this,System.type_info < ::user::window_draw >());
      m_ptwf->twf_start();
      return true;
   }




} // namespace base


uint32_t _thread_proc_start_system(void * p)
{

   ::base::system * psystem = (::base::system *)p;

   return psystem->main();

}

CLASS_DECL_BASE void __start_system(::base::system * psystem)
{

   ::create_thread(NULL,0,&_thread_proc_start_system,(LPVOID)psystem,0,0);

}
