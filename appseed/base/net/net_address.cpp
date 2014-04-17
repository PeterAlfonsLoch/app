#include "framework.h"


namespace net
{


   address::address()
   {

      zero(this, sizeof(u.m_sa));

#ifdef METROWIN

      m_posdata = new os_data();

#endif

   }

   address::address(int32_t family, port_t port)
   {

      zero(this, sizeof(u.m_sa));

#ifdef METROWIN

      m_posdata = new os_data();

#endif

      u.s.m_family = family;
      u.s.m_port = htons(port);
      sync_os_service();

   }


   address::address(const sockaddr & sa)
   {

#ifdef METROWIN

      m_posdata = new os_data();

#endif

      u.m_sa = sa;

      if (u.s.m_family != AF_INET6 && u.s.m_family != AF_INET)
      {
         u.s.m_family = AF_UNSPEC;
      }
      else
      {
         sync_os_address();
         sync_os_service();
      }

   }


   address::address(const string & host, port_t port)
   {

      zero(this, sizeof(u.m_sa));

#ifdef METROWIN

      m_posdata = new os_data();

#endif

      set_address(host);
      u.s.m_port = htons(port);
      sync_os_service();

   }


   address::address(sp(base_application) papp, const string & host, const string & strService)
   {

      zero(this, sizeof(u.m_sa));

#ifdef METROWIN

      m_posdata = new os_data();

#endif

      set_address(host);
      u.s.m_port = Sys(papp).net().service_port(strService);
      sync_os_service();

   }


   address::address(const in6_addr & a, port_t port)
   {

      zero(this, sizeof(u.m_sa));

#ifdef METROWIN

      m_posdata = new os_data();

#endif

      u.s.m_family = AF_INET6;
      u.s.m_port = htons(port);
      u.m_addr6.sin6_addr = a;
      sync_os_address();
      sync_os_service();

   }

   address::address(const sockaddr_in6 & sa)
   {

      u.m_addr6 = sa;

#ifdef METROWIN

      m_posdata = new os_data();

#endif

      if (u.s.m_family != AF_INET6)
      {
         u.s.m_family = AF_UNSPEC;
      }
      else
      {
         sync_os_address();
         sync_os_service();
      }

   }


   address::address(const in_addr& a, port_t port)
   {

      zero(this, sizeof(u.m_sa));

#ifdef METROWIN

      m_posdata = new os_data();

#endif

      u.s.m_family = AF_INET;
      u.s.m_port = htons(port);
      u.m_addr.sin_addr = a;
      sync_os_address();
      sync_os_service();

   }

   address::address(const sockaddr_in & sa)
   {

      u.m_addr = sa;

#ifdef METROWIN

      m_posdata = new os_data();

#endif

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

#ifdef METROWIN

      m_posdata = new os_data();

#endif

      copy(address);

   }


   address::~address()
   {

#ifdef METROWIN

      delete m_posdata;

#endif

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

#ifdef METROWIN

      if (!is_ipv4() && !is_ipv6() && m_posdata != NULL && m_posdata->m_hostname != nullptr)
      {

         ((address *) this)->sync_os_address();

      }

#endif

      if (is_ipv4())
      {

         return ::to_vsstring(&u.m_addr.sin_addr);

      }
      else if (is_ipv6())
      {

         return ::to_vsstring(&u.m_addr6.sin6_addr);

      }
      else
      {

         return "";

      }

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
#ifdef METROWIN

      if (m_family == AF_INET || m_family == AF_INET6)
      {
         m_posdata->m_hostname = ref new ::Windows::Networking::HostName(get_display_number());
      }
      else if (m_posdata->m_hostname != nullptr)
      {

         string strDisplayNumber = m_posdata->m_hostname->RawName;

         if (::sockets::net::isipv4(strDisplayNumber))
         {
            ::sockets::net::convert(m_addr.sin_addr, strDisplayNumber);
            m_family = AF_INET;
         }
         else if (::sockets::net::isipv6(strDisplayNumber))
         {
            ::sockets::net::convert(m_addr6.sin6_addr, strDisplayNumber);
            m_family = AF_INET;
         }
         else
         {
            m_family = AF_UNSPEC;
         }

      }
#endif
   }

   void address::sync_os_service()
   {
#ifdef METROWIN
#endif
   }


   bool address::set_address(const string & strAddress)
   {

#ifdef METROWIN

      m_posdata->m_hostname = ref new ::Windows::Networking::HostName(strAddress);

#else

      if (Sys(get_thread_app()).net().convert(u.m_addr6.sin6_addr, strAddress))
      {
         u.s.m_family = AF_INET6;
      }
      else if (Sys(get_thread_app()).net().convert(u.m_addr.sin_addr, strAddress))
      {
         u.s.m_family = AF_INET;
      }
      else
      {
         u.s.m_family = AF_UNSPEC;
      }

#endif

      return u.s.m_family != AF_UNSPEC;

   }


   /*   string address::reverse() const
   {

   string tmp;

   Sys(get_thread_app()).net().reverse((sockaddr *) &m_sa, sa_len(), tmp);

   return tmp;

   }*/


} // namespace net




