#include "framework.h"

#if defined(LINUX) || defined(MACOS)
#if defined(MACOS)
#define	NI_MAXHOST	1025
#define	NI_MAXSERV	32
#endif
#define __USE_MISC
#include <ctype.h>
#include <sys/socket.h>
#include <netdb.h>
#endif


   namespace sockets
   {

      net::net(::ca::application * papp) :
         ca(papp),
         m_mutexCache(papp)
      {

      }

      net::~net()
      {

      }


      /*
      * Encode string per RFC1738 URL encoding rules
      * tnx rstaveley
      */
      string net::rfc1738_encode(const string & src)
      {
         static   char hex[] = "0123456789ABCDEF";
         string dst;
         for (int i = 0; i < src.get_length(); i++)
         {
            if (isalnum((unsigned char) src[i]))
            {
               dst += src[i];
            }
            else
               if (src[i] == ' ')
               {
                  dst += '+';
               }
               else
               {
                  unsigned char c = static_cast<unsigned char>(src[i]);
                  dst += '%';
                  dst += hex[c / 16];
                  dst += hex[c % 16];
               }
         }
         return dst;
      } // rfc1738_encode


      /*
      * Decode string per RFC1738 URL encoding rules
      * tnx rstaveley
      */
      string net::rfc1738_decode(const string & src)
      {
         string dst;
         for (int i = 0; i < src.get_length(); i++)
         {
            if (src[i] == '%' && isxdigit((unsigned char) (src[i + 1])) && isxdigit((unsigned char) (src[i + 2])))
            {
               char c1 = src[++i];
               char c2 = src[++i];
               c1 = c1 - 48 - ((c1 >= 'A') ? 7 : 0) - ((c1 >= 'a') ? 32 : 0);
               c2 = c2 - 48 - ((c2 >= 'A') ? 7 : 0) - ((c2 >= 'a') ? 32 : 0);
               dst += (char)(c1 * 16 + c2);
            }
            else
               if (src[i] == '+')
               {
                  dst += ' ';
               }
               else
               {
                  dst += src[i];
               }
         }
         return dst;
      } // rfc1738_decode


      bool net::isipv4(const string & str)
      {
         int dots = 0;
         // %! ignore :port?
         for (int i = 0; i < str.get_length(); i++)
         {
            if (str[i] == '.')
               dots++;
            else
               if (!isdigit((unsigned char) str[i]))
                  return false;
         }
         if (dots != 3)
            return false;
         return true;
      }


      bool net::isipv6(const string & str)
      {
         index qc = 0;
         index qd = 0;
         for (int i = 0; i < str.get_length(); i++)
         {
            qc += (str[i] == ':') ? 1 : 0;
            qd += (str[i] == '.') ? 1 : 0;
         }
         if (qc > 7)
         {
            return false;
         }
         if (qd && qd != 3)
         {
            return false;
         }
         ::gen::parse pa(str,":.");
         string tmp = pa.getword();
         while (tmp.get_length())
         {
            if (tmp.get_length() > 4)
            {
               return false;
            }
            for (int i = 0; i < tmp.get_length(); i++)
            {
               if (tmp[i] < '0' || (tmp[i] > '9' && tmp[i] < 'A') ||
                  (tmp[i] > 'F' && tmp[i] < 'a') || tmp[i] > 'f')
               {
                  return false;
               }
            }
            //
            tmp = pa.getword();
         }
         return true;
      }

#ifdef BSD_STYLE_SOCKETS

      bool net::u2ip(const string & str, ipaddr_t& l, int ai_flags)
      {
         DWORD dwTimeTelmo1 = get_tick_count();

         single_lock sl(&m_mutexCache, true);
         dns_cache_item * pitem = NULL;
         if(m_mapCache.Lookup(str, pitem) && ((::get_tick_count() - pitem->m_dwLastChecked) < (((84 + 77) * 1000))))
         {
            l = pitem->m_ipaddr;
            //         DWORD dwTimeTelmo2 = get_tick_count();
            /*TRACE("Got from cache net::u2ip " + str + " : %d.%d.%d.%d (%d ms)",
            (DWORD)((byte*)&pitem->m_ipaddr)[0],
            (DWORD)((byte*)&pitem->m_ipaddr)[1],
            (DWORD)((byte*)&pitem->m_ipaddr)[2],
            (DWORD)((byte*)&pitem->m_ipaddr)[3],
            (dwTimeTelmo2 - dwTimeTelmo1));*/
            return pitem->r;
         }
         if(pitem == NULL)
            pitem = new dns_cache_item;
         struct sockaddr_in sa;
         pitem->r = u2ip(str, sa, ai_flags);
         memcpy(&l, &sa.sin_addr, sizeof(l));
         pitem->m_ipaddr = l;
         pitem->m_dwLastChecked = ::get_tick_count();
         m_mapCache.set_at(str, pitem);
         DWORD dwTimeTelmo2 = get_tick_count();
         TRACE("DNS Lookup net::u2ip " + str + " : %d.%d.%d.%d (%d ms)",
            (DWORD)((byte*)&pitem->m_ipaddr)[0],
            (DWORD)((byte*)&pitem->m_ipaddr)[1],
            (DWORD)((byte*)&pitem->m_ipaddr)[2],
            (DWORD)((byte*)&pitem->m_ipaddr)[3],
            (dwTimeTelmo2 - dwTimeTelmo1));
         return pitem->r;
      }


      bool net::u2ip(const string & str, struct in6_addr& l, int ai_flags)
      {
         struct sockaddr_in6 sa;
         bool r = net::u2ip(str, sa, ai_flags);
         l = sa.sin6_addr;
         return r;
      }


      void net::l2ip(const ipaddr_t ip, string & str)
      {
         struct sockaddr_in sa;
         memset(&sa, 0, sizeof(sa));
         sa.sin_family = AF_INET;
         memcpy(&sa.sin_addr, &ip, sizeof(sa.sin_addr));
         net::reverse( (struct sockaddr *)&sa, sizeof(sa), str, NI_NUMERICHOST);
      }


      void net::l2ip(const in_addr& ip, string & str)
      {
         struct sockaddr_in sa;
         memset(&sa, 0, sizeof(sa));
         sa.sin_family = AF_INET;
         sa.sin_addr = ip;
         net::reverse( (struct sockaddr *)&sa, sizeof(sa), str, NI_NUMERICHOST);
      }


      void net::l2ip(const struct in6_addr& ip, string & str,bool mixed)
      {
         char slask[100]; // l2ip temporary
         *slask = 0;
         unsigned int prev = 0;
         bool skipped = false;
         bool ok_to_skip = true;
         if (mixed)
         {
            unsigned short x;
            unsigned short addr16[8];
            memcpy(addr16, &ip, sizeof(addr16));
            for (index i = 0; i < 6; i++)
            {
               x = ntohs(addr16[i]);
               if (*slask && (x || !ok_to_skip || prev))
                  strcat(slask,":");
               if (x || !ok_to_skip)
               {
                  sprintf(slask + strlen(slask),"%x", x);
                  if (x && skipped)
                     ok_to_skip = false;
               }
               else
               {
                  skipped = true;
               }
               prev = x;
            }
            x = ntohs(addr16[6]);
            sprintf(slask + strlen(slask),":%u.%u",x / 256,x & 255);
            x = ntohs(addr16[7]);
            sprintf(slask + strlen(slask),".%u.%u",x / 256,x & 255);
         }
         else
         {
            struct sockaddr_in6 sa;
            memset(&sa, 0, sizeof(sa));
            sa.sin6_family = AF_INET6;
            sa.sin6_addr = ip;
            net::reverse( (struct sockaddr *)&sa, sizeof(sa), str, NI_NUMERICHOST);
            return;
         }
         str = slask;
      }


      int net::in6_addr_compare(in6_addr a,in6_addr b)
      {
         for (index i = 0; i < 16; i++)
         {
            if (a.s6_addr[i] < b.s6_addr[i])
               return -1;
            if (a.s6_addr[i] > b.s6_addr[i])
               return 1;
         }
         return 0;
      }

#endif

      void net::ResolveLocal()
      {

#ifdef METROWIN

         //Retrieve the ConnectionProfile
         ::Windows::Networking::Connectivity::ConnectionProfile^ InternetConnectionProfile = Windows::Networking::Connectivity::NetworkInformation::GetInternetConnectionProfile();

         if(InternetConnectionProfile == nullptr)
            return;

         if(InternetConnectionProfile->NetworkAdapter == nullptr)
            return;

         //Pass the returned object to a function that accesses the connection data        
         //::Platform::String^ strConnectionProfileInfo = GetConnectionProfileInfo(InternetConnectionProfile);

         //Windows::Networking::Connectivity::NetworkAdapter ^ adp = InternetConnectionProfile->NetworkAdapter();

         ::Windows::Foundation::Collections::IVectorView < ::Windows::Networking::HostName ^ > ^ names = ::Windows::Networking::Connectivity::NetworkInformation::GetHostNames();

         //strProfileInfo += connectionProfile->NetworkAdapter->NetworkAdapterId;
         //strProfileInfo += "\n";


         for(unsigned int ui = 0; ui < names->Size; ui++)
         {
            ::Windows::Networking::HostName ^ name = names->GetAt(ui);
            if(name == nullptr)
               continue;
            if(name->IPInformation == nullptr)
               continue;
            if(name->IPInformation->NetworkAdapter == nullptr)
               continue;
            if(name->IPInformation->NetworkAdapter->NetworkAdapterId == InternetConnectionProfile->NetworkAdapter->NetworkAdapterId)
            {
               // there may be more than one local address though
               m_host = begin(name->CanonicalName);
               m_local_resolved = true;
               break;
            }
         }




#else
         char h[256];

         // get local hostname and translate into ip-address
         *h = 0;
         gethostname(h,255);
         {
            if (net::u2ip(h, m_ip))
            {
               net::l2ip(m_ip, m_addr);
            }
         }
#ifdef ENABLE_IPV6
#ifdef IPPROTO_IPV6
         memset(&m_local_ip6, 0, sizeof(m_local_ip6));
         {
            if (net::u2ip(h, m_local_ip6))
            {
               net::l2ip(m_local_ip6, m_local_addr6);
            }
         }
#endif
#endif
         m_host = h;
         m_local_resolved = true;

#endif

      }


      const string & net::GetLocalHostname()
      {
         if (!m_local_resolved)
         {
            ResolveLocal();
         }
         return m_host;
      }


      ipaddr_t net::GetLocalIP()
      {
         if (!m_local_resolved)
         {
            ResolveLocal();
         }
         return m_ip;
      }


      const string & net::GetLocalAddress()
      {
         if (!m_local_resolved)
         {
            ResolveLocal();
         }
         return m_addr;
      }


      const struct in6_addr& net::GetLocalIP6()
      {
         if (!m_local_resolved)
         {
            ResolveLocal();
         }
         return m_local_ip6;
      }


      const string & net::GetLocalAddress6()
      {
         if (!m_local_resolved)
         {
            ResolveLocal();
         }
         return m_local_addr6;
      }

      string net::Sa2String(struct sockaddr *sa)
      {
         if (sa -> sa_family == AF_INET6)
         {
            struct sockaddr_in6 *sa6 = (struct sockaddr_in6 *)sa;
            string tmp;
            net::l2ip(sa6 -> sin6_addr, tmp);
            return tmp + ":" + gen::str::from(ntohs(sa6 -> sin6_port));
         }
         if (sa -> sa_family == AF_INET)
         {
            struct sockaddr_in *sa4 = (struct sockaddr_in *)sa;
            ipaddr_t a;
            memcpy(&a, &sa4 -> sin_addr, 4);
            string tmp;
            net::l2ip(a, tmp);
            return tmp + ":" + gen::str::from(ntohs(sa4 -> sin_port));
         }
         return "";
      }



      ::sockets::address_sp net::CreateAddress(struct sockaddr *sa,socklen_t sa_len)
      {
         switch (sa -> sa_family)
         {
         case AF_INET:
            if (sa_len == sizeof(struct sockaddr_in))
            {
               struct sockaddr_in *p = (struct sockaddr_in *)sa;
               ::sockets::address_sp addr;
               addr(new ::sockets::ipv4_address(get_app(), *p));
               return addr;
            }
            break;
         case AF_INET6:
            if (sa_len == sizeof(struct sockaddr_in6))
            {
               struct sockaddr_in6 *p = (struct sockaddr_in6 *)sa;
               ::sockets::address_sp addr;
               addr(new ::sockets::ipv6_address(get_app(), *p));
               return addr;
            }
            break;
         }
         return ::sockets::address_sp();
      }


      bool net::u2ip(const string & host, struct sockaddr_in& sa, int ai_flags)
      {

#ifdef METROWIN


         ::Windows::Foundation::Collections::IVectorView < ::Windows::Networking::EndpointPair ^ > ^ data = ::wait(::Windows::Networking::Sockets::DatagramSocket::GetEndpointPairsAsync(ref new ::Windows::Networking::HostName(rtstr(host)), "0"));

         if(data->Size <= 0)
            return false;

         string str = begin(data->GetAt(0)->RemoteHostName->DisplayName); 

         if(!net::isipv4(str))
            return false;

         stringa stra;

         stra.explode(".", str);

         if(stra.get_size() != 4)
            return false;

         sa.sin_addr.S_un.S_un_b.s_b1 = gen::str::to_int(stra[0]);
         sa.sin_addr.S_un.S_un_b.s_b2 = gen::str::to_int(stra[1]);
         sa.sin_addr.S_un.S_un_b.s_b3 = gen::str::to_int(stra[2]);
         sa.sin_addr.S_un.S_un_b.s_b4 = gen::str::to_int(stra[3]);

         return true;

#else
         memset(&sa, 0, sizeof(sa));
         sa.sin_family = AF_INET;
#ifdef NO_GETADDRINFO
         if ((ai_flags & AI_NUMERICHOST) != 0 || isipv4(host))
         {
            ::gen::parse pa((const char *)host, ".");
            union {
               struct {
                  unsigned char b1;
                  unsigned char b2;
                  unsigned char b3;
                  unsigned char b4;
               } a;
               ipaddr_t l;
            } u;
            u.a.b1 = static_cast<unsigned char>(pa.getvalue());
            u.a.b2 = static_cast<unsigned char>(pa.getvalue());
            u.a.b3 = static_cast<unsigned char>(pa.getvalue());
            u.a.b4 = static_cast<unsigned char>(pa.getvalue());
            memcpy(&sa.sin_addr, &u.l, sizeof(sa.sin_addr));
            return true;
         }
#ifndef LINUX
         struct hostent *he = gethostbyname( host );
         if (!he)
         {
            return false;
         }
         memcpy(&sa.sin_addr, he -> h_addr, sizeof(sa.sin_addr));
#else
         struct hostent he;
         struct hostent *result = NULL;
         int myerrno = 0;
         char buf[2000];
         int n = gethostbyname_r(host, &he, buf, sizeof(buf), &result, &myerrno);
         if (n || !result)
         {
            return false;
         }
         if (he.h_addr_list && he.h_addr_list[0])
            memcpy(&sa.sin_addr, he.h_addr, 4);
         else
            return false;
#endif
         return true;
#else
         struct addrinfo hints;
         memset(&hints, 0, sizeof(hints));
         // AI_NUMERICHOST
         // AI_CANONNAME
         // AI_PASSIVE - server
         // AI_ADDRCONFIG
         // AI_V4MAPPED
         // AI_ALL
         // AI_NUMERICSERV
         hints.ai_flags = ai_flags;
         hints.ai_family = AF_INET;
         hints.ai_socktype = 0;
         hints.ai_protocol = 0;
         struct addrinfo *res;
         if (net::isipv4(host))
            hints.ai_flags |= AI_NUMERICHOST;
         int n = getaddrinfo(host, NULL, &hints, &res);
         if (!n)
         {
            comparable_array < addrinfo * > vec;
            addrinfo *ai = res;
            while (ai)
            {
               if (ai -> ai_addrlen == sizeof(sa))
                  vec.add( ai );
               ai = ai -> ai_next;
            }
            if (!vec.get_count())
               return false;
            ai = vec[System.math().rnd() % vec.get_count()];
            {
               memcpy(&sa, ai -> ai_addr, ai -> ai_addrlen);
            }
            freeaddrinfo(res);
            return true;
         }
         string error = "Error: ";
#ifndef __CYGWIN__
         error += gai_strerror(n);
#endif
         return false;
#endif // NO_GETADDRINFO
#endif
      }


      bool net::u2ip(const string & host, struct sockaddr_in6& sa, int ai_flags)
      {

#ifdef METROWIN


         ::Windows::Foundation::Collections::IVectorView < ::Windows::Networking::EndpointPair ^ > ^ data = ::wait(::Windows::Networking::Sockets::DatagramSocket::GetEndpointPairsAsync(ref new ::Windows::Networking::HostName(rtstr(host)), "0"));

         if(data->Size <= 0)
            return false;

         string str = begin(data->GetAt(0)->RemoteHostName->DisplayName); 

         if(!net::isipv6(str))
            return false;

         from_string(&sa.sin6_addr, str);

         return true;

#else
         memset(&sa, 0, sizeof(sa));
         sa.sin6_family = AF_INET6;
#ifdef NO_GETADDRINFO
         if ((ai_flags & AI_NUMERICHOST) != 0 || isipv6(host))
         {
            //         list<string> vec;
            index x = 0;
            for (index i = 0; i <= host.get_length(); i++)
            {
               if (i == host.get_length() || host[i] == ':')
               {
                  string s = host.Mid(x, i - x);
                  //
                  if (strstr(s,".")) // x.x.x.x
                  {
                     Parse pa(s,".");
                     char slask[100]; // u2ip temporary hex2string conversion
                     unsigned long b0 = static_cast<unsigned long>(pa.getvalue());
                     unsigned long b1 = static_cast<unsigned long>(pa.getvalue());
                     unsigned long b2 = static_cast<unsigned long>(pa.getvalue());
                     unsigned long b3 = static_cast<unsigned long>(pa.getvalue());
                     sprintf(slask,"%lx",b0 * 256 + b1);
                     vec.push_back(slask);
                     sprintf(slask,"%lx",b2 * 256 + b3);
                     vec.push_back(slask);
                  }
                  else
                  {
                     vec.push_back(s);
                  }
                  //
                  x = i + 1;
               }
            }
            index sz = vec.get_length(); // number of byte pairs
            index i = 0; // index in in6_addr.in6_u.u6_addr16[] ( 0 .. 7 )
            unsigned short addr16[8];
            for (list<string>::iterator it = vec.begin(); it != vec.end(); it++)
            {
               string bytepair = *it;
               if (bytepair.get_length())
               {
                  addr16[i++] = htons(net::hex2unsigned(bytepair));
               }
               else
               {
                  addr16[i++] = 0;
                  while (sz++ < 8)
                  {
                     addr16[i++] = 0;
                  }
               }
            }
            memcpy(&sa.sin6_addr, addr16, sizeof(addr16));
            return true;
         }
#ifdef SOLARIS
         int errnum = 0;
         struct hostent *he = getipnodebyname( host, AF_INET6, 0, &errnum );
#else
         struct hostent *he = gethostbyname2( host, AF_INET6 );
#endif
         if (!he)
         {
            return false;
         }
         memcpy(&sa.sin6_addr,he -> h_addr_list[0],he -> h_length);
#ifdef SOLARIS
         free(he);
#endif
         return true;
#else
         struct addrinfo hints;
         memset(&hints, 0, sizeof(hints));
         hints.ai_flags = ai_flags;
         hints.ai_family = AF_INET6;
         hints.ai_socktype = 0;
         hints.ai_protocol = 0;
         struct addrinfo *res;
         if (net::isipv6(host))
            hints.ai_flags |= AI_NUMERICHOST;
         int n = getaddrinfo(host, NULL, &hints, &res);
         if (!n)
         {
            comparable_array < addrinfo * > vec;
            struct addrinfo *ai = res;
            while (ai)
            {
               if (ai -> ai_addrlen == sizeof(sa))
                  vec.add( ai );
               ai = ai -> ai_next;
            }
            if (!vec.get_count())
               return false;
            ai = vec[System.math().rnd() % vec.get_count()];
            {
               memcpy(&sa, ai -> ai_addr, ai -> ai_addrlen);
            }
            freeaddrinfo(res);
            return true;
         }
         string error = "Error: ";
#ifndef __CYGWIN__
         error += gai_strerror(n);
#endif
         return false;
#endif // NO_GETADDRINFO

#endif

      }


      bool net::reverse(struct sockaddr *sa, socklen_t sa_len, string & hostname, int flags)
      {
         string service;
         return net::reverse(sa, sa_len, hostname, service, flags);
      }


      bool net::reverse(struct sockaddr *sa, socklen_t sa_len, string & hostname, string & service, int flags)
      {

#ifdef METROWIN

         switch(sa->sa_family)
         {
         case AF_INET:
            {

               union
               {
                  struct
                  {
                     unsigned char b1;
                     unsigned char b2;
                     unsigned char b3;
                     unsigned char b4;
                  } a;
                  ipaddr_t l;
               } u;

               struct sockaddr_in *sa_in = (struct sockaddr_in *)sa;

               memcpy(&u.l, &sa_in -> sin_addr, sizeof(u.l));

               hostname.Format("%u.%u.%u.%u", u.a.b1, u.a.b2, u.a.b3, u.a.b4);

               if (flags & NI_NUMERICHOST)
               {
                  return true;
               }

               ::Windows::Networking::HostName ^ name = ref new ::Windows::Networking::HostName(rtstr(hostname));

               if(name != nullptr)
               {

                  hostname = begin(name->CanonicalName);

                  return true;

               }

            }
            break;

         case AF_INET6:
            {
               char slask[100]; // l2ip temporary
               *slask = 0;
               unsigned int prev = 0;
               bool skipped = false;
               bool ok_to_skip = true;
               {
                  unsigned short addr16[8];
                  struct sockaddr_in6 *sa_in6 = (struct sockaddr_in6 *)sa;
                  memcpy(addr16, &sa_in6 -> sin6_addr, sizeof(addr16));
                  for (index i = 0; i < 8; i++)
                  {
                     unsigned short x = ntohs(addr16[i]);
                     if (*slask && (x || !ok_to_skip || prev))
                        strcat(slask,":");
                     if (x || !ok_to_skip)
                     {
                        sprintf(slask + strlen(slask),"%x", x);
                        if (x && skipped)
                           ok_to_skip = false;
                     }
                     else
                     {
                        skipped = true;
                     }
                     prev = x;
                  }
               }
               if (!*slask)
                  strcpy(slask, "::");
               hostname = slask;
               if (flags & NI_NUMERICHOST)
               {
                  return true;
               }
               // %! TODO: ipv6 reverse lookup

               ::Windows::Networking::HostName ^ name = ref new ::Windows::Networking::HostName(rtstr(hostname));

               if(name != nullptr)
               {

                  hostname = begin(name->CanonicalName);

                  return true;

               }
            }
            break;
         }
         return false;
#else
         hostname = "";
         service = "";
#ifdef NO_GETADDRINFO
         switch (sa -> sa_family)
         {
         case AF_INET:
            if (flags & NI_NUMERICHOST)
            {
               union {
                  struct {
                     unsigned char b1;
                     unsigned char b2;
                     unsigned char b3;
                     unsigned char b4;
                  } a;
                  ipaddr_t l;
               } u;
               struct sockaddr_in *sa_in = (struct sockaddr_in *)sa;
               memcpy(&u.l, &sa_in -> sin_addr, sizeof(u.l));
               char tmp[100];
               sprintf(tmp, "%u.%u.%u.%u", u.a.b1, u.a.b2, u.a.b3, u.a.b4);
               hostname = tmp;
               return true;
            }
            else
            {
               struct sockaddr_in *sa_in = (struct sockaddr_in *)sa;
               struct hostent *h = gethostbyaddr( (const char *)&sa_in -> sin_addr, sizeof(sa_in -> sin_addr), AF_INET);
               if (h)
               {
                  hostname = h -> h_name;
                  return true;
               }
            }
            break;
#ifdef ENABLE_IPV6
         case AF_INET6:
            if (flags & NI_NUMERICHOST)
            {
               char slask[100]; // l2ip temporary
               *slask = 0;
               unsigned int prev = 0;
               bool skipped = false;
               bool ok_to_skip = true;
               {
                  unsigned short addr16[8];
                  struct sockaddr_in6 *sa_in6 = (struct sockaddr_in6 *)sa;
                  memcpy(addr16, &sa_in6 -> sin6_addr, sizeof(addr16));
                  for (index i = 0; i < 8; i++)
                  {
                     unsigned short x = ntohs(addr16[i]);
                     if (*slask && (x || !ok_to_skip || prev))
                        strcat(slask,":");
                     if (x || !ok_to_skip)
                     {
                        sprintf(slask + strlen(slask),"%x", x);
                        if (x && skipped)
                           ok_to_skip = false;
                     }
                     else
                     {
                        skipped = true;
                     }
                     prev = x;
                  }
               }
               if (!*slask)
                  strcpy(slask, "::");
               hostname = slask;
               return true;
            }
            else
            {
               // %! TODO: ipv6 reverse lookup
               struct sockaddr_in6 *sa_in = (struct sockaddr_in6 *)sa;
               struct hostent *h = gethostbyaddr( (const char *)&sa_in -> sin6_addr, sizeof(sa_in -> sin6_addr), AF_INET6);
               if (h)
               {
                  hostname = h -> h_name;
                  return true;
               }
            }
            break;
#endif
         }
         return false;
#else
         char host[NI_MAXHOST];
         char serv[NI_MAXSERV];
         // NI_NOFQDN
         // NI_NUMERICHOST
         // NI_NAMEREQD
         // NI_NUMERICSERV
         // NI_DGRAM
         int n = getnameinfo(sa, sa_len, host, sizeof(host), serv, sizeof(serv), flags);
         if (n)
         {
            // EAI_AGAIN
            // EAI_BADFLAGS
            // EAI_FAIL
            // EAI_FAMILY
            // EAI_MEMORY
            // EAI_NONAME
            // EAI_OVERFLOW
            // EAI_SYSTEM
            return false;
         }
         hostname = host;
         service = serv;
         return true;
#endif // NO_GETADDRINFO
#endif
      }


      bool net::u2service(const string & name, int& service, int ai_flags)
      {

#ifdef BSD_STYLE_SOCKETS

#ifdef NO_GETADDRINFO
         // %!
         return false;
#else
         struct addrinfo hints;
         service = 0;
         memset(&hints, 0, sizeof(hints));
         // AI_NUMERICHOST
         // AI_CANONNAME
         // AI_PASSIVE - server
         // AI_ADDRCONFIG
         // AI_V4MAPPED
         // AI_ALL
         // AI_NUMERICSERV
         hints.ai_flags = ai_flags;
         hints.ai_family = AF_UNSPEC;
         hints.ai_socktype = 0;
         hints.ai_protocol = 0;
         struct addrinfo *res;
         int n = getaddrinfo(NULL, name, &hints, &res);
         if (!n)
         {
            service = res -> ai_protocol;
            freeaddrinfo(res);
            return true;
         }
         return false;
#endif // NO_GETADDRINFO

#else

         return false;

#endif

      }


   } // namespace sockets


