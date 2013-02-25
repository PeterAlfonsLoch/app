/** \file socket.cpp
 **   \date  2004-02-13
 **   \author grymse@alhem.net
**/
/*
Copyright (C) 2004-2007  Anders Hedstrom

This library is made available under the terms of the GNU GPL.

If you would like to use this library in a closed-source application,
a separate license agreement is available. For information about
the closed-source license agreement for the C++ sockets library,
please visit http://www.alhem.net/Sockets/license.html and/or
email license@alhem.net.

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/
#include "framework.h"
#ifdef _WIN32
#else
#include <fcntl.h>
#endif
//#include <ctype.h>


namespace sockets
{

   #ifdef DEBUG
   #define DEB(x) x; fflush(stderr);
   #else
   #define DEB(x)
   #endif


   // statics
   #ifdef _WIN32
   WSAInitializer socket::m_winsock_init;
   #endif


   socket::socket(socket_handler_base& h)
   //:m_flags(0)
   :m_handler(h)
   ,m_socket( INVALID_SOCKET )
   ,m_bDelete(false)
   ,m_bClose(false)
   ,m_timeCreate(time(NULL))
   ,m_psocketParent(NULL)
   ,m_bDisableRead(false)
   ,m_bConnected(false)
   ,m_bErasedByHandler(false)
   ,m_timeClose(0)
   ,m_addressRemoteClient(h.get_app())
   ,m_addressRemote(h.get_app())
   ,m_pfileTrafficMonitor(NULL)
   ,m_bLost(false)
   ,m_bEnableSsl(false)
   ,m_bSsl(false)
   ,m_bSslServer(false)
   ,m_bIpv6(false)
   ,m_iSocketType(0)
   ,m_bClient(false)
   ,m_bRetain(false)
   ,m_bSocks4(false)
   ,m_socks4_host(h.GetSocks4Host())
   ,m_socks4_port(h.GetSocks4Port())
   ,m_socks4_userid(h.GetSocks4Userid())
   ,m_detach(false)
   ,m_detached(false)
   ,m_pThread(NULL)
   ,m_slave_handler(NULL)
   // Line protocol
   ,m_bLineProtocol(false)
   ,m_skip_c(false),
   m_memfileInput(h.get_app())
   {

      m_iBindPort    = -1;
      m_dwStart      = ::get_tick_count();
      m_pcallback    = NULL;

   }


   socket::~socket()
   {
      Handler().remove(this);
      if (m_socket != INVALID_SOCKET
          && !m_bRetain
         )
      {
         close();
      }
   }


   void socket::Init()
   {
   }


   void socket::OnRead()
   {
   }


   void socket::OnWrite()
   {
   }


   void socket::OnException()
   {
      // %! exception doesn't always mean something bad happened, this code should be reworked
      // errno valid here?
      int32_t err = SoError();
      Handler().LogError(this, "exception on select", err, StrError(err), ::ca::log::level_fatal);
      SetCloseAndDelete();
   }


   void socket::OnDelete()
   {
   }


   void socket::OnConnect()
   {
   }


   void socket::OnAccept()
   {
   }


   int32_t socket::close()
   {
      if (m_socket == INVALID_SOCKET) // this could happen
      {
         Handler().LogError(this, "socket::close", 0, "file descriptor invalid", ::ca::log::level_warning);
         return 0;
      }
      int32_t n;
      if ((n = ::closesocket(m_socket)) == -1)
      {
         // failed...
         Handler().LogError(this, "close", Errno, StrError(Errno), ::ca::log::level_error);
      }
      Handler().Set(m_socket, false, false, false); // remove from fd_set's
      Handler().AddList(m_socket, LIST_CALLONCONNECT, false);
      Handler().AddList(m_socket, LIST_DETACH, false);
      Handler().AddList(m_socket, LIST_TIMEOUT, false);
      Handler().AddList(m_socket, LIST_RETRY, false);
      Handler().AddList(m_socket, LIST_CLOSE, false);
      m_socket = INVALID_SOCKET;
      return n;
   }


   SOCKET socket::CreateSocket(int32_t af,int32_t iType, const string & strProtocol)
   {
      struct protoent *p = NULL;
      SOCKET s;

      m_iSocketType = iType;
      m_strSocketProtocol = strProtocol;
      if (strProtocol.get_length())
      {
         p = getprotobyname( strProtocol );
         if (!p)
         {
            Handler().LogError(this, "getprotobyname", Errno, StrError(Errno), ::ca::log::level_fatal);
            SetCloseAndDelete();
            throw simple_exception(get_app(), string("getprotobyname() failed: ") + StrError(Errno));
            return INVALID_SOCKET;
         }
      }
      int32_t protno = p ? p -> p_proto : 0;

      s = ::socket(af, iType, protno);
      if (s == INVALID_SOCKET)
      {
         Handler().LogError(this, "socket", Errno, StrError(Errno), ::ca::log::level_fatal);
         SetCloseAndDelete();
         throw simple_exception(get_app(), string("socket() failed: ") + StrError(Errno));
         return INVALID_SOCKET;
      }
      attach(s);
      OnOptions(af, iType, protno, s);
      attach(INVALID_SOCKET);
      return s;
   }


   void socket::attach(SOCKET s)
   {
      m_socket = s;
   }


   SOCKET socket::GetSocket()
   {
      return m_socket;
   }


   void socket::SetDeleteByHandler(bool x)
   {
      m_bDelete = x;
   }


   bool socket::DeleteByHandler()
   {
      return m_bDelete;
   }


   void socket::SetCloseAndDelete(bool x)
   {
      if (x != m_bClose)
      {
         Handler().AddList(m_socket, LIST_CLOSE, x);
         m_bClose = x;
         if (x)
         {
            m_timeClose = time(NULL);
         }
      }
   }


   bool socket::CloseAndDelete()
   {
      return m_bClose;
   }


   void socket::SetRemoteHostname(const ::sockets::address & ad) //struct sockaddr* sa, socklen_t l)
   {
      m_addressRemote = ad;
   }


   ::sockets::address socket::GetRemoteHostname()
   {
      return m_addressRemote;
   }


   socket_handler_base& socket::Handler() const
   {
      if (IsDetached())
         return *m_slave_handler;
      return m_handler;
   }


   socket_handler_base& socket::MasterHandler() const
   {
      return m_handler;
   }


/*   ipaddr_t socket::GetRemoteIP4()
   {
      ipaddr_t l = 0;
      if(m_bIpv6)
      {
         Handler().LogError(this, "GetRemoteIP4", 0, "get ipv4 address for ipv6 socket", ::ca::log::level_warning);
      }
      if(m_addressRemote.m_p != NULL)
      {
         struct sockaddr *p = *m_addressRemote;
         struct sockaddr_in *sa = (struct sockaddr_in *)p;
         memcpy(&l, &sa -> sin_addr, sizeof(struct in_addr));
      }
      return l;
   }*/


   /*struct in6_addr socket::GetRemoteIP6()
   {
      if(!m_bIpv6)
      {
         Handler().LogError(this, "GetRemoteIP6", 0, "get ipv6 address for ipv4 socket", ::ca::log::level_warning);
      }
      struct sockaddr_in6 fail;
      if (m_addressRemote.m_p != NULL)
      {
         struct sockaddr *p = *m_addressRemote;
         memcpy(&fail, p, sizeof(struct sockaddr_in6));
      }
      else
      {
         memset(&fail, 0, sizeof(struct sockaddr_in6));
      }
      return fail.sin6_addr;
   }*/


   port_t socket::GetRemotePort()
   {
/*      if(m_addressRemote.m_p == NULL)
      {
         return 0;
      }*/
      return m_addressRemote.get_service_number();
   }


   address socket::GetRemoteAddress()
   {
      return m_addressRemote;
   }


   bool socket::SetNonblocking(bool bNb)
   {
   #ifdef _WIN32
      u_long l = bNb ? 1 : 0;
      int32_t n = ioctlsocket(m_socket, FIONBIO, &l);
      if (n != 0)
      {
         Handler().LogError(this, "ioctlsocket(FIONBIO)", Errno, "");
         return false;
      }
      return true;
   #else
      if (bNb)
      {
         if (fcntl(m_socket, F_SETFL, O_NONBLOCK) == -1)
         {
            Handler().LogError(this, "fcntl(F_SETFL, O_NONBLOCK)", Errno, StrError(Errno), ::ca::log::level_error);
            return false;
         }
      }
      else
      {
         if (fcntl(m_socket, F_SETFL, 0) == -1)
         {
            Handler().LogError(this, "fcntl(F_SETFL, 0)", Errno, StrError(Errno), ::ca::log::level_error);
            return false;
         }
      }
      return true;
   #endif
   }


   bool socket::SetNonblocking(bool bNb, SOCKET s)
   {
   #ifdef _WIN32
      u_long l = bNb ? 1 : 0;
      int32_t n = ioctlsocket(s, FIONBIO, &l);
      if (n != 0)
      {
         Handler().LogError(this, "ioctlsocket(FIONBIO)", Errno, "");
         return false;
      }
      return true;
   #else
      if (bNb)
      {
         if (fcntl(s, F_SETFL, O_NONBLOCK) == -1)
         {
            Handler().LogError(this, "fcntl(F_SETFL, O_NONBLOCK)", Errno, StrError(Errno), ::ca::log::level_error);
            return false;
         }
      }
      else
      {
         if (fcntl(s, F_SETFL, 0) == -1)
         {
            Handler().LogError(this, "fcntl(F_SETFL, 0)", Errno, StrError(Errno), ::ca::log::level_error);
            return false;
         }
      }
      return true;
   #endif
   }


   void socket::Set(bool bRead, bool bWrite, bool bException)
   {
      Handler().Set(m_socket, bRead, bWrite, bException);
   }


   bool socket::Ready()
   {
      if (m_socket != INVALID_SOCKET && !CloseAndDelete())
         return true;
      return false;
   }

   bool socket::is_valid()
   {

      return Ready();

   }


   void socket::OnLine(const string & )
   {
   }


   void socket::OnConnectFailed()
   {
   }


   socket *socket::get_parent()
   {
      return m_psocketParent;
   }


   void socket::set_parent(socket * psocketParent)
   {
      m_psocketParent = psocketParent;
   }


   port_t socket::GetPort()
   {
      Handler().LogError(this, "GetPort", 0, "GetPort only implemented for listen_socket", ::ca::log::level_warning);
      return 0;
   }


   bool socket::OnConnectRetry()
   {
      return true;
   }

   void socket::OnReconnect()
   {
   }

   time_t socket::Uptime()
   {
      return time(NULL) - m_timeCreate;
   }


   void socket::SetIpv6(bool bIpv6)
   {
      m_bIpv6 = bIpv6;
   }


   bool socket::IsIpv6()
   {
      return m_bIpv6;
   }

   void socket::DisableRead(bool x)
   {
      m_bDisableRead = x;
   }


   bool socket::IsDisableRead()
   {
      return m_bDisableRead;
   }


   void socket::SendBuf(const char *, int32_t, int32_t)
   {
   }


   void socket::Send(const string &,int32_t)
   {
   }


   void socket::SetConnected(bool bConnected)
   {
      m_bConnected = bConnected;
   }


   bool socket::IsConnected()
   {
      return m_bConnected;
   }


   void socket::OnDisconnect()
   {
   }


   void socket::SetLost()
   {
      m_bLost = true;
   }


   bool socket::Lost()
   {
      return m_bLost;
   }


   void socket::SetErasedByHandler(bool bErasedByHandler)
   {
      m_bErasedByHandler = bErasedByHandler;
   }


   bool socket::ErasedByHandler()
   {
      return m_bErasedByHandler;
   }


   time_t socket::TimeSinceClose()
   {
      return time(NULL) - m_timeClose;
   }


   void socket::SetClientRemoteAddress(const ::sockets::address & ad)
   {
      if (!ad.is_valid())
      {
         Handler().LogError(this, "SetClientRemoteAddress", 0, "remote address not valid", ::ca::log::level_error);
      }
      m_addressRemoteClient = ad;
   }


   address socket::GetClientRemoteAddress()
   {
      if (!m_addressRemoteClient.is_valid())
      {
         Handler().LogError(this, "GetClientRemoteAddress", 0, "remote address not yet set", ::ca::log::level_error);
      }
      return m_addressRemoteClient;
   }


   uint64_t socket::GetBytesSent(bool)
   {
      return 0;
   }


   uint64_t socket::GetBytesReceived(bool)
   {
      return 0;
   }


   #ifdef HAVE_OPENSSL
   void socket::OnSSLConnect()
   {
   }


   void socket::OnSSLAccept()
   {
   }


   bool socket::SSLNegotiate()
   {
      return false;
   }


   bool socket::IsSSL()
   {
      return m_bEnableSsl;
   }


   void socket::EnableSSL(bool bEnable)
   {
      m_bEnableSsl = bEnable;
   }


   bool socket::IsSSLNegotiate()
   {
      return m_bSsl;
   }


   void socket::SetSSLNegotiate(bool bSslNegotiate)
   {
      m_bSsl = bSslNegotiate;
   }


   bool socket::IsSSLServer()
   {
      return m_bSslServer;
   }


   void socket::SetSSLServer(bool bSSLServer)
   {
      m_bSslServer = bSSLServer;
   }


   void socket::OnSSLConnectFailed()
   {
   }


   void socket::OnSSLAcceptFailed()
   {
   }
   #endif // HAVE_OPENSSL


   void socket::CopyConnection(socket *sock)
   {

      attach( sock -> GetSocket() );
      SetIpv6( sock -> IsIpv6() );
      SetSocketType( sock -> GetSocketType() );
      SetSocketProtocol( sock -> GetSocketProtocol() );

      SetClientRemoteAddress(sock -> GetClientRemoteAddress() );
      SetRemoteHostname(sock -> GetRemoteHostname() );
   }


   void socket::SetIsClient()
   {
      m_bClient = true;
   }


   void socket::SetSocketType(int32_t iSocketType)
   {
      m_iSocketType = iSocketType;
   }


   int32_t socket::GetSocketType()
   {
      return m_iSocketType;
   }


   void socket::SetSocketProtocol(const string & strProtocol)
   {
      m_strSocketProtocol = strProtocol;
   }


   const string & socket::GetSocketProtocol()
   {
      return m_strSocketProtocol;
   }


   void socket::SetRetain()
   {
      if(m_bClient) m_bRetain = true;
   }


   bool socket::Retain()
   {
      return m_bRetain && (::get_tick_count() - m_dwStart < 30 * 1000);
   }


   void socket::OnSocks4Connect()
   {
      Handler().LogError(this, "OnSocks4Connect", 0, "Use with tcp_socket only");
   }


   void socket::OnSocks4ConnectFailed()
   {
      Handler().LogError(this, "OnSocks4ConnectFailed", 0, "Use with tcp_socket only");
   }


   bool socket::OnSocks4Read()
   {
      Handler().LogError(this, "OnSocks4Read", 0, "Use with tcp_socket only");
      return true;
   }


   void socket::SetSocks4Host(const string & host)
   {
      System.net().convert(m_socks4_host, host);
   }


   bool socket::Socks4()
   {
      return m_bSocks4;
   }


   void socket::SetSocks4(bool x)
   {
      m_bSocks4 = x;
   }


   void socket::SetSocks4Host(in_addr a)
   {
      m_socks4_host = a;
   }


   void socket::SetSocks4Port(port_t p)
   {
      m_socks4_port = p;
   }


   void socket::SetSocks4Userid(const string & x)
   {
      m_socks4_userid = x;
   }


   in_addr socket::GetSocks4Host()
   {
      return m_socks4_host;
   }


   port_t socket::GetSocks4Port()
   {
      return m_socks4_port;
   }


   const string & socket::GetSocks4Userid()
   {
      return m_socks4_userid;
   }

   bool socket::detach()
   {
      if (!DeleteByHandler())
         return false;
      if (m_pThread)
         return false;
      if (m_detached)
         return false;
      SetDetach();
      return true;
   }


   void socket::DetachSocket()
   {
      SetDetached();
      m_pThread = new socket_thread(this);
   }


   void socket::OnDetached()
   {
   }


   void socket::SetDetach(bool x)
   {
      Handler().AddList(m_socket, LIST_DETACH, x);
      m_detach = x;
   }


   bool socket::IsDetach()
   {
      return m_detach;
   }


   void socket::SetDetached(bool x)
   {
      m_detached = x;
   }


   const bool socket::IsDetached() const
   {
      return m_detached;
   }


   void socket::SetSlaveHandler(socket_handler_base *p)
   {
      m_slave_handler = p;
   }


   socket::socket_thread::socket_thread(socket * p) :
      ::ca::ca(p->get_app()),
      thread(p->get_app()),
      m_psocket(p)
   {
      begin();
   }

   socket::socket_thread::socket_thread(const socket_thread& s) :
      ::ca::ca(((socket_thread & )s).get_app()),
      thread(((socket_thread & )s).get_app()),
      m_psocket(s.GetSocket())
   {
   }


   socket::socket_thread::~socket_thread()
   {
   }


   int32_t socket::socket_thread::run()
   {
      socket_handler h(get_app());
      h.SetSlave();
      h.add(m_psocket);
      m_psocket -> SetSlaveHandler(&h);
      m_psocket -> OnDetached();
      while (h.get_count() && get_run())
      {
         try
         {
            h.Select(30, 0);
         }
         catch(...)
         {
            break;
         }
      }
      return 0;
   }


   int32_t socket::Resolve(const string & host,port_t port)
   {
      return Handler().Resolve(this, host, port);
   }


   int32_t socket::Resolve6(const string & host,port_t port)
   {
      return Handler().Resolve6(this, host, port);
   }


   int32_t socket::Resolve(in_addr a)
   {
      return Handler().Resolve(this, a);
   }


   int32_t socket::Resolve(in6_addr& a)
   {
      return Handler().Resolve(this, a);
   }


   void socket::OnResolved(int32_t,in_addr,port_t)
   {
   }


   void socket::OnResolved(int32_t,in6_addr&,port_t)
   {
   }


   void socket::OnReverseResolved(int32_t,const string &)
   {
   }


   void socket::OnResolveFailed(int32_t)
   {
   }


   /* IP options */


   bool socket::SetIpOptions(const void *p, socklen_t len)
   {
   #ifdef IP_OPTIONS
      if (setsockopt(GetSocket(), IPPROTO_IP, IP_OPTIONS, (char *)p, len) == -1)
      {
         Handler().LogError(this, "setsockopt(IPPROTO_IP, IP_OPTIONS)", Errno, StrError(Errno), ::ca::log::level_fatal);
         return false;
      }
      return true;
   #else
      Handler().LogError(this, "ip option not available", 0, "IP_OPTIONS", ::ca::log::level_info);
      return false;
   #endif
   }


   #ifdef IP_PKTINFO
   bool socket::SetIpPktinfo(bool x)
   {
      int32_t optval = x ? 1 : 0;
      if (setsockopt(GetSocket(), IPPROTO_IP, IP_PKTINFO, (char *)&optval, sizeof(optval)) == -1)
      {
         Handler().LogError(this, "setsockopt(IPPROTO_IP, IP_PKTINFO)", Errno, StrError(Errno), ::ca::log::level_fatal);
         return false;
      }
      return true;
   }
   #endif


   #ifdef IP_RECVTOS
   bool socket::SetIpRecvTOS(bool x)
   {
      int32_t optval = x ? 1 : 0;
      if (setsockopt(GetSocket(), IPPROTO_IP, IP_RECVTOS, (char *)&optval, sizeof(optval)) == -1)
      {
         Handler().LogError(this, "setsockopt(IPPROTO_IP, IP_RECVTOS)", Errno, StrError(Errno), ::ca::log::level_fatal);
         return false;
      }
      return true;
   }
   #endif


   #ifdef IP_RECVTTL
   bool socket::SetIpRecvTTL(bool x)
   {
      int32_t optval = x ? 1 : 0;
      if (setsockopt(GetSocket(), IPPROTO_IP, IP_RECVTTL, (char *)&optval, sizeof(optval)) == -1)
      {
         Handler().LogError(this, "setsockopt(IPPROTO_IP, IP_RECVTTL)", Errno, StrError(Errno), ::ca::log::level_fatal);
         return false;
      }
      return true;
   }
   #endif


   #ifdef IP_RECVOPTS
   bool socket::SetIpRecvopts(bool x)
   {
      int32_t optval = x ? 1 : 0;
      if (setsockopt(GetSocket(), IPPROTO_IP, IP_RECVOPTS, (char *)&optval, sizeof(optval)) == -1)
      {
         Handler().LogError(this, "setsockopt(IPPROTO_IP, IP_RECVOPTS)", Errno, StrError(Errno), ::ca::log::level_fatal);
         return false;
      }
      return true;
   }
   #endif


   #ifdef IP_RETOPTS
   bool socket::SetIpRetopts(bool x)
   {
      int32_t optval = x ? 1 : 0;
      if (setsockopt(GetSocket(), IPPROTO_IP, IP_RETOPTS, (char *)&optval, sizeof(optval)) == -1)
      {
         Handler().LogError(this, "setsockopt(IPPROTO_IP, IP_RETOPTS)", Errno, StrError(Errno), ::ca::log::level_fatal);
         return false;
      }
      return true;
   }
   #endif


   bool socket::SetIpTOS(uchar tos)
   {
   #ifdef IP_TOS
      if (setsockopt(GetSocket(), IPPROTO_IP, IP_TOS, (char *)&tos, sizeof(tos)) == -1)
      {
         Handler().LogError(this, "setsockopt(IPPROTO_IP, IP_TOS)", Errno, StrError(Errno), ::ca::log::level_fatal);
         return false;
      }
      return true;
   #else
      Handler().LogError(this, "ip option not available", 0, "IP_TOS", ::ca::log::level_info);
      return false;
   #endif
   }


   uchar socket::IpTOS()
   {
      uchar tos = 0;
   #ifdef IP_TOS
      socklen_t len = sizeof(tos);
      if (getsockopt(GetSocket(), IPPROTO_IP, IP_TOS, (char *)&tos, &len) == -1)
      {
         Handler().LogError(this, "getsockopt(IPPROTO_IP, IP_TOS)", Errno, StrError(Errno), ::ca::log::level_fatal);
      }
   #else
      Handler().LogError(this, "ip option not available", 0, "IP_TOS", ::ca::log::level_info);
   #endif
      return tos;
   }


   bool socket::SetIpTTL(int32_t ttl)
   {
   #ifdef IP_TTL
      if (setsockopt(GetSocket(), IPPROTO_IP, IP_TTL, (char *)&ttl, sizeof(ttl)) == -1)
      {
         Handler().LogError(this, "setsockopt(IPPROTO_IP, IP_TTL)", Errno, StrError(Errno), ::ca::log::level_fatal);
         return false;
      }
      return true;
   #else
      Handler().LogError(this, "ip option not available", 0, "IP_TTL", ::ca::log::level_info);
      return false;
   #endif
   }


   int32_t socket::IpTTL()
   {
      int32_t ttl = 0;
   #ifdef IP_TTL
      socklen_t len = sizeof(ttl);
      if (getsockopt(GetSocket(), IPPROTO_IP, IP_TTL, (char *)&ttl, &len) == -1)
      {
         Handler().LogError(this, "getsockopt(IPPROTO_IP, IP_TTL)", Errno, StrError(Errno), ::ca::log::level_fatal);
      }
   #else
      Handler().LogError(this, "ip option not available", 0, "IP_TTL", ::ca::log::level_info);
   #endif
      return ttl;
   }


   bool socket::SetIpHdrincl(bool x)
   {
   #ifdef IP_HDRINCL
      int32_t optval = x ? 1 : 0;
      if (setsockopt(GetSocket(), IPPROTO_IP, IP_HDRINCL, (char *)&optval, sizeof(optval)) == -1)
      {
         Handler().LogError(this, "setsockopt(IPPROTO_IP, IP_HDRINCL)", Errno, StrError(Errno), ::ca::log::level_fatal);
         return false;
      }
      return true;
   #else
      Handler().LogError(this, "ip option not available", 0, "IP_HDRINCL", ::ca::log::level_info);
      return false;
   #endif
   }


   #ifdef IP_RECVERR
   bool socket::SetIpRecverr(bool x)
   {
      int32_t optval = x ? 1 : 0;
      if (setsockopt(GetSocket(), IPPROTO_IP, IP_RECVERR, (char *)&optval, sizeof(optval)) == -1)
      {
         Handler().LogError(this, "setsockopt(IPPROTO_IP, IP_RECVERR)", Errno, StrError(Errno), ::ca::log::level_fatal);
         return false;
      }
      return true;
   }
   #endif


   #ifdef IP_MTU_DISCOVER
   bool socket::SetIpMtudiscover(bool x)
   {
      int32_t optval = x ? 1 : 0;
      if (setsockopt(GetSocket(), IPPROTO_IP, IP_MTU_DISCOVER, (char *)&optval, sizeof(optval)) == -1)
      {
         Handler().LogError(this, "setsockopt(IPPROTO_IP, IP_MTU_DISCOVER)", Errno, StrError(Errno), ::ca::log::level_fatal);
         return false;
      }
      return true;
   }
   #endif


   #ifdef IP_MTU
   int32_t socket::IpMtu()
   {
      int32_t mtu = 0;
      socklen_t len = sizeof(mtu);
      if (getsockopt(GetSocket(), IPPROTO_IP, IP_MTU, (char *)&mtu, &len) == -1)
      {
         Handler().LogError(this, "getsockopt(IPPROTO_IP, IP_MTU)", Errno, StrError(Errno), ::ca::log::level_fatal);
      }
      return mtu;
   }
   #endif


   #ifdef IP_ROUTER_ALERT
   bool socket::SetIpRouterAlert(bool x)
   {
      int32_t optval = x ? 1 : 0;
      if (setsockopt(GetSocket(), IPPROTO_IP, IP_ROUTER_ALERT, (char *)&optval, sizeof(optval)) == -1)
      {
         Handler().LogError(this, "setsockopt(IPPROTO_IP, IP_ROUTER_ALERT)", Errno, StrError(Errno), ::ca::log::level_fatal);
         return false;
      }
      return true;
   }
   #endif


   bool socket::SetIpMulticastTTL(int32_t ttl)
   {
   #ifdef IP_MULTICAST_TTL
      if (setsockopt(GetSocket(), IPPROTO_IP, IP_MULTICAST_TTL, (char *)&ttl, sizeof(ttl)) == -1)
      {
         Handler().LogError(this, "setsockopt(IPPROTO_IP, IP_MULTICAST_TTL)", Errno, StrError(Errno), ::ca::log::level_fatal);
         return false;
      }
      return true;
   #else
      Handler().LogError(this, "ip option not available", 0, "IP_MULTICAST_TTL", ::ca::log::level_info);
      return false;
   #endif
   }


   int32_t socket::IpMulticastTTL()
   {
      int32_t ttl = 0;
   #ifdef IP_MULTICAST_TTL
      socklen_t len = sizeof(ttl);
      if (getsockopt(GetSocket(), IPPROTO_IP, IP_MULTICAST_TTL, (char *)&ttl, &len) == -1)
      {
         Handler().LogError(this, "getsockopt(IPPROTO_IP, IP_MULTICAST_TTL)", Errno, StrError(Errno), ::ca::log::level_fatal);
      }
   #else
      Handler().LogError(this, "ip option not available", 0, "IP_MULTICAST_TTL", ::ca::log::level_info);
   #endif
      return ttl;
   }


   bool socket::SetMulticastLoop(bool x)
   {
   #ifdef IP_MULTICAST_LOOP
      int32_t optval = x ? 1 : 0;
      if (setsockopt(GetSocket(), IPPROTO_IP, IP_MULTICAST_LOOP, (char *)&optval, sizeof(optval)) == -1)
      {
         Handler().LogError(this, "setsockopt(IPPROTO_IP, IP_MULTICAST_LOOP)", Errno, StrError(Errno), ::ca::log::level_fatal);
         return false;
      }
      return true;
   #else
      Handler().LogError(this, "ip option not available", 0, "IP_MULTICAST_LOOP", ::ca::log::level_info);
      return false;
   #endif
   }


   #ifdef LINUX
   bool socket::IpAddMembership(struct ip_mreqn& ref)
   {
   #ifdef IP_ADD_MEMBERSHIP
      if (setsockopt(GetSocket(), IPPROTO_IP, IP_ADD_MEMBERSHIP, (char *)&ref, sizeof(struct ip_mreqn)) == -1)
      {
         Handler().LogError(this, "setsockopt(IPPROTO_IP, IP_ADD_MEMBERSHIP)", Errno, StrError(Errno), ::ca::log::level_fatal);
         return false;
      }
      return true;
   #else
      Handler().LogError(this, "ip option not available", 0, "IP_ADD_MEMBERSHIP", ::ca::log::level_info);
      return false;
   #endif
   }
   #endif


   bool socket::IpAddMembership(struct ip_mreq& ref)
   {
   #ifdef IP_ADD_MEMBERSHIP
      if (setsockopt(GetSocket(), IPPROTO_IP, IP_ADD_MEMBERSHIP, (char *)&ref, sizeof(struct ip_mreq)) == -1)
      {
         Handler().LogError(this, "setsockopt(IPPROTO_IP, IP_ADD_MEMBERSHIP)", Errno, StrError(Errno), ::ca::log::level_fatal);
         return false;
      }
      return true;
   #else
      Handler().LogError(this, "ip option not available", 0, "IP_ADD_MEMBERSHIP", ::ca::log::level_info);
      return false;
   #endif
   }


   #ifdef LINUX
   bool socket::IpDropMembership(struct ip_mreqn& ref)
   {
   #ifdef IP_DROP_MEMBERSHIP
      if (setsockopt(GetSocket(), IPPROTO_IP, IP_DROP_MEMBERSHIP, (char *)&ref, sizeof(struct ip_mreqn)) == -1)
      {
         Handler().LogError(this, "setsockopt(IPPROTO_IP, IP_DROP_MEMBERSHIP)", Errno, StrError(Errno), ::ca::log::level_fatal);
         return false;
      }
      return true;
   #else
      Handler().LogError(this, "ip option not available", 0, "IP_DROP_MEMBERSHIP", ::ca::log::level_info);
      return false;
   #endif
   }
   #endif


   bool socket::IpDropMembership(struct ip_mreq& ref)
   {
   #ifdef IP_DROP_MEMBERSHIP
      if (setsockopt(GetSocket(), IPPROTO_IP, IP_DROP_MEMBERSHIP, (char *)&ref, sizeof(struct ip_mreq)) == -1)
      {
         Handler().LogError(this, "setsockopt(IPPROTO_IP, IP_DROP_MEMBERSHIP)", Errno, StrError(Errno), ::ca::log::level_fatal);
         return false;
      }
      return true;
   #else
      Handler().LogError(this, "ip option not available", 0, "IP_DROP_MEMBERSHIP", ::ca::log::level_info);
      return false;
   #endif
   }


   /* SOCKET options */


   bool socket::SetSoReuseaddr(bool x)
   {
   #ifdef SO_REUSEADDR
      int32_t optval = x ? 1 : 0;
      if (setsockopt(GetSocket(), SOL_SOCKET, SO_REUSEADDR, (char *)&optval, sizeof(optval)) == -1)
      {
         Handler().LogError(this, "setsockopt(SOL_SOCKET, SO_REUSEADDR)", Errno, StrError(Errno), ::ca::log::level_fatal);
         return false;
      }
      return true;
   #else
      Handler().LogError(this, "socket option not available", 0, "SO_REUSEADDR", ::ca::log::level_info);
      return false;
   #endif
   }


   bool socket::SetSoKeepalive(bool x)
   {
   #ifdef SO_KEEPALIVE
      int32_t optval = x ? 1 : 0;
      if (setsockopt(GetSocket(), SOL_SOCKET, SO_KEEPALIVE, (char *)&optval, sizeof(optval)) == -1)
      {
         Handler().LogError(this, "setsockopt(SOL_SOCKET, SO_KEEPALIVE)", Errno, StrError(Errno), ::ca::log::level_fatal);
         return false;
      }
      return true;
   #else
      Handler().LogError(this, "socket option not available", 0, "SO_KEEPALIVE", ::ca::log::level_info);
      return false;
   #endif
   }


   #ifdef SO_NOSIGPIPE
   bool socket::SetSoNosigpipe(bool x)
   {
      int32_t optval = x ? 1 : 0;
      if (setsockopt(GetSocket(), SOL_SOCKET, SO_NOSIGPIPE, (char *)&optval, sizeof(optval)) == -1)
      {
         Handler().LogError(this, "setsockopt(SOL_SOCKET, SO_NOSIGPIPE)", Errno, StrError(Errno), ::ca::log::level_fatal);
         return false;
      }
      return true;
   }
   #endif


   bool socket::SoAcceptconn()
   {
      int32_t value = 0;
   #ifdef SO_ACCEPTCONN
      socklen_t len = sizeof(value);
      if (getsockopt(GetSocket(), SOL_SOCKET, SO_ACCEPTCONN, (char *)&value, &len) == -1)
      {
         Handler().LogError(this, "getsockopt(SOL_SOCKET, SO_ACCEPTCONN)", Errno, StrError(Errno), ::ca::log::level_fatal);
      }
   #else
      Handler().LogError(this, "socket option not available", 0, "SO_ACCEPTCONN", ::ca::log::level_info);
   #endif
      return value ? true : false;
   }


   #ifdef SO_BSDCOMPAT
   bool socket::SetSoBsdcompat(bool x)
   {
      int32_t optval = x ? 1 : 0;
      if (setsockopt(GetSocket(), SOL_SOCKET, SO_BSDCOMPAT, (char *)&optval, sizeof(optval)) == -1)
      {
         Handler().LogError(this, "setsockopt(SOL_SOCKET, SO_BSDCOMPAT)", Errno, StrError(Errno), ::ca::log::level_fatal);
         return false;
      }
      return true;
   }
   #endif


   #ifdef SO_BINDTODEVICE
   bool socket::SetSoBindtodevice(const string & intf)
   {
      if (setsockopt(GetSocket(), SOL_SOCKET, SO_BINDTODEVICE, (char *) (const char *)intf, intf.get_length()) == -1)
      {
         Handler().LogError(this, "setsockopt(SOL_SOCKET, SO_BINDTODEVICE)", Errno, StrError(Errno), ::ca::log::level_fatal);
         return false;
      }
      return true;
   }
   #endif


   bool socket::SetSoBroadcast(bool x)
   {
   #ifdef SO_BROADCAST
      int32_t optval = x ? 1 : 0;
      if (setsockopt(GetSocket(), SOL_SOCKET, SO_BROADCAST, (char *)&optval, sizeof(optval)) == -1)
      {
         Handler().LogError(this, "setsockopt(SOL_SOCKET, SO_BROADCAST)", Errno, StrError(Errno), ::ca::log::level_fatal);
         return false;
      }
      return true;
   #else
      Handler().LogError(this, "socket option not available", 0, "SO_BROADCAST", ::ca::log::level_info);
      return false;
   #endif
   }


   bool socket::SetSoDebug(bool x)
   {
   #ifdef SO_DEBUG
      int32_t optval = x ? 1 : 0;
      if (setsockopt(GetSocket(), SOL_SOCKET, SO_DEBUG, (char *)&optval, sizeof(optval)) == -1)
      {
         Handler().LogError(this, "setsockopt(SOL_SOCKET, SO_DEBUG)", Errno, StrError(Errno), ::ca::log::level_fatal);
         return false;
      }
      return true;
   #else
      Handler().LogError(this, "socket option not available", 0, "SO_DEBUG", ::ca::log::level_info);
      return false;
   #endif
   }


   int32_t socket::SoError()
   {
      int32_t value = 0;
   #ifdef SO_ERROR
      socklen_t len = sizeof(value);
      if (getsockopt(GetSocket(), SOL_SOCKET, SO_ERROR, (char *)&value, &len) == -1)
      {
         Handler().LogError(this, "getsockopt(SOL_SOCKET, SO_ERROR)", Errno, StrError(Errno), ::ca::log::level_fatal);
      }
   #else
      Handler().LogError(this, "socket option not available", 0, "SO_ERROR", ::ca::log::level_info);
   #endif
      return value;
   }


   bool socket::SetSoDontroute(bool x)
   {
   #ifdef SO_DONTROUTE
      int32_t optval = x ? 1 : 0;
      if (setsockopt(GetSocket(), SOL_SOCKET, SO_DONTROUTE, (char *)&optval, sizeof(optval)) == -1)
      {
         Handler().LogError(this, "setsockopt(SOL_SOCKET, SO_DONTROUTE)", Errno, StrError(Errno), ::ca::log::level_fatal);
         return false;
      }
      return true;
   #else
      Handler().LogError(this, "socket option not available", 0, "SO_DONTROUTE", ::ca::log::level_info);
      return false;
   #endif
   }


   bool socket::SetSoLinger(int32_t onoff, int32_t linger)
   {
   #ifdef SO_LINGER
      struct linger stl;
      stl.l_onoff = (u_short) onoff;
      stl.l_linger = (u_short) linger;
      if (setsockopt(GetSocket(), SOL_SOCKET, SO_LINGER, (char *)&stl, sizeof(stl)) == -1)
      {
         Handler().LogError(this, "setsockopt(SOL_SOCKET, SO_LINGER)", Errno, StrError(Errno), ::ca::log::level_fatal);
         return false;
      }
      return true;
   #else
      Handler().LogError(this, "socket option not available", 0, "SO_LINGER", ::ca::log::level_info);
      return false;
   #endif
   }


   bool socket::SetSoOobinline(bool x)
   {
   #ifdef SO_OOBINLINE
      int32_t optval = x ? 1 : 0;
      if (setsockopt(GetSocket(), SOL_SOCKET, SO_OOBINLINE, (char *)&optval, sizeof(optval)) == -1)
      {
         Handler().LogError(this, "setsockopt(SOL_SOCKET, SO_OOBINLINE)", Errno, StrError(Errno), ::ca::log::level_fatal);
         return false;
      }
      return true;
   #else
      Handler().LogError(this, "socket option not available", 0, "SO_OOBINLINE", ::ca::log::level_info);
      return false;
   #endif
   }


   #ifdef SO_PASSCRED
   bool socket::SetSoPasscred(bool x)
   {
      int32_t optval = x ? 1 : 0;
      if (setsockopt(GetSocket(), SOL_SOCKET, SO_PASSCRED, (char *)&optval, sizeof(optval)) == -1)
      {
         Handler().LogError(this, "setsockopt(SOL_SOCKET, SO_PASSCRED)", Errno, StrError(Errno), ::ca::log::level_fatal);
         return false;
      }
      return true;
   }
   #endif


   #ifdef SO_PEERCRED
   bool socket::SoPeercred(struct ucred& ucr)
   {
      if (setsockopt(GetSocket(), SOL_SOCKET, SO_PEERCRED, (char *)&ucr, sizeof(ucr)) == -1)
      {
         Handler().LogError(this, "setsockopt(SOL_SOCKET, SO_PEERCRED)", Errno, StrError(Errno), ::ca::log::level_fatal);
         return false;
      }
      return true;
   }
   #endif


   #ifdef SO_PRIORITY
   bool socket::SetSoPriority(int32_t x)
   {
      if (setsockopt(GetSocket(), SOL_SOCKET, SO_PRIORITY, (char *)&x, sizeof(x)) == -1)
      {
         Handler().LogError(this, "setsockopt(SOL_SOCKET, SO_PRIORITY)", Errno, StrError(Errno), ::ca::log::level_fatal);
         return false;
      }
      return true;
   }
   #endif


   bool socket::SetSoRcvlowat(int32_t x)
   {
   #ifdef SO_RCVLOWAT
      if (setsockopt(GetSocket(), SOL_SOCKET, SO_RCVLOWAT, (char *)&x, sizeof(x)) == -1)
      {
         Handler().LogError(this, "setsockopt(SOL_SOCKET, SO_RCVLOWAT)", Errno, StrError(Errno), ::ca::log::level_fatal);
         return false;
      }
      return true;
   #else
      Handler().LogError(this, "socket option not available", 0, "SO_RCVLOWAT", ::ca::log::level_info);
      return false;
   #endif
   }


   bool socket::SetSoSndlowat(int32_t x)
   {
   #ifdef SO_SNDLOWAT
      if (setsockopt(GetSocket(), SOL_SOCKET, SO_SNDLOWAT, (char *)&x, sizeof(x)) == -1)
      {
         Handler().LogError(this, "setsockopt(SOL_SOCKET, SO_SNDLOWAT)", Errno, StrError(Errno), ::ca::log::level_fatal);
         return false;
      }
      return true;
   #else
      Handler().LogError(this, "socket option not available", 0, "SO_SNDLOWAT", ::ca::log::level_info);
      return false;
   #endif
   }


   bool socket::SetSoRcvtimeo(struct timeval& tv)
   {
   #ifdef SO_RCVTIMEO
      if (setsockopt(GetSocket(), SOL_SOCKET, SO_RCVTIMEO, (char *)&tv, sizeof(tv)) == -1)
      {
         Handler().LogError(this, "setsockopt(SOL_SOCKET, SO_RCVTIMEO)", Errno, StrError(Errno), ::ca::log::level_fatal);
         return false;
      }
      return true;
   #else
      Handler().LogError(this, "socket option not available", 0, "SO_RCVTIMEO", ::ca::log::level_info);
      return false;
   #endif
   }


   bool socket::SetSoSndtimeo(struct timeval& tv)
   {
   #ifdef SO_SNDTIMEO
      if (setsockopt(GetSocket(), SOL_SOCKET, SO_SNDTIMEO, (char *)&tv, sizeof(tv)) == -1)
      {
         Handler().LogError(this, "setsockopt(SOL_SOCKET, SO_SNDTIMEO)", Errno, StrError(Errno), ::ca::log::level_fatal);
         return false;
      }
      return true;
   #else
      Handler().LogError(this, "socket option not available", 0, "SO_SNDTIMEO", ::ca::log::level_info);
      return false;
   #endif
   }


   bool socket::SetSoRcvbuf(int32_t x)
   {
   #ifdef SO_RCVBUF
      if (setsockopt(GetSocket(), SOL_SOCKET, SO_RCVBUF, (char *)&x, sizeof(x)) == -1)
      {
         Handler().LogError(this, "setsockopt(SOL_SOCKET, SO_RCVBUF)", Errno, StrError(Errno), ::ca::log::level_fatal);
         return false;
      }
      return true;
   #else
      Handler().LogError(this, "socket option not available", 0, "SO_RCVBUF", ::ca::log::level_info);
      return false;
   #endif
   }


   int32_t socket::SoRcvbuf()
   {
      int32_t value = 0;
   #ifdef SO_RCVBUF
      socklen_t len = sizeof(value);
      if (getsockopt(GetSocket(), SOL_SOCKET, SO_RCVBUF, (char *)&value, &len) == -1)
      {
         Handler().LogError(this, "getsockopt(SOL_SOCKET, SO_RCVBUF)", Errno, StrError(Errno), ::ca::log::level_fatal);
      }
   #else
      Handler().LogError(this, "socket option not available", 0, "SO_RCVBUF", ::ca::log::level_info);
   #endif
      return value;
   }


   #ifdef SO_RCVBUFFORCE
   bool socket::SetSoRcvbufforce(int32_t x)
   {
      if (setsockopt(GetSocket(), SOL_SOCKET, SO_RCVBUFFORCE, (char *)&x, sizeof(x)) == -1)
      {
         Handler().LogError(this, "setsockopt(SOL_SOCKET, SO_RCVBUFFORCE)", Errno, StrError(Errno), ::ca::log::level_fatal);
         return false;
      }
      return true;
   }
   #endif


   bool socket::SetSoSndbuf(int32_t x)
   {
   #ifdef SO_SNDBUF
      if (setsockopt(GetSocket(), SOL_SOCKET, SO_SNDBUF, (char *)&x, sizeof(x)) == -1)
      {
         Handler().LogError(this, "setsockopt(SOL_SOCKET, SO_SNDBUF)", Errno, StrError(Errno), ::ca::log::level_fatal);
         return false;
      }
      return true;
   #else
      Handler().LogError(this, "socket option not available", 0, "SO_SNDBUF", ::ca::log::level_info);
      return false;
   #endif
   }


   int32_t socket::SoSndbuf()
   {
      int32_t value = 0;
   #ifdef SO_SNDBUF
      socklen_t len = sizeof(value);
      if (getsockopt(GetSocket(), SOL_SOCKET, SO_SNDBUF, (char *)&value, &len) == -1)
      {
         Handler().LogError(this, "getsockopt(SOL_SOCKET, SO_SNDBUF)", Errno, StrError(Errno), ::ca::log::level_fatal);
      }
   #else
      Handler().LogError(this, "socket option not available", 0, "SO_SNDBUF", ::ca::log::level_info);
   #endif
      return value;
   }


   #ifdef SO_SNDBUFFORCE
   bool socket::SetSoSndbufforce(int32_t x)
   {
      if (setsockopt(GetSocket(), SOL_SOCKET, SO_SNDBUFFORCE, (char *)&x, sizeof(x)) == -1)
      {
         Handler().LogError(this, "setsockopt(SOL_SOCKET, SO_SNDBUFFORCE)", Errno, StrError(Errno), ::ca::log::level_fatal);
         return false;
      }
      return true;
   }
   #endif


   #ifdef SO_TIMESTAMP
   bool socket::SetSoTimestamp(bool x)
   {
      int32_t optval = x ? 1 : 0;
      if (setsockopt(GetSocket(), SOL_SOCKET, SO_TIMESTAMP, (char *)&optval, sizeof(optval)) == -1)
      {
         Handler().LogError(this, "setsockopt(SOL_SOCKET, SO_TIMESTAMP)", Errno, StrError(Errno), ::ca::log::level_fatal);
         return false;
      }
      return true;
   }
   #endif


   int32_t socket::SoType()
   {
      int32_t value = 0;
   #ifdef SO_TYPE
      socklen_t len = sizeof(value);
      if (getsockopt(GetSocket(), SOL_SOCKET, SO_TYPE, (char *)&value, &len) == -1)
      {
         Handler().LogError(this, "getsockopt(SOL_SOCKET, SO_TYPE)", Errno, StrError(Errno), ::ca::log::level_fatal);
      }
   #else
      Handler().LogError(this, "socket option not available", 0, "SO_TYPE", ::ca::log::level_info);
   #endif
      return value;
   }


   void socket::Subscribe(int32_t id)
   {
      Handler().Subscribe(id, this);
   }


   void socket::Unsubscribe(int32_t id)
   {
      Handler().Unsubscribe(id, this);
   }


   void socket::OnTrigger(int32_t, const TriggerData&)
   {
   }


   void socket::OnCancelled(int32_t)
   {
   }


   void socket::SetTimeout(time_t secs)
   {
      if (!secs)
      {
         Handler().AddList(m_socket, LIST_TIMEOUT, false);
         return;
      }
      Handler().AddList(m_socket, LIST_TIMEOUT, true);
      m_timeTimeoutStart = time(NULL);
      m_timeTimeoutLimit = secs;
   }


   void socket::OnTimeout()
   {
   }


   void socket::OnConnectTimeout()
   {
   }


   bool socket::Timeout(time_t tnow)
   {
      if (tnow - m_timeTimeoutStart > m_timeTimeoutLimit)
         return true;
      return false;
   }


   /** Returns local port number for bound socket file descriptor. */
   port_t socket::GetLocalPort()
   {
      if (IsIpv6())
      {
         struct sockaddr_in6 sa;
         socklen_t sockaddr_length = sizeof(struct sockaddr_in6);
         if (getsockname(GetSocket(), (struct sockaddr *)&sa, (socklen_t*)&sockaddr_length) == -1)
            memset(&sa, 0, sizeof(sa));
         return ntohs(sa.sin6_port);
      }
      struct sockaddr_in sa;
      socklen_t sockaddr_length = sizeof(struct sockaddr_in);
      if (getsockname(GetSocket(), (struct sockaddr *)&sa, (socklen_t*)&sockaddr_length) == -1)
         memset(&sa, 0, sizeof(sa));
      return ntohs(sa.sin_port);
   }


   /** Returns local ipv4 address for bound socket file descriptor. */
   address socket::GetLocalAddress()
   {
      if (IsIpv6())
      {
         struct sockaddr_in6 sa;
         socklen_t sockaddr_length = sizeof(struct sockaddr_in6);
         if (getsockname(GetSocket(), (struct sockaddr *)&sa, (socklen_t*)&sockaddr_length) == -1)
            memset(&sa, 0, sizeof(sa));
         return address(get_app(), sa.sin6_addr, GetRemotePort());
      }
      struct sockaddr_in sa;
      socklen_t sockaddr_length = sizeof(struct sockaddr_in);
      if (getsockname(GetSocket(), (struct sockaddr *)&sa, (socklen_t*)&sockaddr_length) == -1)
         memset(&sa, 0, sizeof(sa));
      return address(get_app(), sa.sin_addr, GetRemotePort());
   }


   void socket::OnRead( char *buf, size_t n )
   {
      m_memfileInput.write(buf, n);
      if (LineProtocol())
      {
         buf[n] = 0;
         size_t i = 0;
         if (m_skip_c && (buf[i] == 13 || buf[i] == 10) && buf[i] != m_c)
         {
            m_skip_c = false;
            i++;
         }
         size_t x = i;
         for (; i < n && LineProtocol(); i++)
         {
            while ((buf[i] == 13 || buf[i] == 10) && LineProtocol())
            {
               char c = buf[i];
               buf[i] = 0;
               if (buf[x])
               {
                  m_line += (buf + x);
               }
               OnLine( m_line );
               i++;
               m_skip_c = true;
               m_c = c;
               if (i < n && (buf[i] == 13 || buf[i] == 10) && buf[i] != c)
               {
                  m_skip_c = false;
                  i++;
               }
               x = i;
               m_line = "";
            }
            if (!LineProtocol())
            {
               break;
            }
         }
         if (!LineProtocol())
         {
            if (i < n)
            {
               OnRawData(buf + i, n - i);
            }
         }
         else
         if (buf[x])
         {
            m_line += (buf + x);
         }
      }
      else
      {
         OnRawData(buf, n);
      }
   }


   void socket::SetLineProtocol(bool x)
   {
      m_bLineProtocol = x;
   }


   bool socket::LineProtocol()
   {
      return m_bLineProtocol;
   }

   void socket::OnRawData(char * buf, size_t len)
   {
      if(m_pcallback != NULL)
      {
         m_pcallback->OnRawData(this, buf, len);
      }
   }

   string socket::get_short_description()
   {

      return GetRemoteAddress().get_canonical_name();

   }

} // namespace sockets
