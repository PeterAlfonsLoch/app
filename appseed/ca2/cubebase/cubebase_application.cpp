#include "framework.h"

#if defined(LINUX) || defined(MACOS)
#include <dlfcn.h>
#endif



namespace cubebase
{


   application::application()
   {
   }

   application::~application()
   {
   }

   sp(::ca::application) application::get_system()
   {
      return new application();
   }


typedef  void (* PFN_ca2_factory_exchange)(sp(::ca::application) papp);

   void application::CubeOnFactoryExchange()
   {

   #ifdef WINDOWSEX

      HMODULE hmodule = ::LoadLibraryA("os2.dll");
      PFN_ca2_factory_exchange pfn_ca2_factory_exchange = (PFN_ca2_factory_exchange) ::GetProcAddress(hmodule, "ca2_factory_exchange");
      pfn_ca2_factory_exchange(this);

   #elif defined(METROWIN)

      HMODULE hmodule = ::LoadPackagedLibrary(L"os2.dll", 0);
      PFN_ca2_factory_exchange pfn_ca2_factory_exchange = (PFN_ca2_factory_exchange) ::GetProcAddress(hmodule, "ca2_factory_exchange");
      pfn_ca2_factory_exchange(this);

#elif defined(LINUX)

      void * pdl = ::dlopen("libca2os2.so", RTLD_NOW | RTLD_GLOBAL);
      PFN_ca2_factory_exchange pfn_ca2_factory_exchange = (PFN_ca2_factory_exchange) ::dlsym(pdl, "ca2_factory_exchange");
      pfn_ca2_factory_exchange(this);

   #else

      throw todo(this);

      //return ::null(); // not implemented... yet!! you may start!!

   #endif

   }


   bool application::initialize1()
   {




      if(is_cube())
      {

         CubeOnFactoryExchange();

         ::ca::smart_pointer < ::cubebase::application >::create(allocer());

         if(::ca::smart_pointer < ::cubebase::application >::is_null())
            return false;

      }




      if(!::plane::application::initialize1())
         return false;

      if(m_psystem == ::null())
         return false;

      if(m_psession == ::null())
         return false;

      if(m_psystem->m_pcube == ::null() && !is_cube())
      {

         sp(::ca::application) papp            = System.create_application("application", "cube", true, ::null());
         if(papp == ::null())
            return false;

         sp(::cube::cube) pcube                = papp;
         if(pcube == ::null())
         {
            papp.release();
            return false;
         }

         pcube->m_psystem                    = m_psystem;
         pcube->m_psession                   = m_psession;
         m_psystem->m_pcube                  = pcube;
         m_psystem->m_pcubeInterface         = pcube;

         //pcube->directrix()->consolidate(&m_psystem->directrix());

         //if(!pcube->start_application(true, ::null()))
         //   return false;

      }

      if(m_psession->m_pbergedge == ::null() && !is_cube() && !is_bergedge())
      {

         sp(::ca::application) papp            = System.create_application("application", "bergedge", true, ::null());
         if(papp == ::null())
            return false;

         ::bergedge::bergedge * pbergedge    = dynamic_cast < ::bergedge::bergedge * > (papp.m_p);
         if(pbergedge == ::null())
         {
            papp.release();
            return false;
         }

         pbergedge->m_psystem                = m_psystem;
         pbergedge->m_psession               = m_psession;
         m_psession->m_pbergedge             = pbergedge;
         m_psession->m_pbergedgeInterface    = pbergedge;

         //if(!pbergedge->start_application(true, ::null()))
         //   return false;

      }


      return true;

   }

   bool application::initialize()
   {

      if(!::plane::application::initialize())
         return false;


      return true;

   }

   bool application::is_cube()
   {
      return false;
   }


   ::user::printer * application::get_printer(const char * pszDeviceName)
   {

      return ::ca::smart_pointer < ::cubebase::application >::m_p->get_printer(pszDeviceName);

   }


   ::ca::filesp application::friendly_get_file(var varFile, UINT nOpenFlags)
   {

      try
      {

         return m_file.get_file(varFile, nOpenFlags);

      }
      catch(::ca::file_exception & e)
      {

         string strMessage = e.get_message();

         App(this).simple_message_box(::null(), strMessage, MB_OK);

         return ::ca::null();

      }

   }


   ::fontopus::fontopus * application::create_fontopus()
   {

      return new ::ca::fontopus::fontopus();

   }


   ::user::user * application::create_user()
   {

      return new ::ca::user::user();

   }


   ::fs::fs * application::create_fs()
   {

      return new ::ca::fs::fs();

   }


   ::html::html * application::create_html()
   {

      return new ::ca::html::html();

   }


} //namespace cube





