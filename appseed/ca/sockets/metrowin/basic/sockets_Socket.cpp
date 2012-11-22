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
#include <errno.h>
#include <netdb.h>
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


   SOCKET socket::s_socket = 0;
   simple_mutex socket::s_mutex;

   simple_map<int,class sockets::socket *> sockets::socket::s_mapSocket;


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
   m_memfileInput(h.get_app()),
   m_event(h.get_app())
   {

      m_iBindPort    = -1;
      m_dwStart      = ::get_tick_count();
      m_pcallback    = NULL;
      m_bExpectResponse = false;
      m_bExpectRequest = false;
      m_bOnConnect = false;

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
      int err = SoError();
      Handler().LogError(this, "exception on select", err, StrError(err), ::gen::log::level::fatal);
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


   int socket::close()
   {
      if (m_socket == INVALID_SOCKET) // this could happen
      {
         Handler().LogError(this, "socket::close", 0, "file descriptor invalid", ::gen::log::level::warning);
         return 0;
      }
      int n = 0;
      if(!close_socket())
      {
         // failed...
         Handler().LogError(this, "close", Errno, StrError(Errno), ::gen::log::level::error);
         n = -1;
      }
      Handler().Set(m_socket, false, false, false); // remove from fd_set's
      Handler().AddList(m_socket, LIST_CALLONCONNECT, false);
      Handler().AddList(m_socket, LIST_DETACH, false);
      Handler().AddList(m_socket, LIST_TIMEOUT, false);
      Handler().AddList(m_socket, LIST_RETRY, false);
      Handler().AddList(m_socket, LIST_CLOSE, false);
      mutex_lock ml(s_mutex);
      s_mapSocket.remove_key(m_socket);
      m_socket = INVALID_SOCKET;
      return n;
   }

   bool socket::close_socket()
   {
      return true;
   }

/*   SOCKET socket::CreateSocket(int af,int iType, const string & strProtocol)
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
            Handler().LogError(this, "getprotobyname", Errno, StrError(Errno), ::gen::log::level::fatal);
            SetCloseAndDelete();
            throw simple_exception(get_app(), string("getprotobyname() failed: ") + StrError(Errno));
            return INVALID_SOCKET;
         }
      }
      int protno = p ? p -> p_proto : 0;

      s = ::socket(af, iType, protno);
      if (s == INVALID_SOCKET)
      {
         Handler().LogError(this, "socket", Errno, StrError(Errno), ::gen::log::level::fatal);
         SetCloseAndDelete();
         throw simple_exception(get_app(), string("socket() failed: ") + StrError(Errno));
         return INVALID_SOCKET;
      }
      attach(s);
      OnOptions(af, iType, protno, s);
      attach(INVALID_SOCKET);
      return s;
   }
   */

   void socket::attach(Platform::Object ^ o)
   {

      mutex_lock ml(s_mutex);
      m_socket = s_socket;
      s_mapSocket.set_at(m_socket, this);
      s_socket++;


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


   void socket::SetRemoteHostname(sockets::address & ad) //struct sockaddr* sa, socklen_t l)
   {

      m_addressRemote = ad;

   }


   sockets::address socket::GetRemoteHostname()
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


/*   in_addr socket::GetRemoteIP4()
   {
      ipaddr_t l = 0;
      if(m_bIpv6)
      {
         Handler().LogError(this, "GetRemoteIP4", 0, "get ipv4 address for ipv6 socket", ::gen::log::level::warning);
      }
      if(m_addressRemote.m_p != NULL)
      {
         struct sockaddr *p = *m_addressRemote;
         struct sockaddr_in *sa = (struct sockaddr_in *)p;
         memcpy(&l, &sa -> sin_addr, sizeof(struct in_addr));
      }
      return l;
   }*/


/*   struct in6_addr socket::GetRemoteIP6()
   {
      if(!m_bIpv6)
      {
         Handler().LogError(this, "GetRemoteIP6", 0, "get ipv6 address for ipv4 socket", ::gen::log::level::warning);
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


/*   port_t socket::GetRemotePort()
   {

      return m_addressRemote.get_service_number();

   }*/


   bool socket::SetNonblocking(bool bNb)
   {
      m_bNonBlocking = bNb;
      return true;
/*   #ifdef _WIN32
      unsigned long l = bNb ? 1 : 0;
      int n = ioctlsocket(m_socket, FIONBIO, &l);
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
            Handler().LogError(this, "fcntl(F_SETFL, O_NONBLOCK)", Errno, StrError(Errno), ::gen::log::level::error);
            return false;
         }
      }
      else
      {
         if (fcntl(m_socket, F_SETFL, 0) == -1)
         {
            Handler().LogError(this, "fcntl(F_SETFL, 0)", Errno, StrError(Errno), ::gen::log::level::error);
            return false;
         }
      }
      return true;
   #endif*/
   }


/*   bool socket::SetNonblocking(bool bNb, SOCKET s)
   {
   #ifdef _WIN32
      unsigned long l = bNb ? 1 : 0;
      int n = ioctlsocket(s, FIONBIO, &l);
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
            Handler().LogError(this, "fcntl(F_SETFL, O_NONBLOCK)", Errno, StrError(Errno), ::gen::log::level::error);
            return false;
         }
      }
      else
      {
         if (fcntl(s, F_SETFL, 0) == -1)
         {
            Handler().LogError(this, "fcntl(F_SETFL, 0)", Errno, StrError(Errno), ::gen::log::level::error);
            return false;
         }
      }
      return true;
   #endif
   }*/


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
      Handler().LogError(this, "GetPort", 0, "GetPort only implemented for listen_socket", ::gen::log::level::warning);
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


   void socket::SendBuf(const char *,size_t,int)
   {
   }


   void socket::Send(const string &,int)
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


   void socket::SetClientRemoteAddress(sockets::address & address)
   {

/*      if (!ad.IsValid())
      {
         Handler().LogError(this, "SetClientRemoteAddress", 0, "remote address not valid", ::gen::log::level::error);
      }*/

      m_addressRemoteClient = address;

   }


   address socket::GetClientRemoteAddress()
   {

/*      if (m_addressRemoteClient.m_p == NULL)
      {
         Handler().LogError(this, "GetClientRemoteAddress", 0, "remote address not yet set", ::gen::log::level::error);
      }*/

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



   void socket::OnSSLConnectFailed()
   {
   }


   void socket::OnSSLAcceptFailed()
   {
   }
   #endif // HAVE_OPENSSL


   void socket::CopyConnection(socket *sock)
   {

      attach(sock -> GetSocket());
      SetIpv6(sock -> IsIpv6());
      SetSocketType(sock -> GetSocketType());
      SetSocketProtocol(sock -> GetSocketProtocol());

      SetClientRemoteAddress(sock -> GetClientRemoteAddress());
      SetRemoteHostname(sock -> GetRemoteHostname());

   }


   void socket::SetIsClient()
   {
      m_bClient = true;
   }


   void socket::SetSocketType(int iSocketType)
   {
      m_iSocketType = iSocketType;
   }


   int socket::GetSocketType()
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
      Begin();
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


   int socket::socket_thread::run()
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


   int socket::Resolve(const string & host,port_t port)
   {
      return Handler().Resolve(this, host, port);
   }


   int socket::Resolve6(const string & host,port_t port)
   {
      return Handler().Resolve6(this, host, port);
   }


   int socket::Resolve(in_addr a)
   {
      return Handler().Resolve(this, a);
   }


   int socket::Resolve(in6_addr& a)
   {
      return Handler().Resolve(this, a);
   }


   void socket::OnResolved(int , const address &)
   {
   }


   /*void socket::OnResolved(int,in6_addr&,port_t)
   {
   }*/


   void socket::OnReverseResolved(int,const string &)
   {
   }


   void socket::OnResolveFailed(int)
   {
   }


   /* IP options */


   bool socket::SetIpOptions(const void *p, socklen_t len)
   {
   #ifdef IP_OPTIONS
      if (setsockopt(GetSocket(), IPPROTO_IP, IP_OPTIONS, (char *)p, len) == -1)
      {
         Handler().LogError(this, "setsockopt(IPPROTO_IP, IP_OPTIONS)", Errno, StrError(Errno), ::gen::log::level::fatal);
         return false;
      }
      return true;
   #else
      Handler().LogError(this, "ip option not available", 0, "IP_OPTIONS", ::gen::log::level::info);
      return false;
   #endif
   }


   #ifdef IP_PKTINFO
   bool socket::SetIpPktinfo(bool x)
   {
      int optval = x ? 1 : 0;
      if (setsockopt(GetSocket(), IPPROTO_IP, IP_PKTINFO, (char *)&optval, sizeof(optval)) == -1)
      {
         Handler().LogError(this, "setsockopt(IPPROTO_IP, IP_PKTINFO)", Errno, StrError(Errno), ::gen::log::level::fatal);
         return false;
      }
      return true;
   }
   #endif


   #ifdef IP_RECVTOS
   bool socket::SetIpRecvTOS(bool x)
   {
      int optval = x ? 1 : 0;
      if (setsockopt(GetSocket(), IPPROTO_IP, IP_RECVTOS, (char *)&optval, sizeof(optval)) == -1)
      {
         Handler().LogError(this, "setsockopt(IPPROTO_IP, IP_RECVTOS)", Errno, StrError(Errno), ::gen::log::level::fatal);
         return false;
      }
      return true;
   }
   #endif


   #ifdef IP_RECVTTL
   bool socket::SetIpRecvTTL(bool x)
   {
      int optval = x ? 1 : 0;
      if (setsockopt(GetSocket(), IPPROTO_IP, IP_RECVTTL, (char *)&optval, sizeof(optval)) == -1)
      {
         Handler().LogError(this, "setsockopt(IPPROTO_IP, IP_RECVTTL)", Errno, StrError(Errno), ::gen::log::level::fatal);
         return false;
      }
      return true;
   }
   #endif


   #ifdef IP_RECVOPTS
   bool socket::SetIpRecvopts(bool x)
   {
      int optval = x ? 1 : 0;
      if (setsockopt(GetSocket(), IPPROTO_IP, IP_RECVOPTS, (char *)&optval, sizeof(optval)) == -1)
      {
         Handler().LogError(this, "setsockopt(IPPROTO_IP, IP_RECVOPTS)", Errno, StrError(Errno), ::gen::log::level::fatal);
         return false;
      }
      return true;
   }
   #endif


   #ifdef IP_RETOPTS
   bool socket::SetIpRetopts(bool x)
   {
      int optval = x ? 1 : 0;
      if (setsockopt(GetSocket(), IPPROTO_IP, IP_RETOPTS, (char *)&optval, sizeof(optval)) == -1)
      {
         Handler().LogError(this, "setsockopt(IPPROTO_IP, IP_RETOPTS)", Errno, StrError(Errno), ::gen::log::level::fatal);
         return false;
      }
      return true;
   }
   #endif


   bool socket::SetIpTOS(unsigned char tos)
   {
   #ifdef IP_TOS
      if (setsockopt(GetSocket(), IPPROTO_IP, IP_TOS, (char *)&tos, sizeof(tos)) == -1)
      {
         Handler().LogError(this, "setsockopt(IPPROTO_IP, IP_TOS)", Errno, StrError(Errno), ::gen::log::level::fatal);
         return false;
      }
      return true;
   #else
      Handler().LogError(this, "ip option not available", 0, "IP_TOS", ::gen::log::level::info);
      return false;
   #endif
   }


   unsigned char socket::IpTOS()
   {
      unsigned char tos = 0;
   #ifdef IP_TOS
      socklen_t len = sizeof(tos);
      if (getsockopt(GetSocket(), IPPROTO_IP, IP_TOS, (char *)&tos, &len) == -1)
      {
         Handler().LogError(this, "getsockopt(IPPROTO_IP, IP_TOS)", Errno, StrError(Errno), ::gen::log::level::fatal);
      }
   #else
      Handler().LogError(this, "ip option not available", 0, "IP_TOS", ::gen::log::level::info);
   #endif
      return tos;
   }


   bool socket::SetIpTTL(int ttl)
   {
   #ifdef IP_TTL
      if (setsockopt(GetSocket(), IPPROTO_IP, IP_TTL, (char *)&ttl, sizeof(ttl)) == -1)
      {
         Handler().LogError(this, "setsockopt(IPPROTO_IP, IP_TTL)", Errno, StrError(Errno), ::gen::log::level::fatal);
         return false;
      }
      return true;
   #else
      Handler().LogError(this, "ip option not available", 0, "IP_TTL", ::gen::log::level::info);
      return false;
   #endif
   }


   int socket::IpTTL()
   {
      int ttl = 0;
   #ifdef IP_TTL
      socklen_t len = sizeof(ttl);
      if (getsockopt(GetSocket(), IPPROTO_IP, IP_TTL, (char *)&ttl, &len) == -1)
      {
         Handler().LogError(this, "getsockopt(IPPROTO_IP, IP_TTL)", Errno, StrError(Errno), ::gen::log::level::fatal);
      }
   #else
      Handler().LogError(this, "ip option not available", 0, "IP_TTL", ::gen::log::level::info);
   #endif
      return ttl;
   }


   bool socket::SetIpHdrincl(bool x)
   {
   #ifdef IP_HDRINCL
      int optval = x ? 1 : 0;
      if (setsockopt(GetSocket(), IPPROTO_IP, IP_HDRINCL, (char *)&optval, sizeof(optval)) == -1)
      {
         Handler().LogError(this, "setsockopt(IPPROTO_IP, IP_HDRINCL)", Errno, StrError(Errno), ::gen::log::level::fatal);
         return false;
      }
      return true;
   #else
      Handler().LogError(this, "ip option not available", 0, "IP_HDRINCL", ::gen::log::level::info);
      return false;
   #endif
   }


   #ifdef IP_RECVERR
   bool socket::SetIpRecverr(bool x)
   {
      int optval = x ? 1 : 0;
      if (setsockopt(GetSocket(), IPPROTO_IP, IP_RECVERR, (char *)&optval, sizeof(optval)) == -1)
      {
         Handler().LogError(this, "setsockopt(IPPROTO_IP, IP_RECVERR)", Errno, StrError(Errno), ::gen::log::level::fatal);
         return false;
      }
      return true;
   }
   #endif


   #ifdef IP_MTU_DISCOVER
   bool socket::SetIpMtudiscover(bool x)
   {
      int optval = x ? 1 : 0;
      if (setsockopt(GetSocket(), IPPROTO_IP, IP_MTU_DISCOVER, (char *)&optval, sizeof(optval)) == -1)
      {
         Handler().LogError(this, "setsockopt(IPPROTO_IP, IP_MTU_DISCOVER)", Errno, StrError(Errno), ::gen::log::level::fatal);
         return false;
      }
      return true;
   }
   #endif


   #ifdef IP_MTU
   int socket::IpMtu()
   {
      int mtu = 0;
      socklen_t len = sizeof(mtu);
      if (getsockopt(GetSocket(), IPPROTO_IP, IP_MTU, (char *)&mtu, &len) == -1)
      {
         Handler().LogError(this, "getsockopt(IPPROTO_IP, IP_MTU)", Errno, StrError(Errno), ::gen::log::level::fatal);
      }
      return mtu;
   }
   #endif


   #ifdef IP_ROUTER_ALERT
   bool socket::SetIpRouterAlert(bool x)
   {
      int optval = x ? 1 : 0;
      if (setsockopt(GetSocket(), IPPROTO_IP, IP_ROUTER_ALERT, (char *)&optval, sizeof(optval)) == -1)
      {
         Handler().LogError(this, "setsockopt(IPPROTO_IP, IP_ROUTER_ALERT)", Errno, StrError(Errno), ::gen::log::level::fatal);
         return false;
      }
      return true;
   }
   #endif


   bool socket::SetIpMulticastTTL(int ttl)
   {
   #ifdef IP_MULTICAST_TTL
      if (setsockopt(GetSocket(), IPPROTO_IP, IP_MULTICAST_TTL, (char *)&ttl, sizeof(ttl)) == -1)
      {
         Handler().LogError(this, "setsockopt(IPPROTO_IP, IP_MULTICAST_TTL)", Errno, StrError(Errno), ::gen::log::level::fatal);
         return false;
      }
      return true;
   #else
      Handler().LogError(this, "ip option not available", 0, "IP_MULTICAST_TTL", ::gen::log::level::info);
      return false;
   #endif
   }


   int socket::IpMulticastTTL()
   {
      int ttl = 0;
   #ifdef IP_MULTICAST_TTL
      socklen_t len = sizeof(ttl);
      if (getsockopt(GetSocket(), IPPROTO_IP, IP_MULTICAST_TTL, (char *)&ttl, &len) == -1)
      {
         Handler().LogError(this, "getsockopt(IPPROTO_IP, IP_MULTICAST_TTL)", Errno, StrError(Errno), ::gen::log::level::fatal);
      }
   #else
      Handler().LogError(this, "ip option not available", 0, "IP_MULTICAST_TTL", ::gen::log::level::info);
   #endif
      return ttl;
   }


   bool socket::SetMulticastLoop(bool x)
   {
   #ifdef IP_MULTICAST_LOOP
      int optval = x ? 1 : 0;
      if (setsockopt(GetSocket(), IPPROTO_IP, IP_MULTICAST_LOOP, (char *)&optval, sizeof(optval)) == -1)
      {
         Handler().LogError(this, "setsockopt(IPPROTO_IP, IP_MULTICAST_LOOP)", Errno, StrError(Errno), ::gen::log::level::fatal);
         return false;
      }
      return true;
   #else
      Handler().LogError(this, "ip option not available", 0, "IP_MULTICAST_LOOP", ::gen::log::level::info);
      return false;
   #endif
   }


   #ifdef LINUX
   bool socket::IpAddMembership(struct ip_mreqn& ref)
   {
   #ifdef IP_ADD_MEMBERSHIP
      if (setsockopt(GetSocket(), IPPROTO_IP, IP_ADD_MEMBERSHIP, (char *)&ref, sizeof(struct ip_mreqn)) == -1)
      {
         Handler().LogError(this, "setsockopt(IPPROTO_IP, IP_ADD_MEMBERSHIP)", Errno, StrError(Errno), ::gen::log::level::fatal);
         return false;
      }
      return true;
   #else
      Handler().LogError(this, "ip option not available", 0, "IP_ADD_MEMBERSHIP", ::gen::log::level::info);
      return false;
   #endif
   }
   #endif


   bool socket::IpAddMembership(struct ip_mreq& ref)
   {
   #ifdef IP_ADD_MEMBERSHIP
      if (setsockopt(GetSocket(), IPPROTO_IP, IP_ADD_MEMBERSHIP, (char *)&ref, sizeof(struct ip_mreq)) == -1)
      {
         Handler().LogError(this, "setsockopt(IPPROTO_IP, IP_ADD_MEMBERSHIP)", Errno, StrError(Errno), ::gen::log::level::fatal);
         return false;
      }
      return true;
   #else
      Handler().LogError(this, "ip option not available", 0, "IP_ADD_MEMBERSHIP", ::gen::log::level::info);
      return false;
   #endif
   }


   #ifdef LINUX
   bool socket::IpDropMembership(struct ip_mreqn& ref)
   {
   #ifdef IP_DROP_MEMBERSHIP
      if (setsockopt(GetSocket(), IPPROTO_IP, IP_DROP_MEMBERSHIP, (char *)&ref, sizeof(struct ip_mreqn)) == -1)
      {
         Handler().LogError(this, "setsockopt(IPPROTO_IP, IP_DROP_MEMBERSHIP)", Errno, StrError(Errno), ::gen::log::level::fatal);
         return false;
      }
      return true;
   #else
      Handler().LogError(this, "ip option not available", 0, "IP_DROP_MEMBERSHIP", ::gen::log::level::info);
      return false;
   #endif
   }
   #endif


   bool socket::IpDropMembership(struct ip_mreq& ref)
   {
   #ifdef IP_DROP_MEMBERSHIP
      if (setsockopt(GetSocket(), IPPROTO_IP, IP_DROP_MEMBERSHIP, (char *)&ref, sizeof(struct ip_mreq)) == -1)
      {
         Handler().LogError(this, "setsockopt(IPPROTO_IP, IP_DROP_MEMBERSHIP)", Errno, StrError(Errno), ::gen::log::level::fatal);
         return false;
      }
      return true;
   #else
      Handler().LogError(this, "ip option not available", 0, "IP_DROP_MEMBERSHIP", ::gen::log::level::info);
      return false;
   #endif
   }


   /* SOCKET options */


   bool socket::SetSoReuseaddr(bool x)
   {
   #ifdef SO_REUSEADDR
      int optval = x ? 1 : 0;
      if (setsockopt(GetSocket(), SOL_SOCKET, SO_REUSEADDR, (char *)&optval, sizeof(optval)) == -1)
      {
         Handler().LogError(this, "setsockopt(SOL_SOCKET, SO_REUSEADDR)", Errno, StrError(Errno), ::gen::log::level::fatal);
         return false;
      }
      return true;
   #else
      Handler().LogError(this, "socket option not available", 0, "SO_REUSEADDR", ::gen::log::level::info);
      return false;
   #endif
   }


   bool socket::SetSoKeepalive(bool x)
   {
   #ifdef SO_KEEPALIVE
      int optval = x ? 1 : 0;
      if (setsockopt(GetSocket(), SOL_SOCKET, SO_KEEPALIVE, (char *)&optval, sizeof(optval)) == -1)
      {
         Handler().LogError(this, "setsockopt(SOL_SOCKET, SO_KEEPALIVE)", Errno, StrError(Errno), ::gen::log::level::fatal);
         return false;
      }
      return true;
   #else
      Handler().LogError(this, "socket option not available", 0, "SO_KEEPALIVE", ::gen::log::level::info);
      return false;
   #endif
   }


   #ifdef SO_NOSIGPIPE
   bool socket::SetSoNosigpipe(bool x)
   {
      int optval = x ? 1 : 0;
      if (setsockopt(GetSocket(), SOL_SOCKET, SO_NOSIGPIPE, (char *)&optval, sizeof(optval)) == -1)
      {
         Handler().LogError(this, "setsockopt(SOL_SOCKET, SO_NOSIGPIPE)", Errno, StrError(Errno), ::gen::log::level::fatal);
         return false;
      }
      return true;
   }
   #endif


   bool socket::SoAcceptconn()
   {
      int value = 0;
   #ifdef SO_ACCEPTCONN
      socklen_t len = sizeof(value);
      if (getsockopt(GetSocket(), SOL_SOCKET, SO_ACCEPTCONN, (char *)&value, &len) == -1)
      {
         Handler().LogError(this, "getsockopt(SOL_SOCKET, SO_ACCEPTCONN)", Errno, StrError(Errno), ::gen::log::level::fatal);
      }
   #else
      Handler().LogError(this, "socket option not available", 0, "SO_ACCEPTCONN", ::gen::log::level::info);
   #endif
      return value ? true : false;
   }


   #ifdef SO_BSDCOMPAT
   bool socket::SetSoBsdcompat(bool x)
   {
      int optval = x ? 1 : 0;
      if (setsockopt(GetSocket(), SOL_SOCKET, SO_BSDCOMPAT, (char *)&optval, sizeof(optval)) == -1)
      {
         Handler().LogError(this, "setsockopt(SOL_SOCKET, SO_BSDCOMPAT)", Errno, StrError(Errno), ::gen::log::level::fatal);
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
         Handler().LogError(this, "setsockopt(SOL_SOCKET, SO_BINDTODEVICE)", Errno, StrError(Errno), ::gen::log::level::fatal);
         return false;
      }
      return true;
   }
   #endif


   bool socket::SetSoBroadcast(bool x)
   {
   #ifdef SO_BROADCAST
      int optval = x ? 1 : 0;
      if (setsockopt(GetSocket(), SOL_SOCKET, SO_BROADCAST, (char *)&optval, sizeof(optval)) == -1)
      {
         Handler().LogError(this, "setsockopt(SOL_SOCKET, SO_BROADCAST)", Errno, StrError(Errno), ::gen::log::level::fatal);
         return false;
      }
      return true;
   #else
      Handler().LogError(this, "socket option not available", 0, "SO_BROADCAST", ::gen::log::level::info);
      return false;
   #endif
   }


   bool socket::SetSoDebug(bool x)
   {
   #ifdef SO_DEBUG
      int optval = x ? 1 : 0;
      if (setsockopt(GetSocket(), SOL_SOCKET, SO_DEBUG, (char *)&optval, sizeof(optval)) == -1)
      {
         Handler().LogError(this, "setsockopt(SOL_SOCKET, SO_DEBUG)", Errno, StrError(Errno), ::gen::log::level::fatal);
         return false;
      }
      return true;
   #else
      Handler().LogError(this, "socket option not available", 0, "SO_DEBUG", ::gen::log::level::info);
      return false;
   #endif
   }


   int socket::SoError()
   {
      int value = 0;
   #ifdef SO_ERROR
      socklen_t len = sizeof(value);
      if (getsockopt(GetSocket(), SOL_SOCKET, SO_ERROR, (char *)&value, &len) == -1)
      {
         Handler().LogError(this, "getsockopt(SOL_SOCKET, SO_ERROR)", Errno, StrError(Errno), ::gen::log::level::fatal);
      }
   #else
      Handler().LogError(this, "socket option not available", 0, "SO_ERROR", ::gen::log::level::info);
   #endif
      return value;
   }


   bool socket::SetSoDontroute(bool x)
   {
   #ifdef SO_DONTROUTE
      int optval = x ? 1 : 0;
      if (setsockopt(GetSocket(), SOL_SOCKET, SO_DONTROUTE, (char *)&optval, sizeof(optval)) == -1)
      {
         Handler().LogError(this, "setsockopt(SOL_SOCKET, SO_DONTROUTE)", Errno, StrError(Errno), ::gen::log::level::fatal);
         return false;
      }
      return true;
   #else
      Handler().LogError(this, "socket option not available", 0, "SO_DONTROUTE", ::gen::log::level::info);
      return false;
   #endif
   }


   bool socket::SetSoLinger(int onoff, int linger)
   {
   #ifdef SO_LINGER
      struct linger stl;
      stl.l_onoff = (u_short) onoff;
      stl.l_linger = (u_short) linger;
      if (setsockopt(GetSocket(), SOL_SOCKET, SO_LINGER, (char *)&stl, sizeof(stl)) == -1)
      {
         Handler().LogError(this, "setsockopt(SOL_SOCKET, SO_LINGER)", Errno, StrError(Errno), ::gen::log::level::fatal);
         return false;
      }
      return true;
   #else
      Handler().LogError(this, "socket option not available", 0, "SO_LINGER", ::gen::log::level::info);
      return false;
   #endif
   }


   bool socket::SetSoOobinline(bool x)
   {
   #ifdef SO_OOBINLINE
      int optval = x ? 1 : 0;
      if (setsockopt(GetSocket(), SOL_SOCKET, SO_OOBINLINE, (char *)&optval, sizeof(optval)) == -1)
      {
         Handler().LogError(this, "setsockopt(SOL_SOCKET, SO_OOBINLINE)", Errno, StrError(Errno), ::gen::log::level::fatal);
         return false;
      }
      return true;
   #else
      Handler().LogError(this, "socket option not available", 0, "SO_OOBINLINE", ::gen::log::level::info);
      return false;
   #endif
   }


   #ifdef SO_PASSCRED
   bool socket::SetSoPasscred(bool x)
   {
      int optval = x ? 1 : 0;
      if (setsockopt(GetSocket(), SOL_SOCKET, SO_PASSCRED, (char *)&optval, sizeof(optval)) == -1)
      {
         Handler().LogError(this, "setsockopt(SOL_SOCKET, SO_PASSCRED)", Errno, StrError(Errno), ::gen::log::level::fatal);
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
         Handler().LogError(this, "setsockopt(SOL_SOCKET, SO_PEERCRED)", Errno, StrError(Errno), ::gen::log::level::fatal);
         return false;
      }
      return true;
   }
   #endif


   #ifdef SO_PRIORITY
   bool socket::SetSoPriority(int x)
   {
      if (setsockopt(GetSocket(), SOL_SOCKET, SO_PRIORITY, (char *)&x, sizeof(x)) == -1)
      {
         Handler().LogError(this, "setsockopt(SOL_SOCKET, SO_PRIORITY)", Errno, StrError(Errno), ::gen::log::level::fatal);
         return false;
      }
      return true;
   }
   #endif


   bool socket::SetSoRcvlowat(int x)
   {
   #ifdef SO_RCVLOWAT
      if (setsockopt(GetSocket(), SOL_SOCKET, SO_RCVLOWAT, (char *)&x, sizeof(x)) == -1)
      {
         Handler().LogError(this, "setsockopt(SOL_SOCKET, SO_RCVLOWAT)", Errno, StrError(Errno), ::gen::log::level::fatal);
         return false;
      }
      return true;
   #else
      Handler().LogError(this, "socket option not available", 0, "SO_RCVLOWAT", ::gen::log::level::info);
      return false;
   #endif
   }


   bool socket::SetSoSndlowat(int x)
   {
   #ifdef SO_SNDLOWAT
      if (setsockopt(GetSocket(), SOL_SOCKET, SO_SNDLOWAT, (char *)&x, sizeof(x)) == -1)
      {
         Handler().LogError(this, "setsockopt(SOL_SOCKET, SO_SNDLOWAT)", Errno, StrError(Errno), ::gen::log::level::fatal);
         return false;
      }
      return true;
   #else
      Handler().LogError(this, "socket option not available", 0, "SO_SNDLOWAT", ::gen::log::level::info);
      return false;
   #endif
   }


   bool socket::SetSoRcvtimeo(struct timeval& tv)
   {
   #ifdef SO_RCVTIMEO
      if (setsockopt(GetSocket(), SOL_SOCKET, SO_RCVTIMEO, (char *)&tv, sizeof(tv)) == -1)
      {
         Handler().LogError(this, "setsockopt(SOL_SOCKET, SO_RCVTIMEO)", Errno, StrError(Errno), ::gen::log::level::fatal);
         return false;
      }
      return true;
   #else
      Handler().LogError(this, "socket option not available", 0, "SO_RCVTIMEO", ::gen::log::level::info);
      return false;
   #endif
   }


   bool socket::SetSoSndtimeo(struct timeval& tv)
   {
   #ifdef SO_SNDTIMEO
      if (setsockopt(GetSocket(), SOL_SOCKET, SO_SNDTIMEO, (char *)&tv, sizeof(tv)) == -1)
      {
         Handler().LogError(this, "setsockopt(SOL_SOCKET, SO_SNDTIMEO)", Errno, StrError(Errno), ::gen::log::level::fatal);
         return false;
      }
      return true;
   #else
      Handler().LogError(this, "socket option not available", 0, "SO_SNDTIMEO", ::gen::log::level::info);
      return false;
   #endif
   }


   bool socket::SetSoRcvbuf(int x)
   {
   #ifdef SO_RCVBUF
      if (setsockopt(GetSocket(), SOL_SOCKET, SO_RCVBUF, (char *)&x, sizeof(x)) == -1)
      {
         Handler().LogError(this, "setsockopt(SOL_SOCKET, SO_RCVBUF)", Errno, StrError(Errno), ::gen::log::level::fatal);
         return false;
      }
      return true;
   #else
      Handler().LogError(this, "socket option not available", 0, "SO_RCVBUF", ::gen::log::level::info);
      return false;
   #endif
   }


   int socket::SoRcvbuf()
   {
      int value = 0;
   #ifdef SO_RCVBUF
      socklen_t len = sizeof(value);
      if (getsockopt(GetSocket(), SOL_SOCKET, SO_RCVBUF, (char *)&value, &len) == -1)
      {
         Handler().LogError(this, "getsockopt(SOL_SOCKET, SO_RCVBUF)", Errno, StrError(Errno), ::gen::log::level::fatal);
      }
   #else
      Handler().LogError(this, "socket option not available", 0, "SO_RCVBUF", ::gen::log::level::info);
   #endif
      return value;
   }


   #ifdef SO_RCVBUFFORCE
   bool socket::SetSoRcvbufforce(int x)
   {
      if (setsockopt(GetSocket(), SOL_SOCKET, SO_RCVBUFFORCE, (char *)&x, sizeof(x)) == -1)
      {
         Handler().LogError(this, "setsockopt(SOL_SOCKET, SO_RCVBUFFORCE)", Errno, StrError(Errno), ::gen::log::level::fatal);
         return false;
      }
      return true;
   }
   #endif


   bool socket::SetSoSndbuf(int x)
   {
   #ifdef SO_SNDBUF
      if (setsockopt(GetSocket(), SOL_SOCKET, SO_SNDBUF, (char *)&x, sizeof(x)) == -1)
      {
         Handler().LogError(this, "setsockopt(SOL_SOCKET, SO_SNDBUF)", Errno, StrError(Errno), ::gen::log::level::fatal);
         return false;
      }
      return true;
   #else
      Handler().LogError(this, "socket option not available", 0, "SO_SNDBUF", ::gen::log::level::info);
      return false;
   #endif
   }


   int socket::SoSndbuf()
   {
      int value = 0;
   #ifdef SO_SNDBUF
      socklen_t len = sizeof(value);
      if (getsockopt(GetSocket(), SOL_SOCKET, SO_SNDBUF, (char *)&value, &len) == -1)
      {
         Handler().LogError(this, "getsockopt(SOL_SOCKET, SO_SNDBUF)", Errno, StrError(Errno), ::gen::log::level::fatal);
      }
   #else
      Handler().LogError(this, "socket option not available", 0, "SO_SNDBUF", ::gen::log::level::info);
   #endif
      return value;
   }


   #ifdef SO_SNDBUFFORCE
   bool socket::SetSoSndbufforce(int x)
   {
      if (setsockopt(GetSocket(), SOL_SOCKET, SO_SNDBUFFORCE, (char *)&x, sizeof(x)) == -1)
      {
         Handler().LogError(this, "setsockopt(SOL_SOCKET, SO_SNDBUFFORCE)", Errno, StrError(Errno), ::gen::log::level::fatal);
         return false;
      }
      return true;
   }
   #endif


   #ifdef SO_TIMESTAMP
   bool socket::SetSoTimestamp(bool x)
   {
      int optval = x ? 1 : 0;
      if (setsockopt(GetSocket(), SOL_SOCKET, SO_TIMESTAMP, (char *)&optval, sizeof(optval)) == -1)
      {
         Handler().LogError(this, "setsockopt(SOL_SOCKET, SO_TIMESTAMP)", Errno, StrError(Errno), ::gen::log::level::fatal);
         return false;
      }
      return true;
   }
   #endif


   int socket::SoType()
   {
      int value = 0;
   #ifdef SO_TYPE
      socklen_t len = sizeof(value);
      if (getsockopt(GetSocket(), SOL_SOCKET, SO_TYPE, (char *)&value, &len) == -1)
      {
         Handler().LogError(this, "getsockopt(SOL_SOCKET, SO_TYPE)", Errno, StrError(Errno), ::gen::log::level::fatal);
      }
   #else
      Handler().LogError(this, "socket option not available", 0, "SO_TYPE", ::gen::log::level::info);
   #endif
      return value;
   }


   void socket::Subscribe(int id)
   {
      Handler().Subscribe(id, this);
   }


   void socket::Unsubscribe(int id)
   {
      Handler().Unsubscribe(id, this);
   }


   void socket::OnTrigger(int, const TriggerData&)
   {
   }


   void socket::OnCancelled(int)
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
/*   port_t socket::GetSockPort()
   {

      throw interface_only_exception(get_app());

   }
   */

   /** Returns local ipv4 address for bound socket file descriptor. */
/*   ipaddr_t socket::GetSockIP4()
   {
      throw interface_only_exception(get_app());
   }
   */

   /** Returns local ipv4 address as text for bound socket file descriptor. */
/*   string socket::GetSockAddress()
   {
      if (IsIpv6())
      {
         return "";
      }
      struct sockaddr_in sa;
      socklen_t sockaddr_length = sizeof(struct sockaddr_in);
      if (getsockname(GetSocket(), (struct sockaddr *)&sa, (socklen_t*)&sockaddr_length) == -1)
         memset(&sa, 0, sizeof(sa));
      ipv4_address addr(get_app(), sa);
      return addr.Convert();
   }
   */

   /** Returns local ipv6 address for bound socket file descriptor. */
/*   struct in6_addr socket::GetSockIP6()
   {
      if (IsIpv6())
      {
         struct sockaddr_in6 sa;
         socklen_t sockaddr_length = sizeof(struct sockaddr_in6);
         if (getsockname(GetSocket(), (struct sockaddr *)&sa, (socklen_t*)&sockaddr_length) == -1)
            memset(&sa, 0, sizeof(sa));
         return sa.sin6_addr;
      }
      struct in6_addr a;
      memset(&a, 0, sizeof(a));
      return a;
   }
   */

   /** Returns local ipv6 address as text for bound socket file descriptor. */
/*   string socket::GetSockAddress6()
   {
      if (IsIpv6())
      {
         struct sockaddr_in6 sa;
         socklen_t sockaddr_length = sizeof(struct sockaddr_in6);
         if (getsockname(GetSocket(), (struct sockaddr *)&sa, (socklen_t*)&sockaddr_length) == -1)
            memset(&sa, 0, sizeof(sa));
         ipv6_address addr(get_app(), sa);
         return addr.Convert();
      }
      return "";
   }
   */

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

/*
   void socket::OnAccept(::Windows::Foundation::IAsyncAction ^ action, ::Windows::Foundation::AsyncStatus status)
   {

      if(status == ::Windows::Foundation::Completed)
      {
         OnAccept();
      }

   }
   */


   port_t socket::GetRemotePort()
   {

      throw interface_only_exception(get_app());

   }
   

   address socket::GetRemoteAddress()
   {

      throw interface_only_exception(get_app());

   }
   

   port_t socket::GetLocalPort()
   {

      throw interface_only_exception(get_app());

   }
   
   
   address socket::GetLocalAddress()
   {

      throw interface_only_exception(get_app());

   }

   void socket::step()
   {
   }

   void socket::run()
   {
      if(m_bOnConnect)
      {
         m_bOnConnect = false;
         OnConnect();
         return;
      }
      if(m_bExpectRequest)
      {
         m_bExpectRequest = false;
         step();
         return;
      }
      if(m_bExpectResponse)
      {
         m_bExpectResponse = false;
         OnRead();
         return;
      }
   }

} // namespace sockets



