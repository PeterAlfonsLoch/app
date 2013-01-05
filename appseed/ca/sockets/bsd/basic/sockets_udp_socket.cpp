/** \file udp_socket.cpp
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


namespace sockets
{


   udp_socket::udp_socket(socket_handler_base& h, int32_t ibufsz, bool ipv6, int32_t retries) : socket(h)
   , m_ibuf(new char[ibufsz])
   , m_ibufsz(ibufsz)
   , m_bind_ok(false)
   , m_port(0)
   , m_last_size_written(-1)
   , m_retries(retries)
   , m_b_read_ts(false)
   {
      SetIpv6(ipv6);
   }


   udp_socket::~udp_socket()
   {
      close();
      delete[] m_ibuf;
   }


   int32_t udp_socket::Bind(port_t &port, int32_t range)
   {
      if (IsIpv6())
      {
         ipv6_address ad(get_app(), port);
         return Bind((in6_addr) ad.m_addr.sin6_addr, ad.m_addr.sin6_port, range);
      }
      ipv4_address ad(get_app(), port);
      return Bind((in_addr)  ad.m_addr.sin_addr, ad.m_addr.sin_port, range);
   }


   int32_t udp_socket::Bind(const string & intf, port_t &port, int32_t range)
   {
      if (IsIpv6())
      {
         ipv6_address ad(get_app(), intf, port);
         if (ad.IsValid())
         {
            return Bind((in6_addr) ad.m_addr.sin6_addr, ad.m_addr.sin6_port, range);
         }
         SetCloseAndDelete();
         return -1;
      }
      ipv4_address ad(get_app(), intf, port);
      if (ad.IsValid())
      {
         return Bind((in_addr)  ad.m_addr.sin_addr, ad.m_addr.sin_port, range);
      }
      SetCloseAndDelete();
      return -1;
   }


   int32_t udp_socket::Bind(in_addr a, port_t &port, int32_t range)
   {
      address ad(get_app(), a, port);
      return Bind(ad, range);
   }


   int32_t udp_socket::Bind(in6_addr a, port_t &port, int32_t range)
   {
      address ad(get_app(), a, port);
      return Bind(ad, range);
   }


   int32_t udp_socket::Bind(sockets::address& ad, int32_t range)
   {
      if (GetSocket() == INVALID_SOCKET)
      {
         attach(CreateSocket(ad.GetFamily(), SOCK_DGRAM, "udp"));
      }
      if (GetSocket() != INVALID_SOCKET)
      {
         SetNonblocking(true);
         int32_t n = bind(GetSocket(), ad.sa(), ad.sa_len());
         int32_t tries = range;
         while (n == -1 && tries--)
         {
            ad.set_service_number(ad.get_service_number() + 1);
            n = bind(GetSocket(), ad.sa(), ad.sa_len());
         }
         if (n == -1)
         {
            Handler().LogError(this, "bind", Errno, StrError(Errno), ::gen::log::level::fatal);
            SetCloseAndDelete();
            throw simple_exception(get_app(), "bind() failed for udp_socket, port:range: " + ::gen::str::from(ad.get_service_number()) + ":" + ::gen::str::from(range));
            return -1;
         }
         m_bind_ok = true;
         m_port = ad.get_service_number();
         return 0;
      }
      return -1;
   }


   /** if you wish to use Send, first open a connection */
   bool udp_socket::open(in_addr l, port_t port)
   {
      address ad(get_app(), l, port);
      return open(ad);
   }


   bool udp_socket::open(const string & host, port_t port)
   {
      address ad(get_app(), host, port);
      if(!ad.is_valid())
         return false;
      return open(ad);
   }


   bool udp_socket::open(struct in6_addr& a, port_t port)
   {
      address ad(get_app(), a, port);
      return open(ad);
   }


   bool udp_socket::open(sockets::address& ad)
   {
      if (GetSocket() == INVALID_SOCKET)
      {
         attach(CreateSocket(ad.GetFamily(), SOCK_DGRAM, "udp"));
      }
      if (GetSocket() != INVALID_SOCKET)
      {
         SetNonblocking(true);
         if (connect(GetSocket(), ad.sa(), ad.sa_len()) == -1)
         {
            Handler().LogError(this, "connect", Errno, StrError(Errno), ::gen::log::level::fatal);
            SetCloseAndDelete();
            return false;
         }
         SetConnected();
         return true;
      }
      return false;
   }


   void udp_socket::CreateConnection()
   {
      if (IsIpv6())
      {
         if (GetSocket() == INVALID_SOCKET)
         {
            SOCKET s = CreateSocket(AF_INET6, SOCK_DGRAM, "udp");
            if (s == INVALID_SOCKET)
            {
               return;
            }
            SetNonblocking(true, s);
            attach(s);
         }
         return;
      }
      if (GetSocket() == INVALID_SOCKET)
      {
         SOCKET s = CreateSocket(AF_INET, SOCK_DGRAM, "udp");
         if (s == INVALID_SOCKET)
         {
            return;
         }
         SetNonblocking(true, s);
         attach(s);
      }
   }


   /** send to specified address */
   void udp_socket::SendToBuf(const string & h, port_t p, const char *data, int32_t len, int32_t flags)
   {
      SendToBuf(address(get_app(), h, p), data, len, flags);
   }


   /** send to specified address */
   void udp_socket::SendToBuf(const in_addr & a, port_t p, const char *data, int32_t len, int32_t flags)
   {
      SendToBuf(address(get_app(), a, p), data, len, flags);
   }


   void udp_socket::SendToBuf(const in6_addr & a, port_t p, const char *data, int32_t len, int32_t flags)
   {
      SendToBuf(address(get_app(), a, p), data, len, flags);
   }


   void udp_socket::SendToBuf(const sockets::address & ad, const char *data, int32_t len, int32_t flags)
   {
      if (GetSocket() == INVALID_SOCKET)
      {
         attach(CreateSocket(ad.GetFamily(), SOCK_DGRAM, "udp"));
      }
      if (GetSocket() != INVALID_SOCKET)
      {
         SetNonblocking(true);
         if ((m_last_size_written = sendto(GetSocket(), data, len, flags, ad.sa(), (int32_t) ad.sa_len())) == -1)
         {
            Handler().LogError(this, "sendto", Errno, StrError(Errno), ::gen::log::level::error);
         }
      }
   }


   void udp_socket::SendTo(const string & a, port_t p, const string & str, int32_t flags)
   {
      SendToBuf(a, p, str, (int32_t)str.get_length(), flags);
   }


   void udp_socket::SendTo(in_addr a, port_t p, const string & str, int32_t flags)
   {
      SendToBuf(a, p, str, (int32_t)str.get_length(), flags);
   }


   void udp_socket::SendTo(in6_addr a, port_t p, const string & str, int32_t flags)
   {
      SendToBuf(a, p, str, (int32_t)str.get_length(), flags);
   }


   void udp_socket::SendTo(sockets::address& ad, const string & str, int32_t flags)
   {
      SendToBuf(ad, str, (int32_t)str.get_length(), flags);
   }


   /** send to connected address */
   void udp_socket::SendBuf(const char *data, size_t len, int32_t flags)
   {
      if (!IsConnected())
      {
         Handler().LogError(this, "SendBuf", 0, "not connected", ::gen::log::level::error);
         return;
      }
      if ((m_last_size_written = send(GetSocket(), data, (int32_t)len, flags)) == -1)
      {
         Handler().LogError(this, "send", Errno, StrError(Errno), ::gen::log::level::error);
      }
   }


   void udp_socket::Send(const string & str, int32_t flags)
   {
      SendBuf(str, (int32_t)str.get_length(), flags);
   }


   #if defined(LINUX) || defined(MACOSX)
   int32_t udp_socket::ReadTS(char *ioBuf, int32_t inBufSize, struct sockaddr *from, socklen_t fromlen, struct timeval *ts)
   {
      struct msghdr msg;
      struct iovec vec[1];
      union {
         struct cmsghdr cm;
   #ifdef MACOSX
   #ifdef __DARWIN_UNIX03
   #define ALIGNBYTES __DARWIN_ALIGNBYTES
   #endif
   #define myALIGN(p) (((uint32_t)(p) + ALIGNBYTES) &~ ALIGNBYTES)
   #define myCMSG_SPACE(l) (myALIGN(sizeof(struct cmsghdr)) + myALIGN(l))
         char data[ myCMSG_SPACE(sizeof(struct timeval)) ];
   #else
         char data[ CMSG_SPACE(sizeof(struct timeval)) ];
   #endif
      } cmsg_un;
      struct cmsghdr *cmsg;
      struct timeval *tv;

      vec[0].iov_base = ioBuf;
      vec[0].iov_len = inBufSize;

      memset(&msg, 0, sizeof(msg));
      memset(from, 0, fromlen);
      memset(ioBuf, 0, inBufSize);
      memset(&cmsg_un, 0, sizeof(cmsg_un));

#ifdef WINDOWS
      msg.msg_name = (caddr_t)from;
#else
      msg.msg_name = from;
#endif
      msg.msg_namelen = fromlen;
      msg.msg_iov = vec;
      msg.msg_iovlen = 1;
      msg.msg_control = cmsg_un.data;
      msg.msg_controllen = sizeof(cmsg_un.data);
      msg.msg_flags = 0;

      // Original version - for reference only
      //int32_t n = recvfrom(GetSocket(), m_ibuf, m_ibufsz, 0, (struct sockaddr *)&sa, &sa_len);

      int32_t n = recvmsg(GetSocket(), &msg, MSG_DONTWAIT);

      // now ioBuf will contain the data, as if we used recvfrom

      // Now get the time
      if(n != -1 && msg.msg_controllen >= sizeof(struct cmsghdr) && !(msg.msg_flags & MSG_CTRUNC))
      {
         tv = 0;
         for (cmsg = CMSG_FIRSTHDR(&msg); cmsg != NULL; cmsg = CMSG_NXTHDR(&msg, cmsg))
         {
            if (cmsg->cmsg_level == SOL_SOCKET && cmsg->cmsg_type == SCM_TIMESTAMP)
            {
               tv = (struct timeval *)CMSG_DATA(cmsg);
            }
         }
         if (tv)
         {
            memcpy(ts, tv, sizeof(struct timeval));
         }
      }
      // The address is in network order, but that's OK right now
      return n;
   }
   #endif


   void udp_socket::OnRead()
   {
      if (IsIpv6())
      {
         struct sockaddr_in6 sa;
         socklen_t sa_len = sizeof(sa);
         if (m_b_read_ts)
         {
            struct timeval ts;
            System.get_time(&ts);
   #if !defined(LINUX) && !defined(MACOSX)
            size_t n = recvfrom(GetSocket(), m_ibuf, m_ibufsz, 0, (struct sockaddr *)&sa, &sa_len);
   #else
            int32_t n = ReadTS(m_ibuf, m_ibufsz, (struct sockaddr *)&sa, sa_len, &ts);
   #endif
            if (n > 0)
            {
               this -> OnRawData(m_ibuf, n, (struct sockaddr *)&sa, sa_len, &ts);
            }
            else
            if (n == -1)
            {
   #ifdef _WIN32
               if (Errno != WSAEWOULDBLOCK)
   #else
               if (Errno != EWOULDBLOCK)
   #endif
                  Handler().LogError(this, "recvfrom", Errno, StrError(Errno), ::gen::log::level::error);
            }
            return;
         }
         size_t n = recvfrom(GetSocket(), m_ibuf, m_ibufsz, 0, (struct sockaddr *)&sa, &sa_len);
         int32_t q = m_retries; // receive max 10 at one cycle
         while (n > 0)
         {
            if (sa_len != sizeof(sa))
            {
               Handler().LogError(this, "recvfrom", 0, "unexpected address struct size", ::gen::log::level::warning);
            }
            this -> OnRawData(m_ibuf, n, (struct sockaddr *)&sa, sa_len);
            if (!q--)
               break;
            //
            n = recvfrom(GetSocket(), m_ibuf, m_ibufsz, 0, (struct sockaddr *)&sa, &sa_len);
         }
         if (n == -1)
         {
   #ifdef _WIN32
            if (Errno != WSAEWOULDBLOCK)
   #else
            if (Errno != EWOULDBLOCK)
   #endif
               Handler().LogError(this, "recvfrom", Errno, StrError(Errno), ::gen::log::level::error);
         }
         return;
      }
      struct sockaddr_in sa;
      socklen_t sa_len = sizeof(sa);
      if (m_b_read_ts)
      {
         struct timeval ts;
         System.get_time(&ts);
   #if !defined(LINUX) && !defined(MACOSX)
         size_t n = recvfrom(GetSocket(), m_ibuf, m_ibufsz, 0, (struct sockaddr *)&sa, &sa_len);
   #else
         int32_t n = ReadTS(m_ibuf, m_ibufsz, (struct sockaddr *)&sa, sa_len, &ts);
   #endif
         if (n > 0)
         {
            this -> OnRawData(m_ibuf, n, (struct sockaddr *)&sa, sa_len, &ts);
         }
         else
         if (n == -1)
         {
   #ifdef _WIN32
            if (Errno != WSAEWOULDBLOCK)
   #else
            if (Errno != EWOULDBLOCK)
   #endif
               Handler().LogError(this, "recvfrom", Errno, StrError(Errno), ::gen::log::level::error);
         }
         return;
      }
      size_t n = recvfrom(GetSocket(), m_ibuf, m_ibufsz, 0, (struct sockaddr *)&sa, &sa_len);
      int32_t q = m_retries;
      while (n > 0)
      {
         if (sa_len != sizeof(sa))
         {
            Handler().LogError(this, "recvfrom", 0, "unexpected address struct size", ::gen::log::level::warning);
         }
         this -> OnRawData(m_ibuf, n, (struct sockaddr *)&sa, sa_len);
         if (!q--)
            break;
         //
         n = recvfrom(GetSocket(), m_ibuf, m_ibufsz, 0, (struct sockaddr *)&sa, &sa_len);
      }
      if (n == -1)
      {
   #ifdef _WIN32
         if (Errno != WSAEWOULDBLOCK)
   #else
         if (Errno != EWOULDBLOCK)
   #endif
            Handler().LogError(this, "recvfrom", Errno, StrError(Errno), ::gen::log::level::error);
      }
   }


   void udp_socket::SetBroadcast(bool b)
   {
      int32_t one = 1;
      int32_t zero = 0;

      if (GetSocket() == INVALID_SOCKET)
      {
         CreateConnection();
      }
      if (b)
      {
         if (setsockopt(GetSocket(), SOL_SOCKET, SO_BROADCAST, (char *) &one, sizeof(one)) == -1)
         {
            Handler().LogError(this, "SetBroadcast", Errno, StrError(Errno), ::gen::log::level::warning);
         }
      }
      else
      {
         if (setsockopt(GetSocket(), SOL_SOCKET, SO_BROADCAST, (char *) &zero, sizeof(zero)) == -1)
         {
            Handler().LogError(this, "SetBroadcast", Errno, StrError(Errno), ::gen::log::level::warning);
         }
      }
   }


   bool udp_socket::IsBroadcast()
   {
      int32_t is_broadcast = 0;
      socklen_t size;

      if (GetSocket() == INVALID_SOCKET)
      {
         CreateConnection();
      }
      if (getsockopt(GetSocket(), SOL_SOCKET, SO_BROADCAST, (char *)&is_broadcast, &size) == -1)
      {
         Handler().LogError(this, "IsBroadcast", Errno, StrError(Errno), ::gen::log::level::warning);
      }
      return is_broadcast != 0;
   }


   void udp_socket::SetMulticastTTL(int32_t ttl)
   {
      if (GetSocket() == INVALID_SOCKET)
      {
         CreateConnection();
      }
      if (setsockopt(GetSocket(), SOL_IP, IP_MULTICAST_TTL, (char *)&ttl, sizeof(int32_t)) == -1)
      {
         Handler().LogError(this, "SetMulticastTTL", Errno, StrError(Errno), ::gen::log::level::warning);
      }
   }


   int32_t udp_socket::GetMulticastTTL()
   {
      int32_t ttl = 0;
      socklen_t size = sizeof(int32_t);

      if (GetSocket() == INVALID_SOCKET)
      {
         CreateConnection();
      }
      if (getsockopt(GetSocket(), SOL_IP, IP_MULTICAST_TTL, (char *)&ttl, &size) == -1)
      {
         Handler().LogError(this, "GetMulticastTTL", Errno, StrError(Errno), ::gen::log::level::warning);
      }
      return ttl;
   }


   void udp_socket::SetMulticastLoop(bool x)
   {
      if (GetSocket() == INVALID_SOCKET)
      {
         CreateConnection();
      }
      if (IsIpv6())
      {
         int32_t val = x ? 1 : 0;
         if (setsockopt(GetSocket(), IPPROTO_IPV6, IPV6_MULTICAST_LOOP, (char *)&val, sizeof(int32_t)) == -1)
         {
            Handler().LogError(this, "SetMulticastLoop", Errno, StrError(Errno), ::gen::log::level::warning);
         }
         return;
      }
      int32_t val = x ? 1 : 0;
      if (setsockopt(GetSocket(), SOL_IP, IP_MULTICAST_LOOP, (char *)&val, sizeof(int32_t)) == -1)
      {
         Handler().LogError(this, "SetMulticastLoop", Errno, StrError(Errno), ::gen::log::level::warning);
      }
   }


   bool udp_socket::IsMulticastLoop()
   {
      if (GetSocket() == INVALID_SOCKET)
      {
         CreateConnection();
      }
      if (IsIpv6())
      {
         int32_t is_loop = 0;
         socklen_t size = sizeof(int32_t);
         if (getsockopt(GetSocket(), IPPROTO_IPV6, IPV6_MULTICAST_LOOP, (char *)&is_loop, &size) == -1)
         {
            Handler().LogError(this, "IsMulticastLoop", Errno, StrError(Errno), ::gen::log::level::warning);
         }
         return is_loop ? true : false;
      }
      int32_t is_loop = 0;
      socklen_t size = sizeof(int32_t);
      if (getsockopt(GetSocket(), SOL_IP, IP_MULTICAST_LOOP, (char *)&is_loop, &size) == -1)
      {
         Handler().LogError(this, "IsMulticastLoop", Errno, StrError(Errno), ::gen::log::level::warning);
      }
      return is_loop ? true : false;
   }


   void udp_socket::AddMulticastMembership(const string & group, const string & local_if, int32_t if_index)
   {
      if (GetSocket() == INVALID_SOCKET)
      {
         CreateConnection();
      }
      if (IsIpv6())
      {
         struct ipv6_mreq x;
         struct in6_addr addr;
         if (System.net().convert( addr, group ))
         {
            x.ipv6mr_multiaddr = addr;
            x.ipv6mr_interface = if_index;
            if (setsockopt(GetSocket(), IPPROTO_IPV6, IPV6_ADD_MEMBERSHIP, (char *)&x, sizeof(struct ipv6_mreq)) == -1)
            {
               Handler().LogError(this, "AddMulticastMembership", Errno, StrError(Errno), ::gen::log::level::warning);
            }
         }
         return;
      }
      struct ip_mreq x; // ip_mreqn
      in_addr addr;
      if (System.net().convert(addr,  group ))
      {
         memcpy(&x.imr_multiaddr.s_addr, &addr, sizeof(addr));
         System.net().convert(addr,  local_if);
         memcpy(&x.imr_interface.s_addr, &addr, sizeof(addr));
   //      x.imr_ifindex = if_index;
         if (setsockopt(GetSocket(), SOL_IP, IP_ADD_MEMBERSHIP, (char *)&x, sizeof(struct ip_mreq)) == -1)
         {
            Handler().LogError(this, "AddMulticastMembership", Errno, StrError(Errno), ::gen::log::level::warning);
         }
      }
   }


   void udp_socket::DropMulticastMembership(const string & group, const string & local_if, int32_t if_index)
   {
      if (GetSocket() == INVALID_SOCKET)
      {
         CreateConnection();
      }
      if (IsIpv6())
      {
         struct ipv6_mreq x;
         struct in6_addr addr;
         if (System.net().convert(addr, group))
         {
            x.ipv6mr_multiaddr = addr;
            x.ipv6mr_interface = if_index;
            if (setsockopt(GetSocket(), IPPROTO_IPV6, IPV6_DROP_MEMBERSHIP, (char *)&x, sizeof(struct ipv6_mreq)) == -1)
            {
               Handler().LogError(this, "DropMulticastMembership", Errno, StrError(Errno), ::gen::log::level::warning);
            }
         }
         return;
      }
      struct ip_mreq x; // ip_mreqn
      in_addr addr;
      if (System.net().convert(addr, group))
      {
         memcpy(&x.imr_multiaddr.s_addr, &addr, sizeof(addr));
         System.net().convert(addr, local_if);
         memcpy(&x.imr_interface.s_addr, &addr, sizeof(addr));
   //      x.imr_ifindex = if_index;
         if (setsockopt(GetSocket(), SOL_IP, IP_DROP_MEMBERSHIP, (char *)&x, sizeof(struct ip_mreq)) == -1)
         {
            Handler().LogError(this, "DropMulticastMembership", Errno, StrError(Errno), ::gen::log::level::warning);
         }
      }
   }


   void udp_socket::SetMulticastHops(int32_t hops)
   {
      if (GetSocket() == INVALID_SOCKET)
      {
         CreateConnection();
      }
      if (!IsIpv6())
      {
         Handler().LogError(this, "SetMulticastHops", 0, "Ipv6 only", ::gen::log::level::error);
         return;
      }
      if (setsockopt(GetSocket(), IPPROTO_IPV6, IPV6_MULTICAST_HOPS, (char *)&hops, sizeof(int32_t)) == -1)
      {
         Handler().LogError(this, "SetMulticastHops", Errno, StrError(Errno), ::gen::log::level::warning);
      }
   }


   int32_t udp_socket::GetMulticastHops()
   {
      if (GetSocket() == INVALID_SOCKET)
      {
         CreateConnection();
      }
      if (!IsIpv6())
      {
         Handler().LogError(this, "SetMulticastHops", 0, "Ipv6 only", ::gen::log::level::error);
         return -1;
      }
      int32_t hops = 0;
      socklen_t size = sizeof(int32_t);
      if (getsockopt(GetSocket(), IPPROTO_IPV6, IPV6_MULTICAST_HOPS, (char *)&hops, &size) == -1)
      {
         Handler().LogError(this, "GetMulticastHops", Errno, StrError(Errno), ::gen::log::level::warning);
      }
      return hops;
   }


   bool udp_socket::IsBound()
   {
      return m_bind_ok;
   }


   void udp_socket::OnRawData(char * buf, size_t len, struct sockaddr * sa, socklen_t sa_len)
   {
      UNREFERENCED_PARAMETER(buf);
      UNREFERENCED_PARAMETER(len);
      UNREFERENCED_PARAMETER(sa);
      UNREFERENCED_PARAMETER(sa_len);
   }


   void udp_socket::OnRawData(char * buf, size_t len, struct sockaddr * sa, socklen_t sa_len, struct timeval * ts)
   {
      UNREFERENCED_PARAMETER(buf);
      UNREFERENCED_PARAMETER(len);
      UNREFERENCED_PARAMETER(sa);
      UNREFERENCED_PARAMETER(sa_len);
      UNREFERENCED_PARAMETER(ts);
   }


   port_t udp_socket::GetPort()
   {
      return m_port;
   }


   size_t udp_socket::GetLastSizeWritten()
   {
      return m_last_size_written;
   }


   void udp_socket::SetTimestamp(bool x)
   {
      m_b_read_ts = x;
   }


}




