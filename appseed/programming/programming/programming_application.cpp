#include "framework.h"


namespace programming
{


application::application() :
   m_semCompiler(this,MAX(1,::get_processor_count()),MAX(1,::get_processor_count()))
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



   }
   else  if(psignal->m_esignal == ::aura::application_signal_exit_instance)
   {

   }

}


} // namespace programming


#ifdef MACOS
int get_processor_count()
{
   return 1;
}
#endif





































