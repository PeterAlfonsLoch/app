#include "StdAfx.h"

namespace sockets
{

   void application_interface::on_application_signal(::ca::application::signal_object * papplicationsignal)
   {
      if(papplicationsignal->m_esignal == ::ca::application::signal_initialize1)
      {
         System.factory().creatable_small < ::http::memory_file > ();
         System.factory().cloneable_small < ::sockets::ipv4_address > ();
         System.factory().cloneable_small < ::sockets::ipv6_address > ();

         if(App(this).is_system())
         {
            m_pajpbasesocketinit = new AjpBaseSocket::Initializer;
            m_pclient_contexts   = new ::collection::string_map < SSL_CTX * >;
         }

         m_countHttpPostBoundary = 0;
      }
      else if(papplicationsignal->m_esignal == ::ca::application::signal_finalize)
      {
         if(Application.is_system())
         {
            if(m_pclient_contexts != NULL)
            {
               delete m_pclient_contexts;
               m_pclient_contexts = NULL;
            }
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
      throw not_implemented_exception();
   }

} // namespace kar