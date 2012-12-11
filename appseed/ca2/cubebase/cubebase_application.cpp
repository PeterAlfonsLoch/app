#include "framework.h"


namespace cubebase
{


   application::application()
   {
   }

   application::~application()
   {
   }

   ::ca::application * application::get_system()
   {
      return new application();
   }


typedef  void (* PFN_ca2_factory_exchange)(::ca::application * papp);

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

   #else

      throw todo(this);

      //return NULL; // not implemented... yet!! you may start!!

   #endif

   }


   bool application::initialize1()
   {




      if(is_cube())
      {

         CubeOnFactoryExchange();

         ::ca::smart_pointer < ::cubebase::application >::create(this);

         if(::ca::smart_pointer < ::cubebase::application >::is_null())
            return false;

      }




      if(!::plane::application::initialize1())
         return false;

      if(m_psystem == NULL)
         return false;

      if(m_psession == NULL)
         return false;

      if(m_psystem->m_pcube == NULL && !is_cube())
      {

         ::ca::application * papp            = System.create_application("application", "cube", true, NULL);
         if(papp == NULL)
            return false;

         ::cube::cube * pcube                = dynamic_cast < ::cube::cube * > (papp);
         if(pcube == NULL)
         {
            delete papp;
            return NULL;
         }

         pcube->m_psystem                    = m_psystem;
         pcube->m_psession                   = m_psession;
         m_psystem->m_pcube                  = pcube;
         m_psystem->m_pcubeInterface         = pcube;

         //pcube->directrix().consolidate(&m_psystem->directrix());

         //if(!pcube->start_application(true, NULL))
         //   return false;

      }

      if(m_psession->m_pbergedge == NULL && !is_cube() && !is_bergedge())
      {

         ::ca::application * papp            = System.create_application("application", "bergedge", true, NULL);
         if(papp == NULL)
            return false;

         ::bergedge::bergedge * pbergedge    = dynamic_cast < ::bergedge::bergedge * > (papp);
         if(pbergedge == NULL)
         {
            delete papp;
            return NULL;
         }

         pbergedge->m_psystem                = m_psystem;
         pbergedge->m_psession               = m_psession;
         m_psession->m_pbergedge             = pbergedge;
         m_psession->m_pbergedgeInterface    = pbergedge;

         //if(!pbergedge->start_application(true, NULL))
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


   ex1::filesp application::friendly_get_file(var varFile, UINT nOpenFlags)
   {

      try
      {

         return get_file(varFile, nOpenFlags);

      }
      catch(::ex1::file_exception & e)
      {

         string strMessage = e.get_message();

         App(this).simple_message_box(NULL, strMessage, MB_OK);

         return ::ca::null();

      }

   }


} //namespace cube



