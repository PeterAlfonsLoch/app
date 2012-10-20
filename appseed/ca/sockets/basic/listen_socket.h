/** \file listen_socket.h
 **   \date  2004-02-13
 **   \author grymse@alhem.net
**/

// xxx ref_Anders_Hedstrom_sockets_library.txt

#pragma once
/*
#ifdef _WIN32
#include <stdlib.h>
#else
#include <errno.h>
#endif
*/


namespace sockets
{


   /** Binds incoming port number to new socket class X.
      \ingroup basic */
   template <class X>
   class listen_socket : public socket
   {
   public:

      bool m_bDetach;

      /** Constructor.
         \param h socket_handler_base reference
         \param use_creator Optional use of creator (default true) */
      listen_socket(socket_handler_base& h,bool use_creator = true) : ::ca::ca(h.get_app()), socket(h), m_depth(0), m_creator(NULL)
      ,m_bHasCreate(false), m_bDetach(false)
      {
         if (use_creator)
         {
            m_creator = new X(h);
            socket *tmp = m_creator -> create();
            if (tmp && dynamic_cast<X *>(tmp))
            {
               m_bHasCreate = true;
            }
            if (tmp)
            {
               delete tmp;
            }
         }
      }
      ~listen_socket() {
         if (m_creator)
         {
            delete m_creator;
         }
      }

      /** close file descriptor. */
      int close() {
         if (GetSocket() != INVALID_SOCKET)
         {
            ::closesocket(GetSocket());
         }
         return 0;
      }

      /** Bind and listen to any interface.
         \param port Port (0 is random)
         \param depth Listen queue depth */
      int Bind(port_t port,int depth = 20) {
         if (IsIpv6())
         {
            ipv6_address ad(get_app(), port);
            return Bind(ad, depth);
         }
         else
         {
            ipv4_address ad(get_app(), port);
            return Bind(ad, depth);
         }
      }

      int Bind(sockets::address& ad,int depth) {
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
      int Bind(port_t port,const string & protocol,int depth = 20) {
         if (IsIpv6())
         {
            ipv6_address ad(get_app(), port);
            return Bind(ad, protocol, depth);
         }
         else
         {
            ipv4_address ad(get_app(), port);
            return Bind(ad, protocol, depth);
         }
      }

      /** Bind and listen to specific interface.
         \param intf Interface hostname
         \param port Port (0 is random)
         \param depth Listen queue depth */
      int Bind(const string & intf,port_t port,int depth = 20)
      {
         if (IsIpv6())
         {
            ipv6_address ad(get_app(), intf, port);
            if (ad.IsValid())
            {
               return Bind(ad, depth);
            }
            Handler().LogError(this, "Bind", 0, "name resolution of interface name failed", ::gen::log::level::fatal);
            return -1;
         }
         else
         {
            ipv4_address ad(get_app(), intf, port);
            if (ad.IsValid())
            {
               return Bind(ad, depth);
            }
            Handler().LogError(this, "Bind", 0, "name resolution of interface name failed", ::gen::log::level::fatal);
            return -1;
         }
      }

      /** Bind and listen to specific interface.
         \param intf Interface hostname
         \param port Port (0 is random)
         \param protocol Network protocol
         \param depth Listen queue depth */
      int Bind(const string & intf,port_t port,const string & protocol,int depth = 20) {
         if (IsIpv6())
         {
            ipv6_address ad(get_app(), intf, port);
            if (ad.IsValid())
            {
               return Bind(ad, protocol, depth);
            }
            Handler().LogError(this, "Bind", 0, "name resolution of interface name failed", ::gen::log::level::fatal);
            return -1;
         }
         else
         {
            ipv4_address ad(get_app(), intf, port);
            if (ad.IsValid())
            {
               return Bind(ad, protocol, depth);
            }
            Handler().LogError(this, "Bind", 0, "name resolution of interface name failed", ::gen::log::level::fatal);
            return -1;
         }
      }

      /** Bind and listen to ipv4 interface.
         \param a Ipv4 interface address
         \param port Port (0 is random)
         \param depth Listen queue depth */
      int Bind(ipaddr_t a,port_t port,int depth = 20) {
         ipv4_address ad(get_app(), a, port);
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
      int Bind(ipaddr_t a,port_t port,const string & protocol,int depth) {
         ipv4_address ad(get_app(), a, port);
         return Bind(ad, protocol, depth);
      }

      /** Bind and listen to ipv6 interface.
         \param a Ipv6 interface address
         \param port Port (0 is random)
         \param depth Listen queue depth */
      int Bind(in6_addr a,port_t port,int depth = 20) {
         ipv6_address ad(get_app(), a, port);
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
      int Bind(in6_addr a,port_t port,const string & protocol,int depth) {
         ipv6_address ad(get_app(), a, port);
         return Bind(ad, protocol, depth);
      }

      /** Bind and listen to network interface.
         \param ad Interface address
         \param protocol Network protocol
         \param depth Listen queue depth */
      int Bind(sockets::address& ad,const string & protocol,int depth) {
         SOCKET s;
         m_iBindPort = ad.GetPort();
         if ( (s = CreateSocket(ad.GetFamily(), SOCK_STREAM, protocol)) == INVALID_SOCKET)
         {
            return -1;
         }
         if (bind(s, ad, ad) == -1)
         {
            Handler().LogError(this, "bind() failed for port " + gen::str::from(ad.GetPort()), Errno, StrError(Errno), ::gen::log::level::fatal);
            ::closesocket(s);
            return -1;
         }
         if (listen(s, depth) == -1)
         {
            Handler().LogError(this, "listen", Errno, StrError(Errno), ::gen::log::level::fatal);
            ::closesocket(s);
            throw simple_exception(get_app(), "listen() failed for port " + gen::str::from(ad.GetPort()) + ": " + StrError(Errno));
            return -1;
         }
         m_depth = depth;
         Attach(s);
         return 0;
      }

      /** Return assigned port number. */
      port_t GetPort()
      {
         return GetSockPort();
      }

      /** Return listen queue depth. */
      int GetDepth()
      {
         return m_depth;
      }

      /** OnRead on a listen_socket receives an incoming connection. */
      void OnRead()
      {
         struct sockaddr sa;
         socklen_t sa_len = sizeof(struct sockaddr);
         SOCKET a_s = accept(GetSocket(), &sa, &sa_len);

         if (a_s == INVALID_SOCKET)
         {
            Handler().LogError(this, "accept", Errno, StrError(Errno), ::gen::log::level::error);
            return;
         }
         if (!Handler().OkToAccept(this))
         {
            Handler().LogError(this, "accept", -1, "Not OK to accept", ::gen::log::level::warning);
            ::closesocket(a_s);
            return;
         }
         if (Handler().get_count() >= FD_SETSIZE)
         {
            Handler().LogError(this, "accept", (int)Handler().get_count(), "socket_handler_base fd_set limit reached", ::gen::log::level::fatal);
            ::closesocket(a_s);
            return;
         }
         socket *tmp = m_bHasCreate ? m_creator -> create() : new X(Handler());
         tmp->m_strCat = m_strCat;
         tmp -> EnableSSL(IsSSL()); // SSL Enabled socket
         tmp -> SetIpv6( IsIpv6() );
         tmp -> SetParent(this);
         tmp -> Attach(a_s);
         tmp -> SetNonblocking(true);
         {
            if (sa_len == sizeof(struct sockaddr_in6))
            {
               struct sockaddr_in6 *p = (struct sockaddr_in6 *)&sa;
               if (p -> sin6_family == AF_INET6)
               {
                  ipv6_address ad(get_app(), p -> sin6_addr,ntohs(p -> sin6_port));
                  ad.SetFlowinfo(p -> sin6_flowinfo);
   #ifndef _WIN32
                  ad.SetScopeId(p -> sin6_scope_id);
   #endif
                  tmp -> SetRemoteAddress(ad);
               }
            }
            if (sa_len == sizeof(struct sockaddr_in))
            {
               struct sockaddr_in *p = (struct sockaddr_in *)&sa;
               if (p -> sin_family == AF_INET)
               {
                  ipv4_address ad(get_app(), p->sin_addr, ntohs(p->sin_port));
                  tmp -> SetRemoteAddress(ad);
               }
            }
         }
         tmp->m_iBindPort = m_iBindPort;
         tmp -> SetConnected(true);
         tmp -> Init();
         tmp -> SetDeleteByHandler(true);
         Handler().add(tmp);
         if(m_bDetach)
         {
            tmp->Detach();
         }
         if (tmp -> IsSSL()) // SSL Enabled socket
         {
            // %! OnSSLAccept calls SSLNegotiate that can finish in this one call.
            // %! If that happens and negotiation fails, the 'tmp' instance is
            // %! still added to the list of active sockets in the sockethandler.
            // %! See bugfix for this in socket_handler::Select - don't Set rwx
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

#ifdef BSD_STYLE_SOCKETS
      /** Please don't use this method.
         "accept()" is handled automatically in the OnRead() method. */
      virtual SOCKET Accept(SOCKET socket, struct sockaddr *saptr, socklen_t *lenptr)
      {
               return accept(socket, saptr, lenptr);
      }
#endif

           bool HasCreator() { return m_bHasCreate; }

      void OnOptions(int,int,int,SOCKET) {
         SetSoReuseaddr(true);
      }

   protected:
      listen_socket(const listen_socket& s) : socket(s) {}
   public:
      listen_socket& operator=(const listen_socket& ) { return *this; }
      int m_depth;
      X *m_creator;
      bool m_bHasCreate;


   };



} // namespace sockets



