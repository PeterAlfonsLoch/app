#pragma once


   namespace sockets
   {


      class CLASS_DECL_BASE sockets :
         virtual public ::aura::departament
      {
      public:



#if defined(BSD_STYLE_SOCKETS)
         ssl_client_context_map                       m_clientcontextmap;
#endif
         AjpBaseSocket::Initializer *                 m_pajpbasesocketinit;

         ::count m_countHttpPostBoundary;
         mutex                                        m_mutexHttpPostBoundary;

         resolv_socket::cache_t                       m_resolvcache;
         resolv_socket::timeout_t                     m_resolvtimeout;
         mutex                                        m_mutexResolvCache;



         sockets(::aura::application * papp);
         virtual ~sockets();


         bool initialize1();

         bool finalize();

      };


   } // namespace sockets


