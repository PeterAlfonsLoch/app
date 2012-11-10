#include "framework.h"

namespace ex2
{

   application::application()
   {
      m_pinitmaindata = NULL;
   }

   application::~application()
   {
      ::ca::smart_pointer < application >::m_p = NULL;
   }

   void application::construct()
   {
   }

   void application::construct(const char * pszId)
   {
      UNREFERENCED_PARAMETER(pszId);
   }

   void application::_001OnFileNew(gen::signal_object * pobj)
   {

      UNREFERENCED_PARAMETER(pobj);

      var varFile;
      var varQuery;

      varQuery["command"] = "new_file";

      request(varFile, varQuery);

      //::ca::smart_pointer < application >::m_p->_001OnFileNew();
   }

   ::user::document_interface * application::_001OpenDocumentFile(var varFile)
   {
      return ::ca::smart_pointer < application >::m_p->_001OpenDocumentFile(varFile);
   }

   void application::_001EnableShellOpen()
   {
       ::ca::smart_pointer < application >::m_p->_001EnableShellOpen();
   }

   bool application::_001OnDDECommand(const char * lpcsz)
   {
      return ::ca::smart_pointer < application >::m_p->_001OnDDECommand(lpcsz);
   }

   ::ex1::file_system & application::file_system()
   {
      return m_spfilesystem;
   }

   bool application::process_initialize()
   {

      if(!::gen::application::process_initialize())
         return false;

      if(is_system())
      {
         Ex1OnFactoryExchange();
      }

      ::radix::thread::s_bAllocReady = true;
      if(::ca::thread_sp::m_p == NULL)
      {
         ::ca::thread_sp::create(this);
         ::ca::smart_pointer < application >::create(this);
         smart_pointer < application >::m_p->construct();
         smart_pointer < application >::m_p->smart_pointer < application >::m_p = this;
         gen::add_ref(this);
         ::ca::thread_sp::m_p = smart_pointer < application >::m_p->::ca::thread_sp::m_p;
         gen::add_ref(smart_pointer < application >::m_p->::ca::thread_sp::m_p);
         ::ca::thread_sp::m_p->set_p(this);
         gen::add_ref(this);
      }
      else
      {
         ::ca::smart_pointer < application >::create(this);
         smart_pointer < application >::m_p->construct();
         smart_pointer < application >::m_p->smart_pointer < application >::m_p = this;
         gen::add_ref(this);
         smart_pointer < application >::m_p->::ca::thread_sp::m_p = ::ca::thread_sp::m_p;
         gen::add_ref(::ca::thread_sp::m_p);
      }
      set_thread(dynamic_cast < ::radix::thread * > (this));
      //m_pappDelete = this;
      //::ca::thread_sp::m_p->m_pappDelete = this;

      if(is_system())
      {
         if(!set_main_init_data(m_pinitmaindata))
            return false;
      }


      if(!smart_pointer < application >::m_p->process_initialize())
            return false;


      return true;
   }

   bool application::initialize1()
   {

      if(!smart_pointer < application >::m_p->initialize1())
         return false;

      if(!gen::application::initialize1())
         return false;

      return true;
   }

   bool application::initialize2()
   {
      if(!smart_pointer < application >::m_p->initialize2())
         return false;
      return gen::application::initialize2();
   }

   bool application::initialize3()
   {
      if(!smart_pointer < application >::m_p->initialize3())
         return false;
      return gen::application::initialize3();
   }

   bool application::initialize()
   {
      m_spfilesystem.create(this);
      if(!gen::application::initialize())
         return false;
      return true;
   }

   bool application::finalize()
   {
      bool bOk = true;
      try
      {
         m_spfilesystem.destroy();
      }
      catch(...)
      {
      }
      try
      {
         if(!gen::application::finalize())
         {
            TRACE("There occurred errors while finalizing gen::application virtual member function");
            bOk = false;
         }
      }
      catch(...)
      {
      }
      return bOk;
   }

   int application::exit_instance()
   {
      if(is_system())
      {

         try
         {
            if(m_spfilesystem.m_p != NULL)
            {
               gen::del(m_spfilesystem.m_p);
            }
         }
         catch(...)
         {
         }
      }

      try
      {
         // avoid calling CloseHandle() on our own thread handle
         // during the thread destructor
         // avoid thread object data auto deletion on thread termination,
         // letting thread function terminate
         ::ca::thread_sp::m_p->m_bAutoDelete = false;

         ::ca::thread_sp::m_p->set_os_data(NULL);

         ::ca::thread_sp::m_p->set_run(false);
         ::ca::smart_pointer < ::ex2::application >::m_p->::ca::thread_sp::m_p->set_run(false);
      }
      catch(...)
      {
      }

      try
      {
         ::ca::smart_pointer < ::ex2::application >::m_p->exit_instance();
      }
      catch(...)
      {
      }

      try
      {
         ::gen::application::exit_instance();
      }
      catch(...)
      {
      }

      return 0;
   }

   ::ca::application * application::get_app() const
   {
      return gen::application::get_app();
   }

   void application::assert_valid() const
   {
      gen::application::assert_valid();
   }

   void application::dump(dump_context & dumpcontext) const
   {
      gen::application::dump(dumpcontext);
   }


   string application::get_version()
   {
      return ::ca::smart_pointer < application >::m_p->get_version();
   }


   bool application::Ex2OnAppInstall()
   {
      return true;
   }

   bool application::Ex2OnAppUninstall()
   {
      return true;
   }


   bool application::DeferRegisterClass(LONG fToRegister, const char ** ppszClass)
   {
      return ::ca::smart_pointer < ::ex2::application >::m_p->DeferRegisterClass(fToRegister, ppszClass);
   }

   void application::LockTempMaps()
   {
      ::ca::smart_pointer < ::ex2::application >::m_p->LockTempMaps();
   }
   bool application::UnlockTempMaps(bool bDeleteTemp)
   {
      return ::ca::smart_pointer < ::ex2::application >::m_p->UnlockTempMaps(bDeleteTemp);
   }

   const char * application::RegisterWndClass(UINT nClassStyle, HCURSOR hCursor, HBRUSH hbrBackground, HICON hIcon)
   {
      return ::ca::smart_pointer < ::ex2::application >::m_p->RegisterWndClass(nClassStyle, hCursor, hbrBackground, hIcon);
   }

   ::radix::thread * application::GetThread()
   {
      if(::ca::smart_pointer < ::ex2::application >::m_p == NULL)
         return NULL;
      return ::ca::smart_pointer < ::ex2::application >::m_p->GetThread();
   }

   void application::set_thread(::radix::thread * pthread)
   {
      ::ca::smart_pointer < ::ex2::application >::m_p->set_thread(pthread);
   }

   ::user::interaction * application::GetMainWnd()
   {
      if(m_puiMain != NULL)
         return m_puiMain;
      return NULL;
   }

/*   ::ca::graphics * application::graphics_from_os_data(void * pdata)
   {
      return ::ca::smart_pointer < ::ex2::application >::m_p->graphics_from_os_data(pdata);
   }*/

   ::ca::window * application::window_from_os_data(void * pdata)
   {
      return ::ca::smart_pointer < ::ex2::application >::m_p->window_from_os_data(pdata);
   }

   ::ca::window * application::window_from_os_data_permanent(void * pdata)
   {
      return ::ca::smart_pointer < ::ex2::application >::m_p->window_from_os_data_permanent(pdata);
   }

   ::ca::window * application::get_desktop_window()
   {
#ifdef METROWIN
      throw todo(this);
#else
      return window_from_os_data(::GetDesktopWindow());
#endif
   }

   void application::SetCurrentHandles()
   {
      ::ca::smart_pointer < ::ex2::application >::m_p->SetCurrentHandles();
   }

   ::ca::window * application::FindWindow(const char * lpszClassName, const char * lpszWindowName)
   {
      return ::ca::smart_pointer < ::ex2::application >::m_p->FindWindow(lpszClassName, lpszWindowName);
   }

   ::ca::window * application::FindWindowEx(oswindow oswindowParent, oswindow oswindowChildAfter, const char * lpszClass, const char * lpszWindow)
   {
      return ::ca::smart_pointer < ::ex2::application >::m_p->FindWindowEx(oswindowParent, oswindowChildAfter, lpszClass, lpszWindow);
   }

#ifndef METROWIN

   void application::get_time(timeval *p)
   {
      ::ca::smart_pointer < ::ex2::application >::m_p->get_time(p);
   }

#endif

   void application::set_env_var(const string & var,const string & value)
   {
      ::ca::smart_pointer < ::ex2::application >::m_p->set_env_var(var, value);
   }

   unsigned long application::get_thread_id()
   {
      return ::ca::smart_pointer < ::ex2::application >::m_p->get_thread_id();
   }

   bool application::set_main_init_data(::ca::main_init_data * pdata)
   {
      return ::ca::smart_pointer < ::ex2::application >::m_p->set_main_init_data(pdata);
   }


} // namespace ex2
