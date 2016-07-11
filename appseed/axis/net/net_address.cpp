#include "framework.h" // from "axis/net/net_sockets.h"
#include "axis/net/net_sockets.h"

#if defined(__arm__)

#include <sys/endian.h>
#include <arpa/inet.h>

#endif

namespace net
{


   address::address()
   {

      zero(this, sizeof(u.m_sa));

//#ifdef METROWIN
//
//      m_posdata = new os_data();
//
//#endif
      m_iLen = -1;
   }


   address::address(int32_t family, port_t port)
   {

      zero(this, sizeof(u.m_sa));

//#ifdef METROWIN
//
//      m_posdata = new os_data();
//
//#endif
      m_iLen = -1;
      u.s.m_family = family;
      u.s.m_port = htons(port);
      sync_os_service();

   }


   address::address(const sockaddr & sa, int iLen)
   {

//#ifdef METROWIN
//
//      m_posdata = new os_data();
//
//#endif

      zero(this, sizeof(u.m_sa));

      if (sa.sa_family == AF_INET6)
      {
         m_iLen = iLen <= 0 ? sizeof(sockaddr_in6) : iLen;
         memcpy(&u.m_sa, &sa, m_iLen);
         sync_os_address();
         sync_os_service();
      }
      else if (sa.sa_family == AF_INET)
      {
         m_iLen = -1;
         memcpy(&u.m_sa, &sa, sizeof(sockaddr_in));
         sync_os_address();
         sync_os_service();
      }
      else
      {
         m_iLen = -1;
         u.s.m_family = AF_UNSPEC;
      }

   }


   address::address(const string & host, port_t port)
   {

      zero(this, sizeof(address));

//#ifdef METROWIN
//
//      m_posdata = new os_data();
//
//#endif
      m_iLen = -1;
      set_address(host);
      u.s.m_port = htons(port);
      sync_os_service();

   }


   address::address(::aura::application * papp, const string & host, const string & strService)
   {

      zero(this, sizeof(u.m_sa));

//#ifdef METROWIN
//
//      m_posdata = new os_data();
//
//#endif
      m_iLen = -1;
      set_address(host);
      u.s.m_port = Sess(papp).sockets().net().service_port(strService);
      sync_os_service();

   }


   address::address(const in6_addr & a, port_t port)
   {

      zero(this, sizeof(u.m_sa));

//#ifdef METROWIN
//
//      m_posdata = new os_data();
//
//#endif
      m_iLen = -1;
      u.s.m_family = AF_INET6;
      u.s.m_port = htons(port);
      u.m_addr6.sin6_addr = a;
      sync_os_address();
      sync_os_service();

   }

   address::address(const sockaddr_in6 & sa, int iLen)
   {

//#ifdef METROWIN
//
//      m_posdata = new os_data();
//
//#endif

      zero(this, sizeof(u.m_sa));

      if (sa.sin6_family != AF_INET6)
      {
         u.s.m_family = AF_UNSPEC;
      }
      else
      {
         m_iLen = iLen <= 0 ? sizeof(sockaddr_in6) : iLen;

         memcpy(&u.m_addr6, &sa, m_iLen);

         sync_os_address();
         sync_os_service();
      }

   }


   address::address(const in_addr& a, port_t port)
   {

      zero(this, sizeof(u.m_sa));

//#ifdef METROWIN
//
//      m_posdata = new os_data();
//
//#endif
      m_iLen = -1;
      u.s.m_family = AF_INET;
      u.s.m_port = htons(port);
      u.m_addr.sin_addr = a;
      sync_os_address();
      sync_os_service();

   }

   address::address(const sockaddr_in & sa)
   {

      zero(this, sizeof(u.m_sa));
      u.m_addr = sa;

//#ifdef METROWIN
//
//      m_posdata = new os_data();
//
//#endif
      m_iLen = -1;
      if (u.s.m_family != AF_INET)
      {
         u.s.m_family = AF_UNSPEC;
      }
      else
      {
         sync_os_address();
         sync_os_service();
      }

   }


   address::address(const address & address)
   {

//#ifdef METROWIN
//
//      m_posdata = new os_data();
//
//#endif

      copy(address);

   }


   address::~address()
   {

//#ifdef METROWIN
//
//      delete m_posdata;
//
//#endif

   }


   address & address::operator = (const address & address)
   {

      if (&address == this)
         return *this;

      copy(address);

      return *this;

   }


   bool address::operator == (const address & address) const
   {

      if (&address == this)
         return true;

      return is_equal(address);

   }


   string address::get_display_number() const
   {

//#ifdef METROWIN
//
//      if (!is_ipv4() && !is_ipv6() && m_posdata != NULL && m_posdata->m_hostname != nullptr)
//      {
//
//         ((address *) this)->sync_os_address();
//
//      }
//
//#endif

      string str;

      if (is_ipv4())
      {

         to_string(str, (in_addr &)u.m_addr.sin_addr);

      }
      else if (is_ipv6())
      {

         to_string(str, (in_addr6 &) u.m_addr6.sin6_addr);

      }

      return str;

   }


   bool address::is_in_same_net(const ::net::address & addr, const ::net::address & addrMask) const
   {

      if (is_ipv4() && addr.is_ipv4() && addrMask.is_ipv4())
      {

         in_addr a1 = u.m_addr.sin_addr;

         in_addr a2 = addr.u.m_addr.sin_addr;

         in_addr aM = addrMask.u.m_addr.sin_addr;

         memand_dup(&a1, &a1, &aM, sizeof(a1));

         memand_dup(&a2, &a2, &aM, sizeof(a2));

         return memcmp(&a1, &a2, sizeof(aM)) == 0;

      }
      else if (is_ipv6() && addr.is_ipv6() && addrMask.is_ipv6())
      {

         in6_addr a1 = u.m_addr6.sin6_addr;

         in6_addr a2 = addr.u.m_addr6.sin6_addr;

         in6_addr aM = addrMask.u.m_addr6.sin6_addr;

         memand_dup(&a1, &a1, &aM, sizeof(a1));

         memand_dup(&a2, &a2, &aM, sizeof(a2));

         return memcmp(&a1, &a2, sizeof(aM)) == 0;

      }
      else
      {
         return false;
      }

   }

   bool address::is_equal(const address & addr) const
   {

      if (u.s.m_port != addr.u.s.m_port)
         return false;

      if (is_ipv6() && addr.is_ipv6())
      {

         return memcmp(&u.m_addr6.sin6_addr, &addr.u.m_addr6.sin6_addr, sizeof(in6_addr)) == 0;

      }
      else if (is_ipv4() && addr.is_ipv4())
      {

         return memcmp(&u.m_addr.sin_addr, &addr.u.m_addr.sin_addr, sizeof(in_addr)) == 0;

      }

      return false;

   }


   void address::sync_os_address()
   {
//#ifdef METROWIN
//
//      if (u.s.m_family == AF_INET || u.s.m_family == AF_INET6)
//      {
//         m_posdata->m_hostname = ref new ::Windows::Networking::HostName(get_display_number());
//      }
//      else if (m_posdata->m_hostname != nullptr)
//      {
//
//         string strDisplayNumber = m_posdata->m_hostname->RawName;
//
//         if (::sockets::net::isipv4(strDisplayNumber))
//         {
//            ::sockets::net::convert(u.m_addr.sin_addr, strDisplayNumber);
//            u.s.m_family = AF_INET;
//         }
//         else if (::sockets::net::isipv6(strDisplayNumber))
//         {
//            ::sockets::net::convert(u.m_addr6.sin6_addr, strDisplayNumber);
//            u.s.m_family = AF_INET;
//         }
//         else
//         {
//            u.s.m_family = AF_UNSPEC;
//         }
//
//      }
//#endif
   }

   void address::sync_os_service()
   {
//#ifdef METROWIN
//#endif
   }


   void * address::addr_data()
   {
      if (u.m_sa.sa_family == AF_INET)
      {
         return &u.m_addr.sin_addr;
      }
      else if (u.m_sa.sa_family == AF_INET6)
      {
         return &u.m_addr6.sin6_addr;
      }
      else
      {
         return NULL;
      }
   }

   bool address::set_address(const string & strAddress)
   {

//#ifdef METROWIN
//
//      m_posdata->m_hostname = ref new ::Windows::Networking::HostName(strAddress);
//
//#else

      if (Sess(get_thread_app()).sockets().net().convert(u.m_addr6.sin6_addr, strAddress))
      {
         u.s.m_family = AF_INET6;
      }
      else if (Sess(get_thread_app()).sockets().net().convert(u.m_addr.sin_addr, strAddress))
      {
         u.s.m_family = AF_INET;
      }
      else
      {
         u.s.m_family = AF_UNSPEC;
      }

//#endif

      return u.s.m_family != AF_UNSPEC;

   }


   /*   string address::reverse() const
   {

   string tmp;

   Sess(get_thread_app()).sockets().net().reverse((sockaddr *) &m_sa, sa_len(), tmp);

   return tmp;

   }*/


   int32_t address::sa_len() const
   {

      int iFamilyLen = family_len(u.s.m_family);

      if (m_iLen <= 0)
         return iFamilyLen;
      else
         return m_iLen;

   }

   void address::copy(const address & address)
   {

      memcpy(this, &address, sizeof(address));

      sync_os_address();
      sync_os_service();

   }




} // namespace net




