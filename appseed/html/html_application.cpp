#include "framework.h"


namespace html
{


   application::application()
   {

      m_pauraapp->m_psignal->connect(this,&application::on_application_signal);

   }


   application::~application()
   {

   }


   void application::on_application_signal(signal_details * pobj)
   {
      
      SCAST_PTR(::aura::application_signal_details,psignal,pobj);

      if(psignal->m_esignal == ::aura::application_signal_process_initialize)
      {
         
      }
      else if(psignal->m_esignal == ::aura::application_signal_initialize1)
      {

         System.factory().creatable_small < html_document >();
         System.factory().creatable_small < html_view >();
         System.factory().creatable_small < ::html::data::image >();
         System.factory().creatable_small < ::html::data >();

         Application.set_form_impact_system(

            new ::user::multiple_document_template(
               get_app(),
               "system/form",
               System.type_info < html_document >(),
               System.get_simple_frame_window_type_info(),
               System.type_info < html_view >()),

            new ::user::multiple_document_template(
               get_app(),
               "system/form",
               System.type_info < html_document >(),
               System.get_simple_child_frame_type_info(),
               System.type_info < html_view >()),

            new ::user::multiple_document_template(
               get_app(),
               "system/form",
               System.type_info < ::user::document >(),
               System.get_simple_frame_window_type_info(),
               System.type_info < ::user::place_holder >())
               
               );



      }
      else  if(psignal->m_esignal == ::aura::application_signal_exit_instance)
      {

      }

   }


} // namespace html








































