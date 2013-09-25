#include "framework.h"


namespace net
{


   address::address()
   {

      zero(this, sizeof(m_sa));

   }

   address::address(int32_t family, port_t port)
   {

      zero(this, sizeof(m_sa));

      m_family    = family;
      m_port      = htons( port );

   }


   address::address(const sockaddr & sa)
   {

      m_sa        = sa;

      if(m_family != AF_INET6 && m_family != AF_INET)
      {
         m_family    = AF_UNSPEC;
      }

   }


   address::address(const string & host, port_t port)
   {

      zero(this, sizeof(m_sa));

      set_address(host);
      m_port = htons( port );

   }




   address::address(const in6_addr & a,port_t port)
   {

      zero(this, sizeof(m_sa));

      m_family             = AF_INET6;
      m_port               = htons( port );
      m_addr6.sin6_addr    = a;

   }

   address::address(const sockaddr_in6 & sa)
   {

      m_addr6     = sa;

      if(m_family != AF_INET6)
      {
         m_family    = AF_UNSPEC;
      }

   }


   address::address(const in_addr& a,port_t port)
   {

      zero(this, sizeof(m_sa));

      m_family             = AF_INET;
      m_port               = htons( port );
      m_addr.sin_addr      = a;

   }

   address::address(const sockaddr_in & sa)
   {

      m_addr      = sa;

      if(m_family != AF_INET)
      {
         m_family    = AF_UNSPEC;
      }

   }


   address::address(const address & address)
   {

      copy(address);

   }



   address & address::operator = (const address & address)
   {

      if(&address == this)
         return *this;

      copy(address);

      return * this;

   }


   bool address::operator == (const address & address) const
   {

      if(&address == this)
         return true;

      return is_equal(address);

   }


   string address::get_display_number() const
   {

      if(is_ipv4())
      {

         return ::to_vsstring(&m_addr.sin_addr);

      }
      else if(is_ipv6())
      {

         return ::to_vsstring(&m_addr6.sin6_addr);

      }
      else
      {

         return "";

      }

   }






   bool address::is_in_same_net(const ::net::address & addr, const ::net::address & addrMask) const
   {

      if(is_ipv4() && addr.is_ipv4() && addrMask.is_ipv4())
      {

         in_addr a1 = m_addr.sin_addr;

         in_addr a2 = addr.m_addr.sin_addr;

         in_addr aM = addrMask.m_addr.sin_addr;

         memand_dup(&a1, &a1, &aM, sizeof(a1));

         memand_dup(&a2, &a2, &aM, sizeof(a2));

         return memcmp(&a1, &a2, sizeof(aM)) == 0;

      }
      else if(is_ipv6() && addr.is_ipv6() && addrMask.is_ipv6())
      {

         in_addr6 a1 = m_addr6.sin6_addr;

         in_addr6 a2 = addr.m_addr6.sin6_addr;

         in_addr6 aM = addrMask.m_addr6.sin6_addr;

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

      if(m_port != addr.m_port)
         return false;

      if(is_ipv6() && addr.is_ipv6())
      {

         return memcmp(&m_addr6.sin6_addr, &addr.m_addr6.sin6_addr, sizeof(in6_addr)) == 0;

      }
      else if(is_ipv4() && addr.is_ipv4())
      {

         return memcmp(&m_addr.sin_addr, &addr.m_addr.sin_addr, sizeof(in_addr)) == 0;

      }

      return false;

   }

   bool address::set_address(const string & strAddress)
   {

      if(Sys(get_thread_app()).net().convert(m_addr6.sin6_addr, strAddress))
      {
         m_family = AF_INET6;
      }
      else if(Sys(get_thread_app()).net().convert(m_addr.sin_addr, strAddress))
      {
         m_family = AF_INET;
      }
      else
      {
         m_family = AF_UNSPEC;
      }

      return m_family != AF_UNSPEC;

   }


   string address::reverse() const
   {

      string tmp;

      Sys(get_thread_app()).net().reverse((sockaddr *) &m_sa, sa_len(), tmp);

      return tmp;

   }


} // namespace net




