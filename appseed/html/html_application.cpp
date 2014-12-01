#include "framework.h"





namespace html
{


   application::application(::aura::application * papp):
      ::element(papp)
   {


      }


   application::~application()
   {

   }



   void application::construct(const char * pszAppId)
   {

      ::core::application::construct(pszAppId);

      ::base::application::construct(pszAppId);

   }




   bool application::is_system()
   {

      return false;

   }

   bool application::initialize2()
   {

      if(!::core::application::initialize2())
         return false;

      if(!::base::application::initialize2())
         return false;

      return true;

   }


   bool application::InitApplication()
   {


      if(!::core::application::InitApplication())
         return false;

      return true;
   }


   bool application::process_initialize()
   {

      if(!::core::application::process_initialize())
         return false;

      m_pauraapp->m_pcoresystem->m_phtml = create_html();

      m_pauraapp->m_pcoresystem->add_ref();

      if(m_pauraapp->m_pcoresystem->m_phtml == NULL)
         return false;

      m_pauraapp->m_pcoresystem->m_phtml->construct(this);

      return true;

   }


   bool application::initialize()
   {

      if(!::core::application::initialize())
         return false;

      return true;
   }



   bool application::initialize1()
   {




      if(!::core::application::initialize1())
         return false;


      if(!m_pauraapp->m_pcoresystem->m_phtml->initialize())
         return false;



      return true;

   }




   bool application::initialize3()
   {

      if(!::core::application::initialize3())
         return false;

      return true;

   }


   bool application::initialize_instance()
   {

      if(!::core::application::initialize_instance())
      {
         return false;
      }

      return true;

   }


   bool application::bergedge_start()
   {
      return true;
   }


   int32_t application::exit_instance()
   {


      int32_t iRet = m_iReturnCode;


      try
      {

         iRet = ::core::application::exit_instance();

      }
      catch(...)
      {

      }



      return iRet;
   }




   bool application::finalize()
   {

      bool bOk = true;

      if(!::core::application::finalize())
      {

         bOk = false;

      }

      return bOk;

   }




   void application::assert_valid() const
   {

     ::core:: application::assert_valid();
      //::database::server::assert_valid();

   }


   void application::dump(dump_context & context) const
   {

      ::core::application::dump(context);
      //::database::server::dump(context);

   }




   ::html::html * application::create_html()
   {

      return canew(::html::html(this));

   }



} // namespace html





uint32_t _thread_proc_start_core_system_main(void * p);



uint32_t _thread_proc_start_core_system_main(void * p)
{

   ::base::application * psystem = (::base::application *)p;

   ::core::application * pplanesystem = dynamic_cast < ::core::application * > (psystem);

   ::set_thread(psystem);

   return pplanesystem->::core::application::main();

}


CLASS_DECL_HTML void __start_core_system_main(::base::application * psystem)
{

   ::create_thread(NULL,0,&_thread_proc_start_core_system_main,(LPVOID)psystem,0,0);

}
