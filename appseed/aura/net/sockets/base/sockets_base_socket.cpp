/** \file base_socket.cpp
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
#include "framework.h" // from "aura/net/net_sockets.h"
#include "aura/net/net_sockets.h"
#ifdef _WIN32
#elif defined(LINUX)
#include <netdb.h>
#include <fcntl.h>
#else
#include <netdb.h>
#include <fcntl.h>
#endif
////#include <ctype.h>

#ifdef LINUX
#include <openssl/ssl.h>
#endif

namespace sockets
{


   mutex * base_socket::s_pmutex = NULL;


   base_socket::base_socket(base_socket_handler & h) :
      m_handler(h)
      ,m_bDelete(false)
      ,m_bClose(false)
      ,m_timeCreate(time(NULL))
      ,m_psocketParent(NULL)
      ,m_bDisableRead(false)
      ,m_bConnected(false)
      ,m_bErasedByHandler(false)
      ,m_timeClose(0)
      ,m_bLost(false)
      ,m_bEnableSsl(false)
      ,m_bSsl(false)
      ,m_bSslServer(false)
      ,m_bIpv6(false)
      ,m_bSocks4(false)
      ,m_b_chunked(false)
      ,m_socket(INVALID_SOCKET)
      ,m_socks4_host(h.GetSocks4Host())
      ,m_socks4_port(h.GetSocks4Port())
      ,m_socks4_userid(h.GetSocks4Userid())
      ,m_detach(false)
      ,m_detached(false)
      ,m_pThread(NULL)
      ,m_slave_handler(NULL)
#ifdef HAVE_OPENSSL
      , m_iSslCtxRetry(0)
      //, m_ssl_ctx(NULL)
      //, m_ssl_session(NULL)
      //, ssl_method()(NULL)
      , m_ssl(NULL)
      , m_sbio(NULL)
#endif
      // Line protocol
      ,m_bLineProtocol(false)
      ,m_skip_c(false),
      m_memfileInput(h.get_app()),
      m_event(h.get_app())
   {

      m_iBindPort    = -1;
      m_dwStart      = ::get_tick_count();
      m_pcallback    = NULL;
#ifdef ENABLE_POOL
      m_bEnablePool  = true;
#endif

      m_timeTimeoutLimit = 30;

   }


   base_socket::~base_socket()
   {


   }


   void base_socket::Init()
   {
   }


   void base_socket::OnRead()
   {
   }


   void base_socket::OnWrite()
   {
   }


   void base_socket::OnException()
   {
      // %! exception doesn't always mean something bad happened, this code should be reworked
      // errno valid here?
      int err = SoError();
      log("exception on select", err, wsa_str_error(err), ::aura::log::level_fatal);
      SetCloseAndDelete();
   }


   void base_socket::OnDelete()
   {
   }


   void base_socket::OnConnect()
   {
   }


   void base_socket::OnAccept()
   {
   }


   void base_socket::close()
   {


   }


   int32_t base_socket::close_socket(SOCKET s)
   {

      UNREFERENCED_PARAMETER(s);

      return 0;

   }


   bool base_socket::is_connecting()
   {
      return false;
   }

   /*   SOCKET base_socket::CreateSocket(int af,int iType, const string & strProtocol)
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
   log("getprotobyname", Errno, wsa_str_error(Errno), ::aura::log::level_fatal);
   SetCloseAndDelete();
   throw simple_exception(get_app(), string("getprotobyname() failed: ") + wsa_str_error(Errno));
   return INVALID_SOCKET;
   }
   }
   int protno = p ? p -> p_proto : 0;

   s = ::base_socket(af, iType, protno);
   if (s == INVALID_SOCKET)
   {
   log("base_socket", Errno, wsa_str_error(Errno), ::aura::log::level_fatal);
   SetCloseAndDelete();
   throw simple_exception(get_app(), string("base_socket() failed: ") + wsa_str_error(Errno));
   return INVALID_SOCKET;
   }
   attach(s);
   OnOptions(af, iType, protno, s);
   attach(INVALID_SOCKET);
   return s;
   }
   */

   void base_socket::attach(SOCKET s)
   {

      m_socket = s;

   }


   SOCKET base_socket::GetSocket()
   {
      return m_socket;
   }


   void base_socket::SetDeleteByHandler(bool x)
   {
      m_bDelete = x;
   }


   bool base_socket::DeleteByHandler()
   {
      return m_bDelete;
   }


   void base_socket::SetCloseAndDelete(bool x)
   {
      if (x ^ m_bClose)
      {
         Handler().AddList(m_socket, LIST_CLOSE, x);
         m_bClose = x;
         if (x)
         {
            m_timeClose = time(NULL);
         }
      }
   }


   bool base_socket::CloseAndDelete()
   {
      return m_bClose;
   }


   void base_socket::SetRemoteHostname(const ::net::address & ad) //struct sockaddr* sa, socklen_t l)
   {

      m_addressRemote = ad;

   }


   ::net::address base_socket::GetRemoteHostname()
   {

      return m_addressRemote;

   }


   base_socket_handler& base_socket::Handler() const
   {
      if (IsDetached())
         return *m_slave_handler;
      return m_handler;
   }


   base_socket_handler& base_socket::MasterHandler() const
   {
      return m_handler;
   }


   /*   in_addr base_socket::GetRemoteIP4()
   {
   ipaddr_t l = 0;
   if(m_bIpv6)
   {
   log("GetRemoteIP4", 0, "get ipv4 address for ipv6 base_socket", ::aura::log::level_warning);
   }
   if(m_addressRemote.m_p != NULL)
   {
   struct sockaddr *p = *m_addressRemote;
   struct sockaddr_in *sa = (struct sockaddr_in *)p;
   memcpy(&l, &sa -> sin_addr, sizeof(struct in_addr));
   }
   return l;
   }*/


   /*   struct in6_addr base_socket::GetRemoteIP6()
   {
   if(!m_bIpv6)
   {
   log("GetRemoteIP6", 0, "get ipv6 address for ipv4 base_socket", ::aura::log::level_warning);
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


   /*   port_t base_socket::GetRemotePort()
   {

   return m_addressRemote.get_service_number();

   }*/


   bool base_socket::SetNonblocking(bool bNb)
   {
      m_bNonBlocking = bNb;

#ifdef BSD_STYLE_SOCKETS
         #ifdef _WIN32
      unsigned long l = bNb ? 1 : 0;
      int n = ioctlsocket(m_socket, FIONBIO, &l);
      if (n != 0)
      {
      log("ioctlsocket(FIONBIO)", Errno, "");
      return false;
      }
      return true;
      #else
      if (bNb)
      {
      if (fcntl(m_socket, F_SETFL, O_NONBLOCK) == -1)
      {
      log("fcntl(F_SETFL, O_NONBLOCK)", Errno, wsa_str_error(Errno), ::aura::log::level_error);
      return false;
      }
      }
      else
      {
      if (fcntl(m_socket, F_SETFL, 0) == -1)
      {
      log("fcntl(F_SETFL, 0)", Errno, wsa_str_error(Errno), ::aura::log::level_error);
      return false;
      }
      }
      return true;
      #endif
#else
      return false;

#endif
   }


   bool base_socket::SetNonblocking(bool bNb, SOCKET s)
   {

      UNREFERENCED_PARAMETER(bNb);
      UNREFERENCED_PARAMETER(s);

      return false;

/*   #ifdef _WIN32
   unsigned long l = bNb ? 1 : 0;
   int n = ioctlsocket(s, FIONBIO, &l);
   if (n != 0)
   {
   log("ioctlsocket(FIONBIO)", Errno, "");
   return false;
   }
   return true;
   #else
   if (bNb)
   {
   if (fcntl(s, F_SETFL, O_NONBLOCK) == -1)
   {
   log("fcntl(F_SETFL, O_NONBLOCK)", Errno, wsa_str_error(Errno), ::aura::log::level_error);
   return false;
   }
   }
   else
   {
   if (fcntl(s, F_SETFL, 0) == -1)
   {
   log("fcntl(F_SETFL, 0)", Errno, wsa_str_error(Errno), ::aura::log::level_error);
   return false;
   }
   }
   return true;
   #endif*/
   }


   void base_socket::Set(bool bRead, bool bWrite, bool bException)
   {
      Handler().set(m_socket, bRead, bWrite, bException);
   }


   bool base_socket::Ready()
   {
      if (m_socket != INVALID_SOCKET && !CloseAndDelete())
         return true;
      return false;
   }

   bool base_socket::is_valid()
   {

      return Ready();

   }


   void base_socket::OnLine(const string & )
   {
   }

   bool base_socket::on_select_idle()
   {
      return false;
   }

   void base_socket::OnConnectFailed()
   {
   }


   base_socket *base_socket::get_parent()
   {
      return m_psocketParent;
   }


   void base_socket::set_parent(base_socket * psocketParent)
   {
      m_psocketParent = psocketParent;
   }


   port_t base_socket::GetPort()
   {
      log("GetPort", 0, "GetPort only implemented for listen_socket", ::aura::log::level_warning);
      return 0;
   }


   bool base_socket::OnConnectRetry()
   {
      return true;
   }

   void base_socket::OnReconnect()
   {
   }

   time_t base_socket::Uptime()
   {
      return time(NULL) - m_timeCreate;
   }


   void base_socket::SetIpv6(bool bIpv6)
   {
      m_bIpv6 = bIpv6;
   }


   bool base_socket::IsIpv6()
   {
      return m_bIpv6;
   }

   void base_socket::DisableRead(bool x)
   {
      m_bDisableRead = x;
   }


   bool base_socket::IsDisableRead()
   {
      return m_bDisableRead;
   }



   void base_socket::SetConnected(bool bConnected)
   {
      m_bConnected = bConnected;
   }


   bool base_socket::IsConnected()
   {
      return m_bConnected;
   }


   void base_socket::OnDisconnect()
   {
   }


   void base_socket::SetLost()
   {
      m_bLost = true;
   }


   bool base_socket::Lost()
   {
      return m_bLost;
   }


   void base_socket::SetErasedByHandler(bool bErasedByHandler)
   {
      m_bErasedByHandler = bErasedByHandler;
   }


   bool base_socket::ErasedByHandler()
   {
      return m_bErasedByHandler;
   }


   time_t base_socket::TimeSinceClose()
   {
      return time(NULL) - m_timeClose;
   }


   void base_socket::SetClientRemoteAddress(const ::net::address & address)
   {

      /*      if (!ad.IsValid())
      {
      log("SetClientRemoteAddress", 0, "remote address not valid", ::aura::log::level_error);
      }*/

      m_addressRemoteClient = address;

   }


   ::net::address base_socket::GetClientRemoteAddress()
   {

      /*      if (m_addressRemoteClient.m_p == NULL)
      {
      log("GetClientRemoteAddress", 0, "remote address not yet set", ::aura::log::level_error);
      }*/

      return m_addressRemoteClient;

   }


   uint64_t base_socket::GetBytesSent(bool)
   {
      return 0;
   }


   uint64_t base_socket::GetBytesReceived(bool)
   {
      return 0;
   }


   void base_socket::OnSSLConnect()
   {
   }


   void base_socket::OnSSLAccept()
   {
   }


   bool base_socket::SSLNegotiate()
   {

      return false;

   }

   void base_socket::OnSSLConnectFailed()
   {
   }


   void base_socket::OnSSLAcceptFailed()
   {
   }


   bool base_socket::IsSSL()
   {
      return m_bEnableSsl;
   }


   void base_socket::EnableSSL(bool bEnable)
   {
      m_bEnableSsl = bEnable;
   }


   bool base_socket::IsSSLNegotiate()
   {
      return m_bSsl;
   }


   void base_socket::SetSSLNegotiate(bool bSslNegotiate)
   {
      m_bSsl = bSslNegotiate;
   }


   bool base_socket::IsSSLServer()
   {
      return m_bSslServer;
   }


   void base_socket::SetSSLServer(bool bSSLServer)
   {
      m_bSslServer = bSSLServer;
   }



   void base_socket::CopyConnection(base_socket * psocket)
   {

      m_iSslCtxRetry = psocket->m_iSslCtxRetry;
      m_spsslclientcontext = psocket->m_spsslclientcontext;
      //m_ssl_ctx = psocket->m_ssl_ctx; ///< ssl context
      //m_ssl_session = psocket->m_ssl_session; ///< ssl session
      //ssl_method() = psocket->ssl_method(); ///< ssl method
      //m_ssl = psocket->m_ssl; ///< ssl 'socket'
      m_ssl = psocket->m_ssl; ///< ssl 'socket'
      m_sbio = psocket->m_sbio; ///< ssl bio
      m_password = psocket->m_password; ///< ssl password

      attach(psocket -> GetSocket());

      SetIpv6(psocket -> IsIpv6());
      SetSocketType(psocket -> GetSocketType());
      SetSocketProtocol(psocket -> GetSocketProtocol());

      SetClientRemoteAddress(psocket -> GetClientRemoteAddress());
      SetRemoteHostname(psocket -> GetRemoteHostname());
      psocket->m_socket = INVALID_SOCKET;
      psocket->m_iSslCtxRetry = 0;
      //psocket->m_ssl_ctx = NULL;
      //psocket->m_ssl_session = NULL;
      //psocket->ssl_method() = NULL;
      psocket->m_spsslclientcontext.release();
      psocket->m_ssl = NULL;
      psocket->m_sbio = NULL;
      psocket->m_password.Empty();


   }


   void base_socket::SetIsClient()
   {
      m_bClient = true;
   }


   void base_socket::SetSocketType(int iSocketType)
   {
      m_iSocketType = iSocketType;
   }


   int base_socket::GetSocketType()
   {
      return m_iSocketType;
   }


   void base_socket::SetSocketProtocol(const string & strProtocol)
   {
      m_strSocketProtocol = strProtocol;
   }


   const string & base_socket::GetSocketProtocol()
   {
      return m_strSocketProtocol;
   }


   void base_socket::SetRetain()
   {

      if(m_bClient && m_bEnablePool)
      {

         m_bRetain = true;

      }

   }


   bool base_socket::Retain()
   {
      return m_bEnablePool && m_bRetain && (::get_tick_count() - m_dwStart < 30 * 1000);
   }


   void base_socket::OnSocks4Connect()
   {
      log("OnSocks4Connect", 0, "Use with tcp_socket only");
   }


   void base_socket::OnSocks4ConnectFailed()
   {
      log("OnSocks4ConnectFailed", 0, "Use with tcp_socket only");
   }


   bool base_socket::OnSocks4Read()
   {
      log("OnSocks4Read", 0, "Use with tcp_socket only");
      return true;
   }


   void base_socket::SetSocks4Host(const string & host)
   {

      Session.sockets().net().convert(m_socks4_host, host);

   }


   bool base_socket::Socks4()
   {
      return m_bSocks4;
   }


   void base_socket::SetSocks4(bool x)
   {
      m_bSocks4 = x;
   }


   void base_socket::SetSocks4Host(in_addr a)
   {
      m_socks4_host = a;
   }


   void base_socket::SetSocks4Port(port_t p)
   {
      m_socks4_port = p;
   }


   void base_socket::SetSocks4Userid(const string & x)
   {
      m_socks4_userid = x;
   }


   in_addr base_socket::GetSocks4Host()
   {
      return m_socks4_host;
   }


   port_t base_socket::GetSocks4Port()
   {
      return m_socks4_port;
   }


   const string & base_socket::GetSocks4Userid()
   {
      return m_socks4_userid;
   }

   bool base_socket::detach()
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


   void base_socket::DetachSocket()
   {
      SetDetached();
      m_pThread = cnew(socket_thread(this));
   }


   void base_socket::OnDetached()
   {
   }


   void base_socket::SetDetach(bool x)
   {
      Handler().AddList(m_socket, LIST_DETACH, x);
      m_detach = x;
   }


   bool base_socket::IsDetach()
   {
      return m_detach;
   }


   void base_socket::SetDetached(bool x)
   {
      m_detached = x;
   }


   const bool base_socket::IsDetached() const
   {
      return m_detached;
   }


   void base_socket::SetSlaveHandler(base_socket_handler *p)
   {

      m_slave_handler = p;

   }


   base_socket::socket_thread::socket_thread(base_socket * p) :
      ::object(p->get_app()),
      thread(p->get_app()),
      m_spsocket(p),
      m_sphandler(canew(socket_handler(get_app())))
   {

      begin_synch();

   }


   base_socket::socket_thread::~socket_thread()
   {

   }


   bool base_socket::socket_thread::initialize_thread()
   {

      if (!::thread::initialize_thread())
         return false;

      socket_handler & h = *m_sphandler;

      h.SetSlave();

      h.add(m_spsocket);

      m_spsocket -> SetSlaveHandler(&h);

      m_spsocket -> OnDetached();

      return true;

   }


   int base_socket::socket_thread::run()
   {

      socket_handler & h = *m_sphandler;

      while (get_run_thread() && h.get_count())
      {

         try
         {

            h.select(0, 1000 * 1000);

         }
         catch(...)
         {

            break;

         }

      }

      m_spsocket.release();

      return 0;

   }


   int base_socket::Resolve(const string & host,port_t port)
   {
      return Handler().Resolve(this, host, port);
   }


   int base_socket::Resolve6(const string & host,port_t port)
   {
      return Handler().Resolve6(this, host, port);
   }


   int base_socket::Resolve(in_addr a)
   {
      return Handler().Resolve(this, a);
   }


   int base_socket::Resolve(in6_addr& a)
   {
      return Handler().Resolve(this, a);
   }


   void base_socket::OnResolved(int , const ::net::address & address)
   {
   }


   /*void base_socket::OnResolved(int,in6_addr&,port_t)
   {
   }*/


   void base_socket::OnReverseResolved(int,const string &)
   {
   }


   void base_socket::OnResolveFailed(int)
   {
   }


   /* IP options */


   bool base_socket::SetIpOptions(const void *p, socklen_t len)
   {
#if defined(IP_OPTIONS) && defined(BSD_STYLE_SOCKETS)
      if (setsockopt(GetSocket(), IPPROTO_IP, IP_OPTIONS, (char *)p, len) == -1)
      {
         log("setsockopt(IPPROTO_IP, IP_OPTIONS)", Errno, wsa_str_error(Errno), ::aura::log::level_fatal);
         return false;
      }
      return true;
#else
      log("ip option not available", 0, "IP_OPTIONS", ::aura::log::level_info);
      return false;
#endif
   }


#if defined(IP_PKTINFO) && defined(BSD_STYLE_SOCKETS)
   bool base_socket::SetIpPktinfo(bool x)
   {
      int optval = x ? 1 : 0;
      if (setsockopt(GetSocket(), IPPROTO_IP, IP_PKTINFO, (char *)&optval, sizeof(optval)) == -1)
      {
         log("setsockopt(IPPROTO_IP, IP_PKTINFO)", Errno, wsa_str_error(Errno), ::aura::log::level_fatal);
         return false;
      }
      return true;
   }
#endif


#if defined(IP_RECVTOS) && defined(BSD_STYLE_SOCKETS)
   bool base_socket::SetIpRecvTOS(bool x)
   {
      int optval = x ? 1 : 0;
      if (setsockopt(GetSocket(), IPPROTO_IP, IP_RECVTOS, (char *)&optval, sizeof(optval)) == -1)
      {
         log("setsockopt(IPPROTO_IP, IP_RECVTOS)", Errno, wsa_str_error(Errno), ::aura::log::level_fatal);
         return false;
      }
      return true;
   }
#endif


#if defined(IP_RECVTTL) && defined(BSD_STYLE_SOCKETS)
   bool base_socket::SetIpRecvTTL(bool x)
   {
      int optval = x ? 1 : 0;
      if (setsockopt(GetSocket(), IPPROTO_IP, IP_RECVTTL, (char *)&optval, sizeof(optval)) == -1)
      {
         log("setsockopt(IPPROTO_IP, IP_RECVTTL)", Errno, wsa_str_error(Errno), ::aura::log::level_fatal);
         return false;
      }
      return true;
   }
#endif


#if defined(IP_RECVOPTS) && defined(BSD_STYLE_SOCKETS)
   bool base_socket::SetIpRecvopts(bool x)
   {
      int optval = x ? 1 : 0;
      if (setsockopt(GetSocket(), IPPROTO_IP, IP_RECVOPTS, (char *)&optval, sizeof(optval)) == -1)
      {
         log("setsockopt(IPPROTO_IP, IP_RECVOPTS)", Errno, wsa_str_error(Errno), ::aura::log::level_fatal);
         return false;
      }
      return true;
   }
#endif


#if defined(IP_RETOPTS) && defined(BSD_STYLE_SOCKETS)
   bool base_socket::SetIpRetopts(bool x)
   {
      int optval = x ? 1 : 0;
      if (setsockopt(GetSocket(), IPPROTO_IP, IP_RETOPTS, (char *)&optval, sizeof(optval)) == -1)
      {
         log("setsockopt(IPPROTO_IP, IP_RETOPTS)", Errno, wsa_str_error(Errno), ::aura::log::level_fatal);
         return false;
      }
      return true;
   }
#endif


   bool base_socket::SetIpTOS(unsigned char tos)
   {
#if defined(IP_TOS) && defined(BSD_STYLE_SOCKETS)
      if (setsockopt(GetSocket(), IPPROTO_IP, IP_TOS, (char *)&tos, sizeof(tos)) == -1)
      {
         log("setsockopt(IPPROTO_IP, IP_TOS)", Errno, wsa_str_error(Errno), ::aura::log::level_fatal);
         return false;
      }
      return true;
#else
      log("ip option not available", 0, "IP_TOS", ::aura::log::level_info);
      return false;
#endif
   }


   unsigned char base_socket::IpTOS()
   {
      unsigned char tos = 0;
#if defined(IP_TOS) && defined(BSD_STYLE_SOCKETS)
      socklen_t len = sizeof(tos);
      if (getsockopt(GetSocket(), IPPROTO_IP, IP_TOS, (char *)&tos, &len) == -1)
      {
         log("getsockopt(IPPROTO_IP, IP_TOS)", Errno, wsa_str_error(Errno), ::aura::log::level_fatal);
      }
#else
      log("ip option not available", 0, "IP_TOS", ::aura::log::level_info);
#endif
      return tos;
   }


   bool base_socket::SetIpTTL(int ttl)
   {
#if defined(IP_TTL) && defined(BSD_STYLE_SOCKETS)
      if (setsockopt(GetSocket(), IPPROTO_IP, IP_TTL, (char *)&ttl, sizeof(ttl)) == -1)
      {
         log("setsockopt(IPPROTO_IP, IP_TTL)", Errno, wsa_str_error(Errno), ::aura::log::level_fatal);
         return false;
      }
      return true;
#else
      log("ip option not available", 0, "IP_TTL", ::aura::log::level_info);
      return false;
#endif
   }


   int base_socket::IpTTL()
   {
      int ttl = 0;
#if defined(IP_TTL) && defined(BSD_STYLE_SOCKETS)
      socklen_t len = sizeof(ttl);
      if (getsockopt(GetSocket(), IPPROTO_IP, IP_TTL, (char *)&ttl, &len) == -1)
      {
         log("getsockopt(IPPROTO_IP, IP_TTL)", Errno, wsa_str_error(Errno), ::aura::log::level_fatal);
      }
#else
      log("ip option not available", 0, "IP_TTL", ::aura::log::level_info);
#endif
      return ttl;
   }


   bool base_socket::SetIpHdrincl(bool x)
   {
#if defined(IP_HDRINCL) && defined(BSD_STYLE_SOCKETS)
      int optval = x ? 1 : 0;
      if (setsockopt(GetSocket(), IPPROTO_IP, IP_HDRINCL, (char *)&optval, sizeof(optval)) == -1)
      {
         log("setsockopt(IPPROTO_IP, IP_HDRINCL)", Errno, wsa_str_error(Errno), ::aura::log::level_fatal);
         return false;
      }
      return true;
#else
      log("ip option not available", 0, "IP_HDRINCL", ::aura::log::level_info);
      return false;
#endif
   }


#if defined(IP_RECVERR) && defined(BSD_STYLE_SOCKETS)
   bool base_socket::SetIpRecverr(bool x)
   {
      int optval = x ? 1 : 0;
      if (setsockopt(GetSocket(), IPPROTO_IP, IP_RECVERR, (char *)&optval, sizeof(optval)) == -1)
      {
         log("setsockopt(IPPROTO_IP, IP_RECVERR)", Errno, wsa_str_error(Errno), ::aura::log::level_fatal);
         return false;
      }
      return true;
   }
#endif


#if defined(IP_MTU_DISCOVER) && defined(BSD_STYLE_SOCKETS)
   bool base_socket::SetIpMtudiscover(bool x)
   {
      int optval = x ? 1 : 0;
      if (setsockopt(GetSocket(), IPPROTO_IP, IP_MTU_DISCOVER, (char *)&optval, sizeof(optval)) == -1)
      {
         log("setsockopt(IPPROTO_IP, IP_MTU_DISCOVER)", Errno, wsa_str_error(Errno), ::aura::log::level_fatal);
         return false;
      }
      return true;
   }
#endif


#if defined(IP_MTU) && defined(BSD_STYLE_SOCKETS)
   int base_socket::IpMtu()
   {
      int mtu = 0;
      socklen_t len = sizeof(mtu);
      if (getsockopt(GetSocket(), IPPROTO_IP, IP_MTU, (char *)&mtu, &len) == -1)
      {
         log("getsockopt(IPPROTO_IP, IP_MTU)", Errno, wsa_str_error(Errno), ::aura::log::level_fatal);
      }
      return mtu;
   }
#endif


#if defined(IP_ROUTER_ALERT) && defined(BSD_STYLE_SOCKETS)
   bool base_socket::SetIpRouterAlert(bool x)
   {
      int optval = x ? 1 : 0;
      if (setsockopt(GetSocket(), IPPROTO_IP, IP_ROUTER_ALERT, (char *)&optval, sizeof(optval)) == -1)
      {
         log("setsockopt(IPPROTO_IP, IP_ROUTER_ALERT)", Errno, wsa_str_error(Errno), ::aura::log::level_fatal);
         return false;
      }
      return true;
   }
#endif


   bool base_socket::SetIpMulticastTTL(int ttl)
   {
#if defined(IP_MULTICAST_TTL) && defined(BSD_STYLE_SOCKETS)
      if (setsockopt(GetSocket(), IPPROTO_IP, IP_MULTICAST_TTL, (char *)&ttl, sizeof(ttl)) == -1)
      {
         log("setsockopt(IPPROTO_IP, IP_MULTICAST_TTL)", Errno, wsa_str_error(Errno), ::aura::log::level_fatal);
         return false;
      }
      return true;
#else
      log("ip option not available", 0, "IP_MULTICAST_TTL", ::aura::log::level_info);
      return false;
#endif
   }


   int base_socket::IpMulticastTTL()
   {
      int ttl = 0;
#if defined(IP_MULTICAST_TTL) && defined(BSD_STYLE_SOCKETS)
      socklen_t len = sizeof(ttl);
      if (getsockopt(GetSocket(), IPPROTO_IP, IP_MULTICAST_TTL, (char *)&ttl, &len) == -1)
      {
         log("getsockopt(IPPROTO_IP, IP_MULTICAST_TTL)", Errno, wsa_str_error(Errno), ::aura::log::level_fatal);
      }
#else
      log("ip option not available", 0, "IP_MULTICAST_TTL", ::aura::log::level_info);
#endif
      return ttl;
   }


   bool base_socket::SetMulticastLoop(bool x)
   {
#if defined(IP_MULTICAST_LOOP) && defined(BSD_STYLE_SOCKETS)
      int optval = x ? 1 : 0;
      if (setsockopt(GetSocket(), IPPROTO_IP, IP_MULTICAST_LOOP, (char *)&optval, sizeof(optval)) == -1)
      {
         log("setsockopt(IPPROTO_IP, IP_MULTICAST_LOOP)", Errno, wsa_str_error(Errno), ::aura::log::level_fatal);
         return false;
      }
      return true;
#else
      log("ip option not available", 0, "IP_MULTICAST_LOOP", ::aura::log::level_info);
      return false;
#endif
   }


#ifdef LINUX
   bool base_socket::IpAddMembership(struct ip_mreqn& ref)
   {
#if defined(IP_ADD_MEMBERSHIP) && defined(BSD_STYLE_SOCKETS)
      if (setsockopt(GetSocket(), IPPROTO_IP, IP_ADD_MEMBERSHIP, (char *)&ref, sizeof(struct ip_mreqn)) == -1)
      {
         log("setsockopt(IPPROTO_IP, IP_ADD_MEMBERSHIP)", Errno, wsa_str_error(Errno), ::aura::log::level_fatal);
         return false;
      }
      return true;
#else
      log("ip option not available", 0, "IP_ADD_MEMBERSHIP", ::aura::log::level_info);
      return false;
#endif
   }
#endif


   bool base_socket::IpAddMembership(struct ip_mreq& ref)
   {
#if defined(IP_ADD_MEMBERSHIP) && defined(BSD_STYLE_SOCKETS)
      if (setsockopt(GetSocket(), IPPROTO_IP, IP_ADD_MEMBERSHIP, (char *)&ref, sizeof(struct ip_mreq)) == -1)
      {
         log("setsockopt(IPPROTO_IP, IP_ADD_MEMBERSHIP)", Errno, wsa_str_error(Errno), ::aura::log::level_fatal);
         return false;
      }
      return true;
#else
      log("ip option not available", 0, "IP_ADD_MEMBERSHIP", ::aura::log::level_info);
      return false;
#endif
   }


#ifdef LINUX
   bool base_socket::IpDropMembership(struct ip_mreqn& ref)
   {
#if defined(IP_DROP_MEMBERSHIP) && defined(BSD_STYLE_SOCKETS)
      if (setsockopt(GetSocket(), IPPROTO_IP, IP_DROP_MEMBERSHIP, (char *)&ref, sizeof(struct ip_mreqn)) == -1)
      {
         log("setsockopt(IPPROTO_IP, IP_DROP_MEMBERSHIP)", Errno, wsa_str_error(Errno), ::aura::log::level_fatal);
         return false;
      }
      return true;
#else
      log("ip option not available", 0, "IP_DROP_MEMBERSHIP", ::aura::log::level_info);
      return false;
#endif
   }
#endif


   bool base_socket::IpDropMembership(struct ip_mreq& ref)
   {
#if defined(IP_DROP_MEMBERSHIP) && defined(BSD_STYLE_SOCKETS)
      if (setsockopt(GetSocket(), IPPROTO_IP, IP_DROP_MEMBERSHIP, (char *)&ref, sizeof(struct ip_mreq)) == -1)
      {
         log("setsockopt(IPPROTO_IP, IP_DROP_MEMBERSHIP)", Errno, wsa_str_error(Errno), ::aura::log::level_fatal);
         return false;
      }
      return true;
#else
      log("ip option not available", 0, "IP_DROP_MEMBERSHIP", ::aura::log::level_info);
      return false;
#endif
   }


   /* SOCKET options */


   bool base_socket::SetSoReuseaddr(bool x)
   {
#if defined(SO_REUSEADDR) && defined(BSD_STYLE_SOCKETS)
      int optval = x ? 1 : 0;
      if (setsockopt(GetSocket(), SOL_SOCKET, SO_REUSEADDR, (char *)&optval, sizeof(optval)) == -1)
      {
         log("setsockopt(SOL_SOCKET, SO_REUSEADDR)", Errno, wsa_str_error(Errno), ::aura::log::level_fatal);
         return false;
      }
      return true;
#else
      log("base_socket option not available", 0, "SO_REUSEADDR", ::aura::log::level_info);
      return false;
#endif
   }


   bool base_socket::SetSoKeepalive(bool x)
   {
#if defined(SO_KEEPALIVE) && defined(BSD_STYLE_SOCKETS)
      int optval = x ? 1 : 0;
      if (setsockopt(GetSocket(), SOL_SOCKET, SO_KEEPALIVE, (char *)&optval, sizeof(optval)) == -1)
      {
         log("setsockopt(SOL_SOCKET, SO_KEEPALIVE)", Errno, wsa_str_error(Errno), ::aura::log::level_fatal);
         return false;
      }
      return true;
#else
      log("base_socket option not available", 0, "SO_KEEPALIVE", ::aura::log::level_info);
      return false;
#endif
   }


#if defined(SO_NOSIGPIPE) && defined(BSD_STYLE_SOCKETS)
   bool base_socket::SetSoNosigpipe(bool x)
   {
      int optval = x ? 1 : 0;
      if (setsockopt(GetSocket(), SOL_SOCKET, SO_NOSIGPIPE, (char *)&optval, sizeof(optval)) == -1)
      {
         log("setsockopt(SOL_SOCKET, SO_NOSIGPIPE)", Errno, wsa_str_error(Errno), ::aura::log::level_fatal);
         return false;
      }
      return true;
   }
#endif


   bool base_socket::SoAcceptconn()
   {
      int value = 0;
#if defined(SO_ACCEPTCONN) && defined(BSD_STYLE_SOCKETS)
      socklen_t len = sizeof(value);
      if (getsockopt(GetSocket(), SOL_SOCKET, SO_ACCEPTCONN, (char *)&value, &len) == -1)
      {
         log("getsockopt(SOL_SOCKET, SO_ACCEPTCONN)", Errno, wsa_str_error(Errno), ::aura::log::level_fatal);
      }
#else
      log("base_socket option not available", 0, "SO_ACCEPTCONN", ::aura::log::level_info);
#endif
      return value ? true : false;
   }


#if defined(SO_BSDCOMPAT) && defined(BSD_STYLE_SOCKETS)
   bool base_socket::SetSoBsdcompat(bool x)
   {
      int optval = x ? 1 : 0;
      if (setsockopt(GetSocket(), SOL_SOCKET, SO_BSDCOMPAT, (char *)&optval, sizeof(optval)) == -1)
      {
         log("setsockopt(SOL_SOCKET, SO_BSDCOMPAT)", Errno, wsa_str_error(Errno), ::aura::log::level_fatal);
         return false;
      }
      return true;
   }
#endif


#if defined(SO_BINDTODEVICE) && defined(BSD_STYLE_SOCKETS)
   bool base_socket::SetSoBindtodevice(const string & intf)
   {
      if (setsockopt(GetSocket(), SOL_SOCKET, SO_BINDTODEVICE, (char *) (const char *)intf, intf.get_length()) == -1)
      {
         log("setsockopt(SOL_SOCKET, SO_BINDTODEVICE)", Errno, wsa_str_error(Errno), ::aura::log::level_fatal);
         return false;
      }
      return true;
   }
#endif


   bool base_socket::SetSoBroadcast(bool x)
   {
#if defined(SO_BROADCAST) && defined(BSD_STYLE_SOCKETS)
      int optval = x ? 1 : 0;
      if (setsockopt(GetSocket(), SOL_SOCKET, SO_BROADCAST, (char *)&optval, sizeof(optval)) == -1)
      {
         log("setsockopt(SOL_SOCKET, SO_BROADCAST)", Errno, wsa_str_error(Errno), ::aura::log::level_fatal);
         return false;
      }
      return true;
#else
      log("base_socket option not available", 0, "SO_BROADCAST", ::aura::log::level_info);
      return false;
#endif
   }


   bool base_socket::SetSoDebug(bool x)
   {
#if defined(SO_DEBUG) && defined(BSD_STYLE_SOCKETS)
      int optval = x ? 1 : 0;
      if (setsockopt(GetSocket(), SOL_SOCKET, SO_DEBUG, (char *)&optval, sizeof(optval)) == -1)
      {
         log("setsockopt(SOL_SOCKET, SO_DEBUG)", Errno, wsa_str_error(Errno), ::aura::log::level_fatal);
         return false;
      }
      return true;
#else
      log("base_socket option not available", 0, "SO_DEBUG", ::aura::log::level_info);
      return false;
#endif
   }


   int base_socket::SoError()
   {
      int value = 0;
#if defined(SO_ERROR) && defined(BSD_STYLE_SOCKETS)
      socklen_t len = sizeof(value);
      if (getsockopt(GetSocket(), SOL_SOCKET, SO_ERROR, (char *)&value, &len) == -1)
      {
         log("getsockopt(SOL_SOCKET, SO_ERROR)", Errno, wsa_str_error(Errno), ::aura::log::level_fatal);
      }
#else
      log("base_socket option not available", 0, "SO_ERROR", ::aura::log::level_info);
#endif
      return value;
   }


   bool base_socket::SetSoDontroute(bool x)
   {
#if defined(SO_DONTROUTE) && defined(BSD_STYLE_SOCKETS)
      int optval = x ? 1 : 0;
      if (setsockopt(GetSocket(), SOL_SOCKET, SO_DONTROUTE, (char *)&optval, sizeof(optval)) == -1)
      {
         log("setsockopt(SOL_SOCKET, SO_DONTROUTE)", Errno, wsa_str_error(Errno), ::aura::log::level_fatal);
         return false;
      }
      return true;
#else
      log("base_socket option not available", 0, "SO_DONTROUTE", ::aura::log::level_info);
      return false;
#endif
   }


   bool base_socket::SetSoLinger(int onoff, int linger)
   {
#if defined(SO_LINGER) && defined(BSD_STYLE_SOCKETS)
      struct linger stl;
      stl.l_onoff = (u_short) onoff;
      stl.l_linger = (u_short) linger;
      if (setsockopt(GetSocket(), SOL_SOCKET, SO_LINGER, (char *)&stl, sizeof(stl)) == -1)
      {
         log("setsockopt(SOL_SOCKET, SO_LINGER)", Errno, wsa_str_error(Errno), ::aura::log::level_fatal);
         return false;
      }
      return true;
#else
      log("base_socket option not available", 0, "SO_LINGER", ::aura::log::level_info);
      return false;
#endif
   }


   bool base_socket::SetSoOobinline(bool x)
   {
#if defined(SO_OOBINLINE) && defined(BSD_STYLE_SOCKETS)
      int optval = x ? 1 : 0;
      if (setsockopt(GetSocket(), SOL_SOCKET, SO_OOBINLINE, (char *)&optval, sizeof(optval)) == -1)
      {
         log("setsockopt(SOL_SOCKET, SO_OOBINLINE)", Errno, wsa_str_error(Errno), ::aura::log::level_fatal);
         return false;
      }
      return true;
#else
      log("base_socket option not available", 0, "SO_OOBINLINE", ::aura::log::level_info);
      return false;
#endif
   }


#if defined(SO_PASSCRED) && defined(BSD_STYLE_SOCKETS)
   bool base_socket::SetSoPasscred(bool x)
   {
      int optval = x ? 1 : 0;
      if (setsockopt(GetSocket(), SOL_SOCKET, SO_PASSCRED, (char *)&optval, sizeof(optval)) == -1)
      {
         log("setsockopt(SOL_SOCKET, SO_PASSCRED)", Errno, wsa_str_error(Errno), ::aura::log::level_fatal);
         return false;
      }
      return true;
   }
#endif


#if defined(SO_PEERCRED) && defined(BSD_STYLE_SOCKETS)
   bool base_socket::SoPeercred(struct ::ucred & ucr)
   {
      if (setsockopt(GetSocket(), SOL_SOCKET, SO_PEERCRED, (char *)&ucr, sizeof(ucr)) == -1)
      {
         log("setsockopt(SOL_SOCKET, SO_PEERCRED)", Errno, wsa_str_error(Errno), ::aura::log::level_fatal);
         return false;
      }
      return true;
   }
#endif


#if defined(SO_PRIORITY) && defined(BSD_STYLE_SOCKETS)
   bool base_socket::SetSoPriority(int x)
   {
      if (setsockopt(GetSocket(), SOL_SOCKET, SO_PRIORITY, (char *)&x, sizeof(x)) == -1)
      {
         log("setsockopt(SOL_SOCKET, SO_PRIORITY)", Errno, wsa_str_error(Errno), ::aura::log::level_fatal);
         return false;
      }
      return true;
   }
#endif


   bool base_socket::SetSoRcvlowat(int x)
   {
#if defined(SO_RCVLOWAT) && defined(BSD_STYLE_SOCKETS)
      if (setsockopt(GetSocket(), SOL_SOCKET, SO_RCVLOWAT, (char *)&x, sizeof(x)) == -1)
      {
         log("setsockopt(SOL_SOCKET, SO_RCVLOWAT)", Errno, wsa_str_error(Errno), ::aura::log::level_fatal);
         return false;
      }
      return true;
#else
      log("base_socket option not available", 0, "SO_RCVLOWAT", ::aura::log::level_info);
      return false;
#endif
   }


   bool base_socket::SetSoSndlowat(int x)
   {
#if defined(SO_SNDLOWAT) && defined(BSD_STYLE_SOCKETS)
      if (setsockopt(GetSocket(), SOL_SOCKET, SO_SNDLOWAT, (char *)&x, sizeof(x)) == -1)
      {
         log("setsockopt(SOL_SOCKET, SO_SNDLOWAT)", Errno, wsa_str_error(Errno), ::aura::log::level_fatal);
         return false;
      }
      return true;
#else
      log("base_socket option not available", 0, "SO_SNDLOWAT", ::aura::log::level_info);
      return false;
#endif
   }


   bool base_socket::SetSoRcvtimeo(struct timeval& tv)
   {
#if defined(SO_RCVTIMEO) && defined(BSD_STYLE_SOCKETS)
      if (setsockopt(GetSocket(), SOL_SOCKET, SO_RCVTIMEO, (char *)&tv, sizeof(tv)) == -1)
      {
         log("setsockopt(SOL_SOCKET, SO_RCVTIMEO)", Errno, wsa_str_error(Errno), ::aura::log::level_fatal);
         return false;
      }
      return true;
#else
      log("base_socket option not available", 0, "SO_RCVTIMEO", ::aura::log::level_info);
      return false;
#endif
   }


   bool base_socket::SetSoSndtimeo(struct timeval& tv)
   {
#if defined(SO_SNDTIMEO) && defined(BSD_STYLE_SOCKETS)
      if (setsockopt(GetSocket(), SOL_SOCKET, SO_SNDTIMEO, (char *)&tv, sizeof(tv)) == -1)
      {
         log("setsockopt(SOL_SOCKET, SO_SNDTIMEO)", Errno, wsa_str_error(Errno), ::aura::log::level_fatal);
         return false;
      }
      return true;
#else
      log("base_socket option not available", 0, "SO_SNDTIMEO", ::aura::log::level_info);
      return false;
#endif
   }


   bool base_socket::SetSoRcvbuf(int x)
   {
#if defined(SO_RCVBUF) && defined(BSD_STYLE_SOCKETS)
      if (setsockopt(GetSocket(), SOL_SOCKET, SO_RCVBUF, (char *)&x, sizeof(x)) == -1)
      {
         log("setsockopt(SOL_SOCKET, SO_RCVBUF)", Errno, wsa_str_error(Errno), ::aura::log::level_fatal);
         return false;
      }
      return true;
#else
      log("base_socket option not available", 0, "SO_RCVBUF", ::aura::log::level_info);
      return false;
#endif
   }


   int base_socket::SoRcvbuf()
   {
      int value = 0;
#if defined(SO_RCVBUF) && defined(BSD_STYLE_SOCKETS)
      socklen_t len = sizeof(value);
      if (getsockopt(GetSocket(), SOL_SOCKET, SO_RCVBUF, (char *)&value, &len) == -1)
      {
         log("getsockopt(SOL_SOCKET, SO_RCVBUF)", Errno, wsa_str_error(Errno), ::aura::log::level_fatal);
      }
#else
      log("base_socket option not available", 0, "SO_RCVBUF", ::aura::log::level_info);
#endif
      return value;
   }


#if defined(SO_RCVBUFFORCE) && defined(BSD_STYLE_SOCKETS)
   bool base_socket::SetSoRcvbufforce(int x)
   {
      if (setsockopt(GetSocket(), SOL_SOCKET, SO_RCVBUFFORCE, (char *)&x, sizeof(x)) == -1)
      {
         log("setsockopt(SOL_SOCKET, SO_RCVBUFFORCE)", Errno, wsa_str_error(Errno), ::aura::log::level_fatal);
         return false;
      }
      return true;
   }
#endif


   bool base_socket::SetSoSndbuf(int x)
   {
#if defined(SO_SNDBUF) && defined(BSD_STYLE_SOCKETS)
      if (setsockopt(GetSocket(), SOL_SOCKET, SO_SNDBUF, (char *)&x, sizeof(x)) == -1)
      {
         log("setsockopt(SOL_SOCKET, SO_SNDBUF)", Errno, wsa_str_error(Errno), ::aura::log::level_fatal);
         return false;
      }
      return true;
#else
      log("base_socket option not available", 0, "SO_SNDBUF", ::aura::log::level_info);
      return false;
#endif
   }


   int base_socket::SoSndbuf()
   {
      int value = 0;
#if defined(SO_SNDBUF) && defined(BSD_STYLE_SOCKETS)
      socklen_t len = sizeof(value);
      if (getsockopt(GetSocket(), SOL_SOCKET, SO_SNDBUF, (char *)&value, &len) == -1)
      {
         log("getsockopt(SOL_SOCKET, SO_SNDBUF)", Errno, wsa_str_error(Errno), ::aura::log::level_fatal);
      }
#else
      log("base_socket option not available", 0, "SO_SNDBUF", ::aura::log::level_info);
#endif
      return value;
   }


#if defined(SO_SNDBUFFORCE) && defined(BSD_STYLE_SOCKETS)
   bool base_socket::SetSoSndbufforce(int x)
   {
      if (setsockopt(GetSocket(), SOL_SOCKET, SO_SNDBUFFORCE, (char *)&x, sizeof(x)) == -1)
      {
         log("setsockopt(SOL_SOCKET, SO_SNDBUFFORCE)", Errno, wsa_str_error(Errno), ::aura::log::level_fatal);
         return false;
      }
      return true;
   }
#endif


#if defined(SO_TIMESTAMP) && defined(BSD_STYLE_SOCKETS)
   bool base_socket::SetSoTimestamp(bool x)
   {
      int optval = x ? 1 : 0;
      if (setsockopt(GetSocket(), SOL_SOCKET, SO_TIMESTAMP, (char *)&optval, sizeof(optval)) == -1)
      {
         log("setsockopt(SOL_SOCKET, SO_TIMESTAMP)", Errno, wsa_str_error(Errno), ::aura::log::level_fatal);
         return false;
      }
      return true;
   }
#endif


   int base_socket::SoType()
   {
      int value = 0;

#if defined(SO_TYPE) && defined(BSD_STYLE_SOCKETS)
      socklen_t len = sizeof(value);
      if (getsockopt(GetSocket(), SOL_SOCKET, SO_TYPE, (char *)&value, &len) == -1)
      {
         log("getsockopt(SOL_SOCKET, SO_TYPE)", Errno, wsa_str_error(Errno), ::aura::log::level_fatal);
      }
#else
      log("base_socket option not available", 0, "SO_TYPE", ::aura::log::level_info);
#endif
      return value;
   }


   void base_socket::Subscribe(int id)
   {
      Handler().Subscribe(id, this);
   }


   void base_socket::Unsubscribe(int id)
   {
      Handler().Unsubscribe(id, this);
   }


   void base_socket::OnTrigger(int, const trigger_data&)
   {
   }


   void base_socket::OnCancelled(SOCKET)
   {
   }


   void base_socket::SetTimeout(time_t secs)
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


   void base_socket::OnTimeout()
   {

      m_estatus = status_timed_out;

   }


   void base_socket::OnConnectTimeout()
   {
   }


   bool base_socket::Timeout(time_t tnow)
   {
      if (tnow - m_timeTimeoutStart > m_timeTimeoutLimit)
         return true;
      return false;
   }


   /** Returns local port number for bound base_socket file descriptor. */
   /*   port_t base_socket::GetSockPort()
   {

   ::exception::throw_interface_only(get_app());

   }
   */

   /** Returns local ipv4 address for bound base_socket file descriptor. */
   /*   ipaddr_t base_socket::GetSockIP4()
   {
   ::exception::throw_interface_only(get_app());
   }
   */

   /** Returns local ipv4 address as text for bound base_socket file descriptor. */
   /*   string base_socket::GetSockAddress()
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

   /** Returns local ipv6 address for bound base_socket file descriptor. */
   /*   struct in6_addr base_socket::GetSockIP6()
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

   /** Returns local ipv6 address as text for bound base_socket file descriptor. */
   /*   string base_socket::GetSockAddress6()
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

   void base_socket::on_read(const void * pdata, int_ptr n )
   {

      char * buf = (char *) pdata;

      m_memfileInput.write(buf, n);
      if (LineProtocol())
      {
         buf[n] = 0;
         int i = 0;
         if (m_skip_c && (buf[i] == 13 || buf[i] == 10) && buf[i] != m_c)
         {
            m_skip_c = false;
            i++;
         }
         int x = i;
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
               if(CloseAndDelete())
                  break;
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
            if(CloseAndDelete())
               break;
         }
         if(CloseAndDelete())
            return;
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


   void base_socket::SetLineProtocol(bool x)
   {
      m_bLineProtocol = x;
   }


   bool base_socket::LineProtocol()
   {
      return m_bLineProtocol;
   }

   void base_socket::OnRawData(char * buf, size_t len)
   {
      if(m_pcallback != NULL)
      {
         m_pcallback->OnRawData(this, buf, len);
      }
   }

   /*
   void base_socket::OnAccept(::Windows::Foundation::IAsyncAction ^ action, ::Windows::Foundation::AsyncStatus status)
   {

   if(status == ::Windows::Foundation::Completed)
   {
   OnAccept();
   }

   }
   */


   port_t base_socket::GetRemotePort()
   {

      return m_addressRemote.get_service_number();

   }


   ::net::address base_socket::GetRemoteAddress()
   {

      return m_addressRemote;

   }


   port_t base_socket::GetLocalPort()
   {

      ::exception::throw_interface_only(get_app());

      return 0;

   }


   ::net::address base_socket::GetLocalAddress()
   {

      ::exception::throw_interface_only(get_app());

      return ::net::address();

   }

   void base_socket::run()
   {
   }

   void base_socket::step()
   {
   }


   void base_socket::log(const string & strUser, int32_t err, const string & strSystem, ::aura::log::e_level elevel)
   {

      Handler().log(this, strUser, err, strSystem, elevel);

   }


   string base_socket::get_short_description()
   {

      return Session.sockets().net().canonical_name(GetRemoteAddress());

   }


   void base_socket::free_ssl_session()
   {

      synch_lock sl(m_pmutex);

      if (m_ssl_session != NULL)
      {

         SSL_SESSION_free(m_ssl_session);

         try
         {

            if (m_spsslclientcontext.is_set())
            {

               m_spsslclientcontext->m_psession = NULL;

            }

         }
         catch (...)
         {

         }

         m_ssl_session = NULL;

      }

   }


   void base_socket::get_ssl_session()
   {

      synch_lock sl(m_pmutex);

      if (m_ssl_session == NULL)
      {

         if (m_spsslclientcontext.is_set())
         {

            m_spsslclientcontext->m_psession = SSL_get1_session(m_ssl);

            m_ssl_session = m_spsslclientcontext->m_psession;

         }

      }

   }


} // namespace sockets



