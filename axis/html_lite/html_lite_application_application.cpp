#include "framework.h"


namespace html_lite
{


   application_interface::application_interface()
   {

      m_pauraapp->m_psignal->connect(this,&application_interface::on_application_signal);

   }


   application_interface::~application_interface()
   {


   }


   void application_interface::construct(const char * pszAppId)
   {

      //::core::application::construct(pszAppId);

      //::base::application::construct(pszAppId);

   }




   bool application_interface::is_system()
   {

      return false;

   }

   void application_interface::on_application_signal(signal_details * pobj)
   {

      SCAST_PTR(::aura::application_signal_details,psignal,pobj);

      if(psignal->m_esignal == ::aura::application_signal_process_initialize)
      {

         m_pauraapp->m_paurasystem->m_phtml = create_html();

         if(m_pauraapp->m_paurasystem->m_phtml == NULL)
         {
            psignal->m_bOk = false;
            psignal->m_bRet = true;
            return;
         }

         m_pauraapp->m_paurasystem->m_phtml->add_ref();


         m_pauraapp->m_paurasystem->m_phtml->construct(m_pauraapp);

      }
      else if(psignal->m_esignal == ::aura::application_signal_initialize1)
      {

         if(!m_pauraapp->m_paurasystem->m_phtml->initialize())
         {
            psignal->m_bOk = false;
            psignal->m_bRet = true;
            return;
         }

      }
      else  if(psignal->m_esignal == ::aura::application_signal_exit_instance)
      {

      }


   }


   ::html::html * application_interface::create_html()
   {

      return canew(::html::html(m_pauraapp));

   }



} // namespace html_lite





//uint32_t _thread_proc_start_core_system_main(void * p);



//uint32_t _thread_proc_start_core_system_main(void * p)
//{
//
//   ::base::applicationce * psystem = (::base::application_interface *)p;
//
//   ::core::application_interface * pplanesystem = dynamic_cast < ::core::application_interface * > (psystem);
//
//   ::set_thread(psystem);
//
//   return pplanesystem->::core::application_interface::main();
//
//}
//

//CLASS_DECL_HTML void __start_core_system_main(::base::application_interface * psystem)
//{
//
//   ::create_thread(NULL,0,&_thread_proc_start_core_system_main,(LPVOID)psystem,0,0);
//
//}
