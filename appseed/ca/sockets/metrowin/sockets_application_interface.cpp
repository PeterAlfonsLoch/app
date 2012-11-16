#include "framework.h"


namespace sockets
{


   application_interface::application_interface() :
      m_mutexHttpPostBoundary(get_app()),
      m_mutexResolvCache(get_app())
   {

      m_pajpbasesocketinit    = NULL;

   }


   void application_interface::on_application_signal(::radix::application_signal_object * papplicationsignal)
   {
      if(papplicationsignal->m_esignal == ::ca::application_signal_initialize1)
      {

         if(App(dynamic_cast < ::ca::application * >(this)).is_system())
         {

            ::sockets::SSLInitializer ssl_init(m_psystem);

            System.factory().creatable_small < ::http::memory_file > ();
            System.factory().cloneable_small < ::sockets::ipv4_address > ();
            System.factory().cloneable_small < ::sockets::ipv6_address > ();

            m_pajpbasesocketinit = new AjpBaseSocket::Initializer;
         }

         m_countHttpPostBoundary = 0;
      }
      else if(papplicationsignal->m_esignal == ::ca::application_signal_finalize)
      {
         if(Application.is_system())
         {
            if(m_pajpbasesocketinit != NULL)
            {
               delete m_pajpbasesocketinit;
               m_pajpbasesocketinit = NULL;
            }
         }
      }
   }


   void application_interface::http_config_proxy(const char * pszUrl, http_tunnel * psocket)
   {
      UNREFERENCED_PARAMETER(pszUrl);
      UNREFERENCED_PARAMETER(psocket);
      throw not_implemented(get_app());
   }


} // namespace kar


