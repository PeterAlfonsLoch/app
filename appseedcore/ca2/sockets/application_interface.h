#pragma once

namespace sockets
{

   class CLASS_DECL_ca application_interface :
      virtual public ::ca::application_interface
   {
   public:


      ssl_client_context_map                       m_clientcontextmap;
      AjpBaseSocket::Initializer *                 m_pajpbasesocketinit;

      count                                        m_countHttpPostBoundary;
      mutex                                        m_mutexHttpPostBoundary;

      resolv_socket::cache_t                       m_resolvcache;
      resolv_socket::timeout_t                     m_resolvtimeout;
      mutex                                        m_mutexResolvCache;

      
      application_interface();


      void on_application_signal(::radix::application_signal_object * papplicationsignal);
      virtual void http_config_proxy(const char * pszUrl, http_tunnel * psocket);
   };


} // namespace kar