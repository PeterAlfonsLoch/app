#include "StdAfx.h"

namespace ca
{
   application::application() :
      ::radix::thread(NULL)
   {
      set_app(this);

      m_bInitializeProDevianMode = true;

      // almost always forgotten, assumed, as exception, responsability of application to add first ref on constructor.
      gen::add_ref(this);

      m_puiInitialPlaceHolderContainer = NULL;
      profiler::initialize();
      _setmbcp(CP_UTF8);
//      DWORD dw = ::_getmbcp();
#ifdef WIN32
      srand(::GetTickCount());
#else
      srand(microtime());
#endif

      m_pinitmaindata = NULL;
      m_bService = false;
   }


   application::~application()
   {
   }

   void application::construct()
   {
   }

   void application::construct(const char * pszId)
   {
      UNREFERENCED_PARAMETER(pszId);
   }

   application * application::get_app() const
   {
      return ::ca::ca::get_app();
   }

   bool application::process_initialize()
   {
      signal_object signal(&m_signal, signal_process_initialize);
      m_signal.emit(&signal);
      return true;
   }

   bool application::initialize1()
   {
      
      if(!is_system())
      {
         System.register_bergedge_application(this);
      }

      signal_object signal(&m_signal, signal_initialize1);
      m_signal.emit(&signal);
      return signal.m_bOk;
   }
   
   bool application::initialize2()
   {
      signal_object signal(&m_signal, signal_initialize2);
      m_signal.emit(&signal);
      return signal.m_bOk;
   }
   
   bool application::initialize3()
   {
      signal_object signal(&m_signal, signal_initialize3);
      m_signal.emit(&signal);
      return signal.m_bOk;
   }

   bool application::initialize()
   {
      signal_object signal(&m_signal, signal_initialize);
      m_signal.emit(&signal);
      return signal.m_bOk;
   }

   bool application::finalize()
   {
      signal_object signal(&m_signal, signal_finalize);
      try
      {
         m_signal.emit(&signal);
      }
      catch(...)
      {
      }




      return signal.m_bOk;
   }



   bool application::final_handle_exception(exception & e)
   {
      UNREFERENCED_PARAMETER(e);
//linux      exit(-1);
      return false;
   }


   bool application::open_link(const char * pszLink, const char * pszTarget)
   {
      UNREFERENCED_PARAMETER(pszLink);
      UNREFERENCED_PARAMETER(pszTarget);
      return false;
   }

   int application::exit()
   {
      return thread::exit(); 
   }

   int application::exit_instance()
   {
      signal_object signal(&m_signal, signal_exit_instance);
      try
      {
         m_signal.emit(&signal);
      }
      catch(...)
      {
      }

      try
      {
         if(!is_system())
         {
            System.unregister_bergedge_application(this);
         }
      }
      catch(...)
      {
      }

      try
      {
         gen::release(smart_pointer <::ca::thread>::m_p);
      }
      catch(...)
      {
      }


      return 0;
/*      int nReturnValue=0;
      if(AfxGetCurrentMessage())
      {
         nReturnValue=static_cast<int>(AfxGetCurrentMessage()->wParam);
      }*/
//      return nReturnValue; // returns the value from PostQuitMessage
   }


   // Temporary ::collection::map management (locks temp ::collection::map on current thread)
   void application::LockTempMaps()
   {
   }

   BOOL application::UnlockTempMaps(BOOL bDeleteTemps)
   {
      UNREFERENCED_PARAMETER(bDeleteTemps);
      return TRUE;
   }

   void application::TermThread(HINSTANCE hInstTerm)
   {
      UNREFERENCED_PARAMETER(hInstTerm);
   }

   graphics * application::graphics_from_os_data(void * pdata)
   {
      UNREFERENCED_PARAMETER(pdata);
      return NULL;
   }

   window * application::window_from_os_data(void * pdata)
   {
      UNREFERENCED_PARAMETER(pdata);
      return NULL;
   }

   window * application::window_from_os_data_permanent(void * pdata)
   {
      UNREFERENCED_PARAMETER(pdata);
      return NULL;
   }

   window* application::FindWindow(const char * lpszClassName, const char * lpszWindowName)
   {
      UNREFERENCED_PARAMETER(lpszClassName);
      UNREFERENCED_PARAMETER(lpszWindowName);
      throw not_implemented_exception();   
   }
   window* application::FindWindowEx(HWND hwndParent, HWND hwndChildAfter, const char * lpszClass, const char * lpszWindow)
   {
      UNREFERENCED_PARAMETER(hwndParent);
      UNREFERENCED_PARAMETER(hwndChildAfter);
      UNREFERENCED_PARAMETER(lpszClass);
      UNREFERENCED_PARAMETER(lpszWindow);
      throw not_implemented_exception();   
   }

   string application::get_local_mutex_name(const char * pszAppName)
   {
      string strMutex;
      strMutex.Format("Local\\ca2_fontopus_votagus_application_local_mutex:%s", pszAppName);
      return strMutex;
   }

   string application::get_local_id_mutex_name(const char * pszAppName, const char * pszId)
   {
      string strId(pszId);
      string strMutex;
      strMutex.Format("Local\\ca2_fontopus_votagus_application_local_mutex:%s, id:%s", pszAppName, strId);
      return strMutex;
   }

   string application::get_global_mutex_name(const char * pszAppName)
   {
      string strMutex;
      strMutex.Format("Global\\ca2_fontopus_votagus_application_global_mutex:%s", pszAppName);
      return strMutex;
   }

   string application::get_global_id_mutex_name(const char * pszAppName, const char * pszId)
   {
      string strId(pszId);
      string strMutex;
      strMutex.Format("Global\\ca2_fontopus_votagus_application_global_mutex:%s, id:%s", pszAppName,  strId);
      return strMutex;
   }

   string application::get_local_mutex_name()
   {
      return get_local_mutex_name(get_mutex_name_radix());
   }

   string application::get_local_id_mutex_name()
   {
      return get_local_id_mutex_name(get_mutex_name_radix(), get_local_mutex_id());
   }

   string application::get_global_mutex_name()
   {
      return get_global_mutex_name(get_mutex_name_radix());
   }

   string application::get_global_id_mutex_name()
   {
      return get_global_id_mutex_name(get_mutex_name_radix(), get_global_mutex_id());
   }

   string application::load_string(id id)
   {
      UNREFERENCED_PARAMETER(id);
      return "";
   }

/*
   string application::load_string(UINT uiId, wchar_t * lpBuffer, int nBufferMax)
   {
      UNREFERENCED_PARAMETER(uiId);
      UNREFERENCED_PARAMETER(lpBuffer);
      UNREFERENCED_PARAMETER(nBufferMax);
      return -1;
   }
*/

   application::signal_object::signal_object(gen::signal * psignal, e_signal esignal) :
      gen::signal_object(psignal)
   {

      g_pfnca2_alloc = base_ca2_alloc;
      g_pfnca2_alloc_dbg = base_ca2_alloc_dbg;
      g_pfnca2_realloc = base_ca2_realloc;
      g_pfnca2_free = base_ca2_free;


      m_esignal         = esignal;
      m_bOk             = true;

   }

   bool application::is_system()
   {
      return m_psystem == this;
   }

   ::ca::ca * application::alloc(const ::ca::type_info & info)
   {
      return System.alloc(this, info);
   }

   bool application::init_main_data(void * pdata)
   {
      m_pinitmaindata = pdata;
      return true;
   }
      
   bool application::set_main_init_data(void * pdata)
   {
      return true;
   }

   int application::main()
   {
      return 0;
   }

   bool application::bergedge_start()
   {
      return true;
   }

   bool application::os_native_bergedge_start()
   {
      return true;
   }

} // namespace ca


