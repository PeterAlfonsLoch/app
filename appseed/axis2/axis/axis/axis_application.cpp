#include "framework.h"


#if defined(CUBE)


void draw2d_factory_exchange(sp(::axis::application) papp);


#endif


#if defined(APPLEOS)

void openURL(const string &url_str);

#endif

#if defined(LINUX)
#ifdef _GNU_SOURCE
#undef _GNU_SOURCE
#endif
#define _GNU_SOURCE
#define __USE_GNU
#include <link.h>
#elif defined(APPLEOS)
#include <dlfcn.h>
#endif


void dappy(const char * psz)
{

   //printf("app._ : %s : %s\n",_argv[2],psz);
   //printf("hello!!    : %s\n",psz);
   //::OutputDebugString("hello!!    : " + string(psz) + "\n");

}


namespace axis
{

   UINT application::APPM_LANGUAGE = WM_APP + 117;
   WPARAM application::WPARAM_LANGUAGE_UPDATE = 1;


   application::application():
      m_allocer(this),
      m_mutexMatterLocator(this),
      m_mutexStr(this)
   {

      m_peventReady = NULL;


#ifdef WINDOWS

      m_hinstance                = NULL;

#endif

      if(m_pbaseapp == NULL)
      {

         m_pbaseapp              = this;

      }

      if(m_pbaseapp != NULL)
      {

         m_pbasesystem           = m_pbaseapp->m_pbasesystem;

         if(m_pbaseapp->m_pbasesession == NULL && m_pbasesystem != NULL)
         {

            m_pbasesession       = m_pbasesystem->m_pbasesession;

         }
         else
         {

            m_pbasesession       = m_pbaseapp->m_pbasesession;

         }

#ifdef WINDOWS

         m_hinstance             = m_pbaseapp->m_hinstance;

#endif

      }
      else
      {

         m_pbasesystem           = NULL;

      }

      m_pcoreapp                 = NULL;

      


      m_bLicense                 = true;

      // initialize wait cursor state
      m_iWaitCursorCount         = 0;

      m_bAxisProcessInitialize         = false;
      m_bAxisProcessInitializeResult   = false;

      m_bAxisInitialize1               = false;
      m_bAxisInitialize1Result         = false;

      m_bAxisInitialize                = false;
      m_bAxisInitializeResult          = false;

      m_bAxisInitializeInstance        = false;
      m_bAxisInitializeInstanceResult  = false;



      m_pinitmaindata = NULL;


   }

   application::~application()
   {
   }



   
   int32_t application::simple_message_box(const char * pszMessage,UINT fuStyle)
   {

#if defined(WINDOWSEX)

      return ::simple_message_box(NULL,pszMessage,m_strAppName,fuStyle);
      //return MessageBoxW(NULL,wstring(pszMessage),wstring(m_strAppName),fuStyle);
      //return MessageBoxW((puiOwner == NULL ? NULL : (puiOwner->get_wnd() == NULL ? NULL : puiOwner->get_handle())),
      //   wstring(pszMessage), wstring(m_strAppName), fuStyle);

#elif  defined(LINUX) || defined(APPLEOS) || defined(ANDROID)

      return ::simple_message_box(NULL, pszMessage, m_strAppName, fuStyle);
      //   return simple_message_box((puiOwner == NULL ? NULL : (puiOwner->get_wnd() == NULL ? NULL : puiOwner->get_handle())), pszMessage, m_strAppName, fuStyle);

#else

      return ::simple_message_box(NULL, pszMessage, m_strAppName, fuStyle);

#endif

   }

   string application::message_box(const string & pszMatter,property_set & propertyset)
   {

      simple_message_box(pszMatter,0);

      return "";

   }

   sp(element) application::alloc(sp(type) info)
   {
      return System.alloc(this,info);
   }

   sp(element) application::alloc(const  id & idType)
   {
      return System.alloc(this,idType);
   }

   bool application::is_system()
   {

      return false;

   }

   bool application::is_session()
   {

      return false;

   }


   bool application::is_serviceable()
   {

      return false;

   }
   
   bool application::load_string(string & str,id id)
   {
      str = id;
      return true;
   }
   

   bool application::app_map_lookup(const char * psz,void * & p)
   {
      return m_appmap.Lookup(psz,p) != FALSE;
   }

   void application::app_map_set(const char * psz,void * p)
   {
      m_appmap.set_at(psz,p);
   }

   bool application::verb()
   {
      return true;
   }

   class open_url
   {
   public:
      string m_strLink;
      string m_strTarget;
      open_url(const string & strLink,const string & pszTarget);
      bool open();
   };




   open_url::open_url(const string & strLink,const string & pszTarget)
   {
      m_strLink = strLink;
      m_strTarget = pszTarget;
   }


   uint32_t c_cdecl thread_proc_open_url(void * p)
   {

      open_url * popenurl = (open_url *) p;

      if(!popenurl->open())
         return -1;

      return 0;
   }

   bool open_url::open()
   {
      string strLink = m_strLink;
      string pszTarget = m_strTarget;
#ifdef WINDOWSEX
      string strUrl = strLink;
      if(!::str::begins_ci(strUrl,"http://")
         && !::str::begins_ci(strUrl,"https://"))
      {
         strUrl = "http://" + strUrl;
      }
      ::ShellExecuteA(NULL,"open",strUrl,NULL,NULL,SW_SHOW);
      return true;
#elif defined METROWIN
#pragma push_macro("System")
#undef System
      ::Windows::Foundation::Uri ^ uri = ref new ::Windows::Foundation::Uri(strLink);
      ::Windows::System::LauncherOptions ^ options = ref new ::Windows::System::LauncherOptions();
      options->TreatAsUntrusted = false;
      bool success = ::wait(::Windows::System::Launcher::LaunchUriAsync(uri,options));

      return success;

#pragma pop_macro("System")
#elif defined(LINUX)
      ::system("xdg-open " + strLink);
      return true;
#elif defined(APPLEOS)
      openURL(strLink);
      return true;
#else
      throw not_implemented(get_thread_app());
#endif

   }


   bool application::open_link(const string & strLink,const string & pszTarget)
   {
      if(is_system())
      {
         return create_thread(NULL, 0, thread_proc_open_url,new open_url(strLink, pszTarget), 0, NULL) != FALSE;
      }
      else
      {
         return System.open_link(strLink,pszTarget);
      }

      return false;

   }





   void application::DoWaitCursor(int32_t nCode)
   {

      if(nCode < 0)
      {

         m_iWaitCursorCount = 0;
         ShowWaitCursor(false);

      }
      else if(nCode == 0)
      {

         if(m_iWaitCursorCount > 0)
         {
            m_iWaitCursorCount--;
         }

         if(m_iWaitCursorCount > 0)
         {

            ShowWaitCursor(true);

         }

         m_iWaitCursorCount = 0;
         ShowWaitCursor(false);

      }
      else
      {

         if(m_iWaitCursorCount < 0)
         {
            m_iWaitCursorCount = 0;
         }

         m_iWaitCursorCount++;

         ShowWaitCursor(true);

      }



   }

   void application::ShowWaitCursor(bool bShow)
   {

      if(m_pimpl == NULL)
         return;

      m_pimpl->ShowWaitCursor(bShow);

   }



   void application::construct(const char * pszAppId)
   {

   }



   void application::TermThread(HINSTANCE hInstTerm)
   {

      throw interface_only_exception(this);

   }




   string application::get_version()
   {

      throw interface_only_exception(this);

   }


   void application::SetCurrentHandles()
   {

   }


   void application::set_env_var(const string & var,const string & value)
   {

      throw interface_only_exception(this);

   }




   bool application::_001OnDDECommand(const char * lpcsz)
   {

      throw interface_only_exception(this);

   }


   void application::_001EnableShellOpen()
   {

      throw interface_only_exception(this);

   }


   bool application::update_module_paths()
   {


      if(is_system())
      {

         if(!m_pimpl->update_module_paths())
            return false;


      }

      return true;


   }



   string application::veriwell_multimedia_music_midi_get_default_library_name()
   {

      if(m_pimpl == NULL)
         return "";

      return m_pimpl->veriwell_multimedia_music_midi_get_default_library_name();

   }



   string application::multimedia_audio_mixer_get_default_library_name()
   {

      if(m_pimpl == NULL)
         return "";

      return m_pimpl->multimedia_audio_mixer_get_default_library_name();

   }



   string application::multimedia_audio_get_default_library_name()
   {

      if(m_pimpl == NULL)
         return "";

      return m_pimpl->multimedia_audio_get_default_library_name();

   }



   string application::draw2d_get_default_library_name()
   {

      if(m_pimpl == NULL)
         return "draw2d_cairo";

      return m_pimpl->draw2d_get_default_library_name();

   }










   void application::_001CloseApplication()
   {

      throw todo(get_app());

   }







   uint32_t application::get_thread_id()
   {
      return m_pimpl->get_thread_id();
   }





#ifndef METROWIN

   void application::get_time(timeval *p)
   {
      m_pimpl->get_time(p);
   }

#endif








   bool application::final_handle_exception(::exception::exception & e)
   {
      UNREFERENCED_PARAMETER(e);
      //linux      exit(-1);

      if(!is_system())
      {

         // get_app() may be it self, it is ok...
         if(Sys(get_app()).final_handle_exception((::exception::exception &) e))
            return true;


      }

      return false;
   }





   int32_t application::main()
   {

      return 0;

   }




   bool application::pre_run()
   {

      return true;


   }




   int32_t application::on_run()
   {
      
      return 0;

   }




   int32_t application::application_pre_run()
   {

      return 0;

   }



   bool application::InitApplication()
   {

      return true;

   }



   bool application::initial_check_directrix()
   {

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


   bool application::system_add_app_install(const char * pszId)
   {

      return true;

   }



   bool application::os_native_bergedge_start()
   {

      return true;

   }



   int32_t application::run()
   {

      return 0;

   }


   bool application::safe_is_running()
   {

      bool bRunning = false;

      try
      {

         if(is_running())
         {

            bRunning = true;

         }

      }
      catch(...)
      {

         bRunning = false;

      }


      return bRunning;

   }


   sp(application) application::assert_running(const char * pszAppId)
   {

      return NULL;

   }





   typedef  void(*PFN_ca2_factory_exchange)(sp(application) papp);




   /*::file::binary_buffer_sp application::friendly_get_file(var varFile, UINT nOpenFlags)
   {

   try
   {

   return m_file.get_file(varFile, nOpenFlags);

   }
   catch (::file::exception & e)
   {

   string strMessage = e.get_message();

   App(this).simple_message_box(NULL, strMessage, MB_OK);

   return NULL;

   }

   }
   */




   bool application::is_installing()
   {

      return false;

   }


   bool application::is_uninstalling()
   {

      return false;

   }


   bool application::create_new_service()
   {

      if(m_pservice != NULL)
         return false;

      m_pservice = allocate_new_service();

      if(m_pservice == NULL)
         return false;

      return true;

   }



   bool application::create_service()
   {

      return false;

   }

   bool application::remove_service()
   {

      return false;

   }

   bool application::start_service()
   {

      return false;

   }

   bool application::stop_service()
   {

      return false;

   }



   bool application::process_initialize()
   {

      if(m_bAxisProcessInitialize)
         return m_bAxisProcessInitializeResult;

      m_bAxisProcessInitialize = true;
      m_bAxisProcessInitializeResult = false;


      

      
      m_pimpl.alloc(allocer());

      m_pimpl->construct(NULL);

      m_pimpl->m_pimpl = this;


      if(is_system())
      {

         if(!update_module_paths())
            return false;

      }


      if(!ca_process_initialize())
         return false;

      if(is_system())
      {

         draw2d_factory_exchange();

      }

      if(!m_pimpl->process_initialize())
         return false;


      m_bAxisProcessInitializeResult = true;

      return true;

   }


   bool application::initialize_instance()
   {

      return true;

      return true;

   }


   bool application::initialize1()
   {

      if(m_bAxisInitialize1)
         return m_bAxisInitialize1Result;

      m_bAxisInitialize1 = true;

      m_bAxisInitialize1Result = false;


      if(!ca_initialize1())
         return false;





      if(!m_pimpl->initialize1())
         return false;

      m_bAxisInitialize1Result = true;

      return true;

   }


   bool application::initialize2()
   {

      if(!m_pimpl->initialize2())
         return false;

      if(!ca_initialize2())
         return false;

      return true;

   }


   bool application::initialize3()
   {

      if(!m_pimpl->initialize3())
         return false;

      if(!ca_initialize3())
         return false;

      return true;

   }


   bool application::initialize()
   {

      if(m_bAxisInitialize)
         return m_bAxisInitializeResult;

      m_bAxisInitialize = true;
      m_bAxisInitializeResult = false;



      return true;

   }


   int32_t application::exit_instance()
   {


      return 0;

   }


   bool application::finalize()
   {

      return true;

   }






   bool application::is_running()
   {
      return is_alive();
   }

   service_base * application::allocate_new_service()
   {

      return NULL;

   }







   bool application::ca_initialize2()
   {

      return true;

   }


   bool application::ca_initialize3()
   {


      return true;

   }










   bool application::check_exclusive()
   {

#ifdef METROWIN

      return true;

#endif

      bool bSetOk;

      LPSECURITY_ATTRIBUTES lpsa = NULL;

      bool bResourceException = false;

#ifdef WINDOWSEX

      bSetOk = false;

      SECURITY_ATTRIBUTES MutexAttributes;
      ZeroMemory(&MutexAttributes,sizeof(MutexAttributes));
      MutexAttributes.nLength = sizeof(MutexAttributes);
      MutexAttributes.bInheritHandle = FALSE; // object uninheritable
      // declare and initialize a security descriptor
      SECURITY_DESCRIPTOR SD;
      bool bInitOk = InitializeSecurityDescriptor(&SD,SECURITY_DESCRIPTOR_REVISION) != FALSE;
      if(bInitOk)
      {
         // give the security descriptor a Null Dacl
         // done using the  "TRUE, (PACL)NULL" here
         bSetOk = SetSecurityDescriptorDacl(&SD,
            TRUE,
            (PACL)NULL,
            FALSE) != FALSE;
      }

      if(bSetOk)
      {

         MutexAttributes.lpSecurityDescriptor = &SD;

         lpsa = &MutexAttributes;

      }

#else

      bSetOk = true;

#endif

      if(bSetOk)
      {
         // Make the security attributes point
         // to the security descriptor
         bResourceException = false;
         try
         {
            m_pmutexGlobal = new mutex(this,FALSE,get_global_mutex_name(),lpsa);
         }
         catch(resource_exception &)
         {
            try
            {
               m_pmutexGlobal = new mutex(this,FALSE,get_global_mutex_name());
            }
            catch(resource_exception &)
            {
               bResourceException = true;
            }
         }

         if(m_eexclusiveinstance == ExclusiveInstanceGlobal
            && (::GetLastError() == ERROR_ALREADY_EXISTS || bResourceException))
         {
            // Should in some way activate the other instance, but this is global, what to do? do not know yet.
            //System.simple_message_box("A instance of the application:<br><br>           - " + string(m_strAppName) + "<br><br>seems to be already running at the same machine<br>Only one instance of this application can run globally: at the same machine.<br><br>Exiting this new instance.");
            TRACE("A instance of the application:<br><br>           - " + string(m_strAppName) + "<br><br>seems to be already running at the same machine<br>Only one instance of this application can run globally: at the same machine.<br><br>Exiting this new instance.");
            on_exclusive_instance_conflict(ExclusiveInstanceGlobal);
            return false;
         }
         if(m_eexclusiveinstance == ExclusiveInstanceGlobalId)
         {
            bResourceException = false;
            try
            {
               m_pmutexGlobalId = new mutex(this,FALSE,get_global_id_mutex_name(),lpsa);
            }
            catch(resource_exception &)
            {
               try
               {
                  m_pmutexGlobalId = new mutex(this,FALSE,get_global_id_mutex_name());
               }
               catch(resource_exception &)
               {
                  bResourceException = true;
               }
            }
            if(::GetLastError() == ERROR_ALREADY_EXISTS || bResourceException)
            {
               // Should in some way activate the other instance
               //System.simple_message_box("A instance of the application:<br><br>           - " + string(m_strAppName) + "<br><br>seems to be already running at the same account.<br>Only one instance of this application can run locally: at the same account.<br><br>Exiting this new instance.");
               TRACE("A instance of the application:<br><br>           - " + string(m_strAppName) + "with the id \"" + get_local_mutex_id() + "\" <br><br>seems to be already running at the same machine<br>Only one instance of this application can run globally: at the same machine with the same id.<br><br>Exiting this new instance.");
               on_exclusive_instance_conflict(ExclusiveInstanceGlobalId);
               return false;
            }
         }
         bResourceException = false;
         try
         {
            m_pmutexLocal = new mutex(this,FALSE,get_local_mutex_name(),lpsa);
         }
         catch(resource_exception &)
         {
            try
            {
               m_pmutexLocal = new mutex(this,FALSE,get_local_mutex_name());
            }
            catch(resource_exception &)
            {
               bResourceException = true;
            }
         }
         if(m_eexclusiveinstance == ExclusiveInstanceLocal && (::GetLastError() == ERROR_ALREADY_EXISTS || bResourceException))
         {
            // Should in some way activate the other instance
            //System.simple_message_box("A instance of the application:<br><br>           - " + string(m_strAppName) + "<br><br>seems to be already running at the same account.<br>Only one instance of this application can run locally: at the same account.<br><br>Exiting this new instance.");
            TRACE("A instance of the application:<br><br>           - " + string(m_strAppName) + "<br><br>seems to be already running at the same account.<br>Only one instance of this application can run locally: at the same account.<br><br>Exiting this new instance.");
            on_exclusive_instance_conflict(ExclusiveInstanceLocal);
            return false;
         }
         if(m_eexclusiveinstance == ExclusiveInstanceLocalId)
         {
            bResourceException = false;
            try
            {
               m_pmutexLocalId = new mutex(this,FALSE,get_local_id_mutex_name(),lpsa);
            }
            catch(resource_exception &)
            {
               try
               {
                  m_pmutexLocalId = new mutex(this,FALSE,get_local_id_mutex_name());
               }
               catch(resource_exception &)
               {
                  bResourceException = true;
               }
            }
            if(::GetLastError() == ERROR_ALREADY_EXISTS || bResourceException)
            {
               // Should in some way activate the other instance
               //System.simple_message_box("A instance of the application:<br><br>           - " + string(m_strAppName) + "<br><br>seems to be already running at the same account.<br>Only one instance of this application can run locally: at the same account.<br><br>Exiting this new instance.");
               TRACE("A instance of the application:<br><br>           - " + string(m_strAppName) + "with the id \"" + get_local_mutex_id() + "\" <br><br>seems to be already running at the same account.<br>Only one instance of this application can run locally: at the same ac::count with the same id.<br><br>Exiting this new instance.");
               on_exclusive_instance_conflict(ExclusiveInstanceLocalId);
               return false;
            }
         }
      }
      else
      {
         return false;
      }

      return true;

   }

   bool application::release_exclusive()
   {
      if(m_pmutexGlobal.is_set())
      {
         m_pmutexGlobal.release();
      }
      if(m_pmutexGlobalId.is_set())
      {
         m_pmutexGlobalId.release();
      }
      if(m_pmutexLocal.is_set())
      {
         m_pmutexLocal.release();
      }
      if(m_pmutexLocalId.is_set())
      {
         m_pmutexLocalId.release();
      }
      return true;
   }



   bool application::ca_process_initialize()
   {
      return true;
   }

   bool application::ca_initialize1()
   {
      return true;
   }



   bool application::ca_finalize()
   {
      return true;
   }



   string application::get_local_mutex_name(const char * pszAppName)
   {
      string strMutex;
      strMutex.Format("Local\\ca2_application_local_mutex:%s",pszAppName);
      return strMutex;
   }

   string application::get_local_id_mutex_name(const char * pszAppName,const char * pszId)
   {
      string strId(pszId);
      string strMutex;
      strMutex.Format("Local\\ca2_application_local_mutex:%s, id:%s",pszAppName,strId.c_str());
      return strMutex;
   }

   string application::get_global_mutex_name(const char * pszAppName)
   {
      string strMutex;
      strMutex.Format("Global\\ca2_application_global_mutex:%s",pszAppName);
      return strMutex;
   }

   string application::get_global_id_mutex_name(const char * pszAppName,const char * pszId)
   {
      string strId(pszId);
      string strMutex;
      strMutex.Format("Global\\ca2_application_global_mutex:%s, id:%s",pszAppName,strId.c_str());
      return strMutex;
   }

   string application::get_local_mutex_name()
   {
      return get_local_mutex_name(get_mutex_name_gen());
   }

   string application::get_local_id_mutex_name()
   {
      return get_local_id_mutex_name(get_mutex_name_gen(),get_local_mutex_id());
   }

   string application::get_global_mutex_name()
   {
      return get_global_mutex_name(get_mutex_name_gen());
   }

   string application::get_global_id_mutex_name()
   {
      return get_global_id_mutex_name(get_mutex_name_gen(),get_global_mutex_id());
   }




   void application::on_exclusive_instance_conflict(EExclusiveInstance eexclusive)
   {
      if(eexclusive == ExclusiveInstanceLocal)
      {
         on_exclusive_instance_local_conflict();
      }
   }

   void application::on_exclusive_instance_local_conflict()
   {
   }


   string application::get_mutex_name_gen()
   {
      return m_strAppName;
   }

   string application::get_local_mutex_id()
   {
      return "";
   }

   string application::get_global_mutex_id()
   {
      return "";
   }

   ::mutex * application::get_local_mutex()
   {
      return m_pmutexLocal;
   }

   ::mutex * application::get_global_mutex()
   {
      return m_pmutexGlobal;
   }



   bool application::Ex2OnAppInstall()
   {
      return true;
   }

   bool application::Ex2OnAppUninstall()
   {
      return true;
   }


   void application::draw2d_factory_exchange()
   {



   }






   void application::on_set_scalar(e_scalar escalar,int64_t iValue)
   {

      //if (escalar == scalar_app_install_progress)
      //{

      //   m_iProgressInstallStep = iValue;

      //}
      //else if (escalar == scalar_app_install_progress_min)
      //{

      //   m_iProgressInstallStart = iValue;

      //}
      //else if (escalar == scalar_app_install_progress_max)
      //{

      //   m_iProgressInstallEnd = iValue;

      //}
      //else
      {

         return ::int_scalar_source::on_set_scalar(escalar,iValue);

      }

   }


   void application::get_scalar_minimum(e_scalar escalar,int64_t & i)
   {

      //if (escalar == scalar_app_install_progress)
      //{

      //   i = m_iProgressInstallStart;

      //}
      //else if (escalar == scalar_app_install_progress_min)
      //{

      //   i = 0;

      //}
      //else if (escalar == scalar_app_install_progress_max)
      //{

      //   i = 0;

      //}
      //else
      {

         ::int_scalar_source::get_scalar_minimum(escalar,i);

      }

   }

   void application::get_scalar(e_scalar escalar,int64_t & i)
   {

      //if (escalar == scalar_app_install_progress)
      //{

      //   i = m_iProgressInstallStep;

      //}
      //else if (escalar == scalar_app_install_progress_min)
      //{

      //   i = m_iProgressInstallStart;

      //}
      //else if (escalar == scalar_app_install_progress_max)
      //{

      //   i = m_iProgressInstallEnd;

      //}
      //else
      {

         ::int_scalar_source::get_scalar(escalar,i);

      }

   }

   void application::get_scalar_maximum(e_scalar escalar,int64_t & i)
   {

      //if (escalar == scalar_download_size)
      //{

      //   i = m_iProgressInstallEnd;

      //}
      //else if (escalar == scalar_app_install_progress_min)
      //{

      //   i = 0x7fffffff;

      //}
      //else if (escalar == scalar_app_install_progress_max)
      //{

      //   i = 0x7fffffff;

      //}
      //else
      {

         ::int_scalar_source::get_scalar_minimum(escalar,i);

      }

   }





   service_base * application::get_service()
   {

      return m_pservice;

   }








   application * application_ptra::find_by_app_name(const string & strAppName)
   {

      application * papp = NULL;

      for(int32_t i = 0; i < get_count(); i++)
      {
         try
         {

            papp = element_at(i).m_p;

            if(papp == NULL)
               continue;

            if(papp->m_strAppName == strAppName)
            {

               return papp;

            }

         }
         catch(...)
         {

         }

      }

      return NULL;


   }


   application * application_ptra::find_running_defer_try_quit_damaged(const string & strAppName)
   {

      return NULL;


   }




   string application::get_license_id()
   {

      return m_strAppId;

   }






   

   void application::assert_user_logged_in()
   {


   }

   bool application::init_main_data(::axis::main_init_data * pdata)
   {

      m_pinitmaindata = pdata;

      return true;

   }

   bool application::set_main_init_data(::axis::main_init_data * pdata)
   {

      return m_pimpl->set_main_init_data(pdata);

   }




} // namespace axis




#if defined(MACOS)

void openURL(const string &url_str);


void openURL(const string &url_str) {
   CFURLRef url = CFURLCreateWithBytes (
      NULL,                        // allocator
      (UInt8*)url_str.c_str(),     // URLBytes
      url_str.length(),            // length
      kCFStringEncodingASCII,      // encoding
      NULL                         // baseURL
      );
   LSOpenCFURLRef(url,0);
   CFRelease(url);
}

#elif defined(APPLE_IOS)

void openURL(const string &url_str);


void openURL(const string &url_str) {
   CFURLRef url = CFURLCreateWithBytes (
      NULL,                        // allocator
      (UInt8*)url_str.c_str(),     // URLBytes
      url_str.length(),            // length
      kCFStringEncodingASCII,      // encoding
      NULL                         // baseURL
      );
   //    LSOpenCFURLRef(url,0);
   CFRelease(url);
}


#endif
