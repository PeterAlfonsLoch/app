#pragma once

namespace sockets
{

   class CLASS_DECL_ca application_interface :
      virtual public ::ca::application_interface
   {
   public:


      ::collection::string_map < SSL_CTX * > *     m_pclient_contexts;
      AjpBaseSocket::Initializer *                 m_pajpbasesocketinit;

      count                                        m_countHttpPostBoundary;
      mutex                                        m_mutexHttpPostBoundary;

      resolv_socket::cache_t                       m_resolvcache;
      resolv_socket::timeout_t                     m_resolvtimeout;
      mutex                                        m_mutexResolvCache;



      void on_application_signal(::ca::application::signal_object * papplicationsignal);
      virtual void http_config_proxy(const char * pszUrl, http_tunnel * psocket);
   };


} // namespace kar