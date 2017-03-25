#pragma once


   namespace sockets
   {


      class CLASS_DECL_AURA sockets :
         virtual public ::aura::department
      {
      public:


         int32_t                                      m_iReturnCode;

         SSLInitializer *                             m_psslinit;

         byte                                         m_baTicketKey[SSL_SESSION_TICKET_KEY_SIZE];

#if defined(BSD_STYLE_SOCKETS)
         mutex                                        m_mutexClientContextMap;
         ssl_client_context_map                       m_clientcontextmap;
//         ssl_server_context_map                       m_servercontextmap;
#endif
         AjpBaseSocket::Initializer *                 m_pajpaxissocketinit;

         ::count m_countHttpPostBoundary;
         mutex                                        m_mutexHttpPostBoundary;

         resolv_socket::cache_t                       m_resolvcache;
         resolv_socket::timeout_t                     m_resolvtimeout;
         mutex                                        m_mutexResolvCache;
         sp(::sockets::net)                           m_spnet;
         ::net::port_forward_sp                       m_spportforward;

         mutex                                        m_mutexPool;
         socket_map                                   m_pool; ///< Active sockets map


         sockets(::aura::application * papp);
         virtual ~sockets();

         class ::sockets::net                         & net();

         bool initialize1();

         bool finalize();

      };


   } // namespace sockets


