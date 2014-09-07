#include "framework.h" // from "base/net/net_sockets.h"


namespace sockets
{


   listen_socket_base::listen_socket_base(base_socket_handler & h) : 
      element(h.get_app()), 
      base_socket(h),
      socket(h), 
      m_depth(0),
      m_bDetach(false)
   {

   }

   listen_socket_base::listen_socket_base(const listen_socket_base& s) : 
      element(s.get_app()), 
      base_socket(s),
      socket(s)
   {

   }

   listen_socket_base::~listen_socket_base() 
   {
   }

   /** close file descriptor. */
   void listen_socket_base::close()
   {

      if (GetSocket() != INVALID_SOCKET)
      {

         close_socket(GetSocket());

      }

   }

   /** Bind and listen to any interface.
   \param port Port (0 is random)
   \param depth Listen queue depth */
   int32_t listen_socket_base::Bind(port_t port,int32_t depth) 
   {
      if (IsIpv6())
      {
         ::net::address ad(AF_INET6, port);
         return Bind(ad, depth);
      }
      else
      {
         ::net::address ad(AF_INET, port);
         return Bind(ad, depth);
      }
   }

   int32_t listen_socket_base::Bind(const ::net::address & ad,int32_t depth)
   {
#ifdef USE_SCTP
      if (dynamic_cast<SctpSocket *>(m_creator))
      {
         return Bind(ad, "sctp", depth);
      }
#endif
      return Bind(ad, "tcp", depth);
   }

   /** Bind and listen to any interface, with optional protocol.
   \param port Port (0 is random)
   \param protocol Network protocol
   \param depth Listen queue depth */
   int32_t listen_socket_base::Bind(port_t port,const string & protocol,int32_t depth)
   {
      if (IsIpv6())
      {
         ::net::address ad(AF_INET6, port);
         return Bind(ad.u.m_addr6.sin6_addr, port, protocol, depth);
      }
      else
      {
         ::net::address ad(AF_INET, port);
         return Bind(ad.u.m_addr.sin_addr, port, protocol, depth);
      }
   }

   /** Bind and listen to specific interface.
   \param intf Interface hostname
   \param port Port (0 is random)
   \param depth Listen queue depth */
   int32_t listen_socket_base::Bind(const string & intf,port_t port,int32_t depth)
   {
      ::net::address ad(intf, port);
      if (ad.is_valid())
      {
         return Bind(ad, depth);
      }
      log("Bind", 0, "name resolution of interface name failed", ::aura::log::level_fatal);
      return -1;
   }

   /** Bind and listen to specific interface.
   \param intf Interface hostname
   \param port Port (0 is random)
   \param protocol Network protocol
   \param depth Listen queue depth */
   int32_t listen_socket_base::Bind(const string & intf,port_t port,const string & protocol,int32_t depth)
   {
      ::net::address ad(intf, port);
      if (ad.is_valid())
      {
         return Bind(ad, protocol, depth);
      }
      log("Bind", 0, "name resolution of interface name failed", ::aura::log::level_fatal);
      return -1;
   }

   /** Bind and listen to ipv4 interface.
   \param a Ipv4 interface address
   \param port Port (0 is random)
   \param depth Listen queue depth */
   int32_t listen_socket_base::Bind(in_addr a,port_t port,int32_t depth)
   {
      ::net::address ad(a, port);
#ifdef USE_SCTP
      if (dynamic_cast<SctpSocket *>(m_creator))
      {
         return Bind(ad, "sctp", depth);
      }
#endif
      return Bind(ad, "tcp", depth);
   }
   /** Bind and listen to ipv4 interface.
   \param a Ipv4 interface address
   \param port Port (0 is random)
   \param protocol Network protocol
   \param depth Listen queue depth */
   int32_t listen_socket_base::Bind(in_addr a,port_t port,const string & protocol,int32_t depth)
   {
      ::net::address ad(a, port);
      return Bind(ad, protocol, depth);
   }

   /** Bind and listen to ipv6 interface.
   \param a Ipv6 interface address
   \param port Port (0 is random)
   \param depth Listen queue depth */
   int32_t listen_socket_base::Bind(in6_addr a,port_t port,int32_t depth) 
   {
      ::net::address ad(a, port);
#ifdef USE_SCTP
      if (dynamic_cast<SctpSocket *>(m_creator))
      {
         return Bind(ad, "sctp", depth);
      }
#endif
      return Bind(ad, "tcp", depth);
   }
   /** Bind and listen to ipv6 interface.
   \param a Ipv6 interface address
   \param port Port (0 is random)
   \param protocol Network protocol
   \param depth Listen queue depth */
   int32_t listen_socket_base::Bind(in6_addr a,port_t port,const string & protocol,int32_t depth)
   {
      ::net::address ad(a, port);
      return Bind(ad, protocol, depth);
   }

   /** Bind and listen to network interface.
   \param ad Interface address
   \param protocol Network protocol
   \param depth Listen queue depth */
   int32_t listen_socket_base::Bind(const ::net::address & ad,const string & protocol,int32_t depth)
   {

      SOCKET s;
      m_iBindPort = ad.get_service_number();
      if ( (s = CreateSocket(ad.get_family(), SOCK_STREAM, protocol)) == INVALID_SOCKET)
      {
         return -1;
      }
      if (bind(s, ad.sa(), ad.sa_len()) == -1)
      {
         log("bind() failed for port " + ::str::from(ad.get_service_number()), Errno, StrError(Errno), ::aura::log::level_fatal);
         close_socket(s);
         return -1;
      }
      if (listen(s, depth) == -1)
      {
         log("listen", Errno, StrError(Errno), ::aura::log::level_fatal);
         close_socket(s);
         throw simple_exception(get_app(), "listen() failed for port " + ::str::from(ad.get_service_number()) + ": " + StrError(Errno));
         return -1;
      }
      m_depth = depth;
      attach(s);
      return 0;
   }

   /** Return assigned port number. */
   //         port_t GetPort()
   //       {
   //        return GetSockPort();
   //   }

   /** Return listen queue depth. */
   int32_t listen_socket_base::GetDepth()
   {
      return m_depth;
   }

   /** OnRead on a listen_socket_base receives an incoming connection. */
   void listen_socket_base::OnRead()
   {

      struct sockaddr sa;
      socklen_t sa_len = sizeof(struct sockaddr);
      SOCKET a_s = accept(GetSocket(), &sa, &sa_len);

      if (a_s == INVALID_SOCKET)
      {
         log("accept", Errno, StrError(Errno), ::aura::log::level_error);
         return;
      }
      if (!Handler().OkToAccept(this))
      {
         log("accept", -1, "Not OK to accept", ::aura::log::level_warning);
         close_socket(a_s);
         return;
      }
      if (Handler().get_count() >= FD_SETSIZE)
      {
         log("accept", (int32_t)Handler().get_count(), "base_socket_handler fd_set limit reached", ::aura::log::level_fatal);
         close_socket(a_s);
         return;
      }
      sp(socket) tmp = create_listen_socket();
      tmp->m_strCat = m_strCat;
      tmp -> EnableSSL(IsSSL()); // SSL Enabled socket
      tmp -> SetIpv6( IsIpv6() );
      tmp -> set_parent(this);
      tmp -> attach(a_s);
      tmp -> SetNonblocking(true);
      tmp->SetRemoteHostname(::net::address(sa));
      tmp->m_iBindPort = m_iBindPort;
      tmp -> SetConnected(true);
      tmp -> Init();
      tmp -> SetDeleteByHandler(true);
      Handler().add(tmp);
      if(m_bDetach)
      {
         tmp->detach();
      }
      if (tmp -> IsSSL()) // SSL Enabled socket
      {
         // %! OnSSLAccept calls SSLNegotiate that can finish in this one call.
         // %! If that happens and negotiation fails, the 'tmp' instance is
         // %! still added to the list of active sockets in the sockethandler.
         // %! See bugfix for this in socket_handler::Select - don't set rwx
         // %! flags if CloseAndDelete() flag is true.
         // %! An even better fugbix (see tcp_socket::OnSSLAccept) now avoids
         // %! the add problem altogether, so ignore the above.
         // %! (OnSSLAccept does no longer call SSLNegotiate().)
         tmp -> OnSSLAccept();
      }
      else
      {
         tmp -> OnAccept();
      }


   }

   /** Please don't use this method.
   "accept()" is handled automatically in the OnRead() method. */
   SOCKET listen_socket_base::Accept(SOCKET socket, struct sockaddr *saptr, socklen_t *lenptr)
   {
      return accept(socket, saptr, lenptr);
   }

   bool listen_socket_base:: HasCreator()
   { 
      return false; 
   }

   void listen_socket_base::OnOptions(int32_t,int32_t,int32_t,SOCKET)
   {
      SetSoReuseaddr(true);
   }

   listen_socket_base& listen_socket_base::operator=(const listen_socket_base& )
   { 

      return *this; 

   }

   sp(socket) listen_socket_base::create_listen_socket()
   {
      return NULL;
   }


} // namespace sockets





