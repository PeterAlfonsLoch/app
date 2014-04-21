#include "framework.h"


class ::id base_system::idEmpty;
class ::id_space * base_system::s_pidspace = NULL;


base_system::base_system(sp(base_application) papp) :
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

#ifdef METROWIN
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

   
   xxdebug_box("Going to start Log", "Just before initialize log", 0);

   // log starts here
   if(!initialize_log(strId))
   {
   xxdebug_box("Could not initialize log", "Failed to initialize log", 0);
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

   if (!m_pxml->initialize1())
      throw simple_exception(this, "failed to construct base_system");

   if (!m_pxml->initialize())
      throw simple_exception(this, "failed to construct base_system");

   
   m_compress.set_app(this);


}


void base_system::construct()
{

   ::base_application::construct();




}
base_factory & base_system::factory()
{
   return *m_pfactory;
}


::exception::engine & base_system::eengine()
{

   static ::exception::engine s_eengine(NULL);

   return s_eengine;

}


bool base_system::process_initialize()
{

   m_pfactory->cloneable_large < create_context > ();
   m_pfactory->cloneable_large < application_bias > ();
   m_pfactory->cloneable_large < command_line > ();
   m_pfactory->cloneable_large < manual_reset_event > ();
   m_pfactory->cloneable_large < mutex > ();
   m_pfactory->cloneable_large < event > ();

   if (!base_application::process_initialize())
      return false;
   
   m_spos.create(allocer());

   m_spfile.create(allocer());

   m_spdir.create(allocer());

   if (!m_spdir->initialize())
      return false;

   m_spcrypto.create(allocer());

   if (!m_spcrypto.is_set())
      return false;

   return true;

}




bool base_system::initialize_instance()
{

   m_pfactory->enable_simple_factory_request();

   if (!::base_application::initialize_instance())
      return false;

   return true;

}


int32_t base_system::exit_instance()
{

   base_application::exit_instance();

#ifdef WINDOWS

   m_pdevicecontext = nullptr;

   m_pmutexDc.release();

#endif

   return 0;

}


UINT base_system::os_post_to_all_threads(UINT uiMessage, WPARAM wparam, lparam lparam)
{

   throw interface_only_exception(this);

   return -1;

}

sp(element) base_system::clone()
{
   // by the time, it is not possible to clone a base_system
   return NULL;
}

sp(element) base_system::clone(sp(element) pobj)
{
   return System.factory().base_clone(pobj);
}


void base_system::discard_to_factory(sp(element) pca)
{

   if(m_pfactory == NULL)
      return;

   m_pfactory->discard(pca);

}



void base_system::wait_twf()
{

}

bool base_system::is_system()
{

   return true;

}









bool base_system::assert_failed_line(const char * lpszFileName, int32_t iLine)
{
   UNREFERENCED_PARAMETER(lpszFileName);
   UNREFERENCED_PARAMETER(iLine);
   return false;
}


bool base_system::on_assert_failed_line(const char * lpszFileName, int32_t iLine)
{
   UNREFERENCED_PARAMETER(lpszFileName);
   UNREFERENCED_PARAMETER(iLine);
   return true;
}




sp(element) base_system::on_alloc(sp(base_application) papp, sp(type) info)
{
   /*string str;
   str.Format("Could not alloc %s", info.name());
   simple_message_box(str);*/
   sp(element) pobj = m_pfactory->create(papp, info);
   if(pobj != NULL)
      return pobj;
   on_allocation_error(papp, info);
   return NULL;
}

sp(element) base_system::alloc(sp(base_application) papp, sp(type) info)
{
   return on_alloc(papp, info);
}

sp(element) base_system::alloc(sp(base_application) papp, const std_type_info & info)
{
   return on_alloc(papp, canew(type(info)));
}

void base_system::on_allocation_error(sp(base_application) papp, sp(type) info)
{
   UNREFERENCED_PARAMETER(papp);
   UNREFERENCED_PARAMETER(info);
}

sp(element) base_system::alloc(sp(base_application) papp, const class id & idType)
{
   return on_alloc(papp, get_type_info(idType));
}


sp(type) base_system::get_type_info(const ::std_type_info & info)
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


::xml::departament & base_system::xml()
{
   return *m_pxml;
}



class ::str::base64 & base_system::base64()
{

   return m_base64;

}





::sockets::net & base_system::net()
{
   return m_net;
}



class ::crypto::crypto & base_system::crypto()
{
   return *m_spcrypto;
}



::datetime::departament & base_system::datetime()
{
   return *m_pdatetime;
}



sp(::user::window_draw) base_system::get_twf()
{

   return m_ptwf;

}

::core::log & base_system::log()
{
   return *m_plog;
}




::fontopus::user_set & base_system::userset()
{
   return m_userset;
}



::core::compress & base_system::compress()
{
   return m_compress;
}



machine_event_central & base_system::machine_event_central()
{
   return *m_pmachineeventcentral;
}


::user::str & base_system::str()
{

   return *m_puserstr;

}


sp(::user::object) base_system::place_hold(sp(::user::interaction) pui)
{


   //if(m_pcubeInterface != NULL)
   //{
     // return m_pcubeInterface->hold(pui);
   //}

   return NULL;

}


sp(::base_session) base_system::query_session(index iEdge)
{

   return NULL;

}


::core::os & base_system::os()
{

   return *m_spos;

}




bool base_system::initialize_log(const char * pszId)
{
   if (m_plog != NULL)
      return true;
   m_plog = new ::core::log(this);
   m_plog->set_extended_log();
   m_plog->set_app(this);
   if (!m_plog->initialize(pszId))
   {
      m_plog.release();
      return false;
   }
   //      ::core::trace_v = &::core::system_log_trace_v;
   return true;
}


application_ptra & base_system::appptra()
{
   return m_appptra;
}




void base_system::appa_load_string_table()
{

   retry_single_lock rsl(&m_mutex, millis(84), millis(84));

   for (int32_t i = 0; i < appptra().get_size(); i++)
   {
      sp(base_application) papp = appptra()(i);
      papp->load_string_table();
   }

}

void base_system::appa_set_locale(const char * pszLocale, ::action::context actioncontext)
{

   retry_single_lock rsl(&m_mutex, millis(84), millis(84));

   for (int32_t i = 0; i < appptra().get_size(); i++)
   {
      sp(base_application) papp = appptra()(i);
      papp->set_locale(pszLocale, actioncontext);
   }

}

void base_system::appa_set_schema(const char * pszStyle, ::action::context actioncontext)
{

   retry_single_lock rsl(&m_mutex, millis(84), millis(84));

   for (int32_t i = 0; i < appptra().get_size(); i++)
   {
      sp(base_application) papp = appptra()(i);
      papp->set_schema(pszStyle, actioncontext);
   }

}



bool base_system::assert_running_global(const char * pszAppName, const char * pszId)
{
   if (string(pszId).has_char())
   {
      //         HANDLE h = ::OpenMutex(SYNCHRONIZE, FALSE, get_global_id_mutex_name(pszAppName, pszId));
      ::mutex * pmutex = mutex::open_mutex(this, get_global_id_mutex_name(pszAppName, pszId));
      if (pmutex == NULL)
      {

         string strApp = pszAppName;
         strApp += "app.exe";

         string strParameters;
         strParameters = ": global_mutex_id=\"" + string(pszId) + "\"";

#if defined(WINDOWSEX) || defined(LINUX) || defined(MACOS)

         simple_shell_launcher launcher(NULL, NULL, dir().path(get_module_folder(), strApp), strParameters, NULL, SW_SHOW);

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
      ::mutex * pmutex = mutex::open_mutex(this, get_global_mutex_name(pszAppName));
      if (pmutex == NULL)
      {
         string strApp = pszAppName;
         strApp += "app.exe";

#ifdef METROWIN

         throw todo(get_app());

#else

         simple_shell_launcher launcher(NULL, NULL, dir().path(get_module_folder(), strApp), NULL, NULL, SW_SHOW);

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

bool base_system::assert_running_local(const char * pszAppName, const char * pszId)
{
   string strAppName(pszAppName);
   string strId(pszId);
   if (strId.has_char())
   {
      //HANDLE h = ::OpenMutex(SYNCHRONIZE, FALSE, get_local_id_mutex_name(pszAppName, strId));
      ::mutex * pmutex = mutex::open_mutex(this, get_local_id_mutex_name(pszAppName, strId));
      if (pmutex == NULL)
      {
         string strApp;
         strApp = "app.exe";
         string strParameters;
         strParameters = ": app=" + strAppName + " local_mutex_id=\"" + strId + "\"";

#ifdef METROWIN

         throw todo(get_app());

#else

         simple_shell_launcher launcher(NULL, NULL, dir().path(get_ca2_module_folder(), strApp), strParameters, NULL, SW_SHOW);

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
      ::mutex * pmutex = mutex::open_mutex(this, get_local_mutex_name(pszAppName));
      if (pmutex == NULL)
      {
         string strApp;
         strApp = "app.exe";
         string strParameters;
         strParameters = ": app=" + strAppName;

#ifdef METROWIN

         throw todo(get_app());

#else

         simple_shell_launcher launcher(NULL, NULL, dir().path(get_ca2_module_folder(), strApp), strParameters, NULL, SW_SHOW);

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



uint32_t _thread_proc_start_system(void * p)
{

   base_system * psystem = (base_system *)p;

   return psystem->main();

}

void __start_system(base_system * psystem)
{

   ::create_thread(NULL, 0, &_thread_proc_start_system, (LPVOID)psystem, 0, 0);

}


