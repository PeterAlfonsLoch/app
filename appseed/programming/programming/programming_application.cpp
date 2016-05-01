#include "framework.h"


namespace programming
{


   application::application() :
      m_semCompiler(this, MAX(1, ::get_processor_count()), MAX(1, ::get_processor_count()))
   {

      m_pauraapp->m_psignal->connect(this, &application::on_application_signal);

   }


   application::~application()
   {

   }


   void application::on_application_signal(signal_details * pobj)
   {

      SCAST_PTR(::aura::application_signal_details, psignal, pobj);

      if (psignal->m_esignal == ::aura::application_signal_process_initialize)
      {

      }
      else if (psignal->m_esignal == ::aura::application_signal_initialize1)
      {



      }
      else  if (psignal->m_esignal == ::aura::application_signal_exit_instance)
      {

      }

   }


   void application::on_request(sp(::create) pcreatecontext)
   {


      if (pcreatecontext->m_spCommandLine->m_varQuery.has_property("introj"))
      {

         ::introjection::compiler *  pcompiler = canew(::introjection::compiler(this));
         
         bool bNew;

         ::aura::library & lib = pcompiler->compile(::dir::system() / "config\\xmpp_resident\\room\\ca2@livecoding.tv\\xmpp_bot.cpp", bNew);

         if (lib.m_pca2library == NULL)
         {

            return;

         }

         sp(object) p = lib.create_object(get_app(), "plugin", this);

         if (p.is_null())
            return;

///         m_p = p.cast < plugin >();

      }



   }


} // namespace programming


#ifdef MACOS
int get_processor_count()
{
   return 1;
}
#endif





































