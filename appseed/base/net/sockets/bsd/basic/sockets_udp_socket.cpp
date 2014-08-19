#include "framework.h"


namespace sockets
{


   udp_socket::udp_socket(base_socket_handler& h, int32_t ibufsz, bool ipv6, int32_t retries) : 
      element(h.get_app())
      ,base_socket(h)
      ,socket(h)
   , m_ibuf(new char[ibufsz])
   , m_ibufsz(ibufsz)
   , m_bind_ok(false)
   , m_port(0)
   , m_last_size_written(-1)
   , m_retries(retries)
   , m_b_read_ts(false)
   {
      m_iWriteFlags = 0;
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
         ::net::address ad(AF_INET6, port);
         return Bind((in6_addr) ad.u.m_addr6.sin6_addr, ad.u.m_addr6.sin6_port, range);
      }
      ::net::address ad(AF_INET, port);
      return Bind((in_addr)  ad.u.m_addr.sin_addr, ad.u.m_addr.sin_port, range);
   }


   int32_t udp_socket::Bind(const string & intf, port_t &port, int32_t range)
   {

      ::net::address ad(intf, port);
      
      if (ad.is_valid())
      {
         if(ad.is_ipv6())
         {
            return Bind((in6_addr) ad.u.m_addr6.sin6_addr, ad.u.m_addr6.sin6_port, range);
         }
         else if(ad.is_ipv4())
         {
            return Bind((in_addr)  ad.u.m_addr.sin_addr, ad.u.m_addr.sin_port, range);
         }

      }
         
      SetCloseAndDelete();

      return -1;

   }


   int32_t udp_socket::Bind(in_addr a, port_t &port, int32_t range)
   {
      ::net::address ad(a, port);
      return Bind(ad, range);
   }


   int32_t udp_socket::Bind(in6_addr a, port_t &port, int32_t range)
   {
      ::net::address ad(a, port);
      return Bind(ad, range);
   }


   int32_t udp_socket::Bind(::net::address & ad, int32_t range)
   {
      if (GetSocket() == INVALID_SOCKET)
      {
         attach(CreateSocket(ad.get_family(), SOCK_DGRAM, "udp"));
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
            log("bind", Errno, StrError(Errno), ::axis::log::level_fatal);
            SetCloseAndDelete();
            throw simple_exception(get_app(), "bind() failed for udp_socket, port:range: " + ::str::from(ad.get_service_number()) + ":" + ::str::from(range));
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
      ::net::address ad(l, port);
      return open(ad);
   }


   bool udp_socket::open(const string & host, port_t port)
   {
      ::net::address ad(host, port);
      if(!ad.is_valid())
         return false;
      return open(ad);
   }


   bool udp_socket::open(struct in6_addr& a, port_t port)
   {
     ::net::address ad(a, port);
      return open(ad);
   }


   bool udp_socket::open(const ::net::address & ad)
   {
      if (GetSocket() == INVALID_SOCKET)
      {
         attach(CreateSocket(ad.get_family(), SOCK_DGRAM, "udp"));
      }
      if (GetSocket() != INVALID_SOCKET)
      {
         SetNonblocking(true);
         if (connect(GetSocket(), ad.sa(), ad.sa_len()) == -1)
         {
            log("connect", Errno, StrError(Errno), ::axis::log::level_fatal);
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
      SendToBuf(::net::address(h, p), data, len, flags);
   }


   /** send to specified address */
   void udp_socket::SendToBuf(const in_addr & a, port_t p, const char *data, int32_t len, int32_t flags)
   {
      SendToBuf(::net::address(a, p), data, len, flags);
   }


   void udp_socket::SendToBuf(const in6_addr & a, port_t p, const char *data, int32_t len, int32_t flags)
   {
      SendToBuf(::net::address(a, p), data, len, flags);
   }


   void udp_socket::SendToBuf(const ::net::address & ad, const char *data, int32_t len, int32_t flags)
   {
      if (GetSocket() == INVALID_SOCKET)
      {
         attach(CreateSocket(ad.get_family(), SOCK_DGRAM, "udp"));
      }
      if (GetSocket() != INVALID_SOCKET)
      {
         SetNonblocking(true);
         if ((m_last_size_written = sendto(GetSocket(), data, len, flags, ad.sa(), (int32_t) ad.sa_len())) == -1)
         {
            log("sendto", Errno, StrError(Errno), ::axis::log::level_error);
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


   void udp_socket::SendTo(const ::net::address & ad, const string & str, int32_t flags)
   {
      SendToBuf(ad, str, (int32_t)str.get_length(), flags);
   }


   /** send to connected address */
   void udp_socket::write(const void *data, ::primitive::memory_size len)
   {
      
      if (!IsConnected())
      {

         log("write", 0, "not connected", ::axis::log::level_error);

         return;

      }
      
      if ((m_last_size_written = send(GetSocket(), (const char *) data, (int32_t)len, m_iWriteFlags)) == -1)
      {

         log("write", Errno, StrError(Errno), ::axis::log::level_error);

      }

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
                  log("recvfrom", Errno, StrError(Errno), ::axis::log::level_error);
            }
            return;
         }
         size_t n = recvfrom(GetSocket(), m_ibuf, m_ibufsz, 0, (struct sockaddr *)&sa, &sa_len);
         int32_t q = m_retries; // receive MAX 10 at one cycle
         while (n > 0)
         {
            if (sa_len != sizeof(sa))
            {
               log("recvfrom", 0, "unexpected address struct size", ::axis::log::level_warning);
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
               log("recvfrom", Errno, StrError(Errno), ::axis::log::level_error);
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
               log("recvfrom", Errno, StrError(Errno), ::axis::log::level_error);
         }
         return;
      }
      size_t n = recvfrom(GetSocket(), m_ibuf, m_ibufsz, 0, (struct sockaddr *)&sa, &sa_len);
      int32_t q = m_retries;
      while (n > 0)
      {
         if (sa_len != sizeof(sa))
         {
            log("recvfrom", 0, "unexpected address struct size", ::axis::log::level_warning);
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
            log("recvfrom", Errno, StrError(Errno), ::axis::log::level_error);
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
            log("SetBroadcast", Errno, StrError(Errno), ::axis::log::level_warning);
         }
      }
      else
      {
         if (setsockopt(GetSocket(), SOL_SOCKET, SO_BROADCAST, (char *) &zero, sizeof(zero)) == -1)
         {
            log("SetBroadcast", Errno, StrError(Errno), ::axis::log::level_warning);
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
         log("IsBroadcast", Errno, StrError(Errno), ::axis::log::level_warning);
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
         log("SetMulticastTTL", Errno, StrError(Errno), ::axis::log::level_warning);
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
         log("GetMulticastTTL", Errno, StrError(Errno), ::axis::log::level_warning);
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
            log("SetMulticastLoop", Errno, StrError(Errno), ::axis::log::level_warning);
         }
         return;
      }
      int32_t val = x ? 1 : 0;
      if (setsockopt(GetSocket(), SOL_IP, IP_MULTICAST_LOOP, (char *)&val, sizeof(int32_t)) == -1)
      {
         log("SetMulticastLoop", Errno, StrError(Errno), ::axis::log::level_warning);
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
            log("IsMulticastLoop", Errno, StrError(Errno), ::axis::log::level_warning);
         }
         return is_loop ? true : false;
      }
      int32_t is_loop = 0;
      socklen_t size = sizeof(int32_t);
      if (getsockopt(GetSocket(), SOL_IP, IP_MULTICAST_LOOP, (char *)&is_loop, &size) == -1)
      {
         log("IsMulticastLoop", Errno, StrError(Errno), ::axis::log::level_warning);
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
               log("AddMulticastMembership", Errno, StrError(Errno), ::axis::log::level_warning);
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
            log("AddMulticastMembership", Errno, StrError(Errno), ::axis::log::level_warning);
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
               log("DropMulticastMembership", Errno, StrError(Errno), ::axis::log::level_warning);
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
            log("DropMulticastMembership", Errno, StrError(Errno), ::axis::log::level_warning);
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
         log("SetMulticastHops", 0, "Ipv6 only", ::axis::log::level_error);
         return;
      }
      if (setsockopt(GetSocket(), IPPROTO_IPV6, IPV6_MULTICAST_HOPS, (char *)&hops, sizeof(int32_t)) == -1)
      {
         log("SetMulticastHops", Errno, StrError(Errno), ::axis::log::level_warning);
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
         log("SetMulticastHops", 0, "Ipv6 only", ::axis::log::level_error);
         return -1;
      }
      int32_t hops = 0;
      socklen_t size = sizeof(int32_t);
      if (getsockopt(GetSocket(), IPPROTO_IPV6, IPV6_MULTICAST_HOPS, (char *)&hops, &size) == -1)
      {
         log("GetMulticastHops", Errno, StrError(Errno), ::axis::log::level_warning);
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




