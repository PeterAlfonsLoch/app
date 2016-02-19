#pragma once


namespace sockets
{


   class CLASS_DECL_AXIS sockets :
      virtual public ::aura::department
   {
   public:

      int32_t                                      m_iReturnCode;
#ifdef HAVE_OPENSSL
      ssl_client_context_map                       m_clientcontextmap;
#endif

      AjpBaseSocket::Initializer *                 m_pajpbasesocketinit;

      count                                        m_countHttpPostBoundary;
      mutex                                        m_mutexHttpPostBoundary;

      resolv_socket::cache_t                       m_resolvcache;
      resolv_socket::timeout_t                     m_resolvtimeout;
      mutex                                        m_mutexResolvCache;

      sp(::sockets::net)                           m_spnet;


      sockets(::aura::application * papp);


      bool initialize1();
      bool finalize();


      virtual void http_config_proxy(const char * pszUrl, http_tunnel * psocket);


      class ::sockets::net & net();

   };


} // namespace sockets



