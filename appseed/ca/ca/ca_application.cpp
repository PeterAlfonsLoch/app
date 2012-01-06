#include "StdAfx.h"


namespace ca
{


   application::application()
   {

      set_app(this);

      m_bInitializeProDevianMode = true;

      // almost always forgotten, assumed, as exception, responsability of application to add first ref on constructor.
      gen::add_ref(this);

      //_setmbcp(CP_UTF8);
//      DWORD dw = ::_getmbcp();
      srand(::GetTickCount());

      m_pinitmaindata   = NULL;
      m_bService        = false;

      m_bZipIsDir       = true;

   }


   application::~application()
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


   int application::exit()
   {
      return 0;
   }

   int application::exit_instance()
   {
      return 0;
   }

   bool application::is_system()
   {
      return false;
   }

   bool application::is_bergedge()
   {
      return false;
   }

   bool application::init_main_data(main_init_data * pdata)
   {
      m_pinitmaindata = pdata;
      return true;
   }

   bool application::set_main_init_data(main_init_data * pdata)
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

   bool application::process_initialize()
   {
      return true;
   }

   bool application::initialize1()
   {
      return true;
   }

   bool application::initialize2()
   {
      return true;
   }

   bool application::initialize3()
   {
      return true;
   }

   bool application::initialize()
   {
      return true;
   }

   bool application::finalize()
   {
      return true;
   }


} // namespace ca


