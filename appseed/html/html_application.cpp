#include "framework.h"





namespace html
{


   application::application(::aura::application * papp):
      ::element(papp)
   {

      m_psignal->connect(this,&application::on_application_signal);

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


   void application::on_application_signal(signal_details * pobj)
   {
      
      SCAST_PTR(::aura::application_signal_details,psignal,pobj);

      if(psignal->m_esignal == ::aura::application_signal_process_initialize)
      {
         
         m_pauraapp->m_pcoresystem->m_phtml = create_html();

         m_pauraapp->m_pcoresystem->add_ref();

         if(m_pauraapp->m_pcoresystem->m_phtml == NULL)
         {
            psignal->m_bOk = false;
            psignal->m_bRet = true;
            return;
         }

         m_pauraapp->m_pcoresystem->m_phtml->construct(this);

      }
      else if(psignal->m_esignal == ::aura::application_signal_initialize1)
      {

         System.factory().creatable_small < html_document >();
         System.factory().creatable_small < html_child_frame >();
         System.factory().creatable_small < html_frame >();
         System.factory().creatable_small < html_view >();

         
         if(!m_pauraapp->m_pcoresystem->m_phtml->initialize())
         {
            psignal->m_bOk = false;
            psignal->m_bRet = true;
            return;
         }

         Platform.userex()->m_ptemplateForm = new ::user::multiple_document_template(
            get_app(),
            "system/form",
            System.type_info < html_document >(),
            System.type_info < html_frame >(),
            System.type_info < html_view >());

         Platform.userex()->m_ptemplateChildForm = new ::user::multiple_document_template(
            get_app(),
            "system/form",
            System.type_info < html_document >(),
            System.type_info < html_child_frame >(),
            System.type_info < html_view >());

         Platform.userex()->m_ptemplatePlaceHolder = new ::user::multiple_document_template(
            get_app(),
            "system/form",
            System.type_info < simple_document >(),
            System.type_info < simple_frame_window >(),
            System.type_info < ::user::place_holder >());



      }
      else  if(psignal->m_esignal == ::aura::application_signal_exit_instance)
      {
      }
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
