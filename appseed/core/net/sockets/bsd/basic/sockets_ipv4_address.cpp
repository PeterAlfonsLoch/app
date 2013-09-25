#include "framework.h"


namespace sockets
{

   ipv4_address::ipv4_address(sp(base_application) papp, port_t port) :
      element(papp),
      m_bValid(true)
   {
      memset(&m_addr, 0, sizeof(m_addr));
      m_addr.sin_family = AF_INET;
      m_addr.sin_port = htons( port );
   }


/*   ipv4_address::ipv4_address(sp(base_application) papp, ipaddr_t a,port_t port) : element(papp), m_bValid(true)
   {
      memset(&m_addr, 0, sizeof(m_addr));
      m_addr.sin_family = AF_INET;
      m_addr.sin_port = htons( port );
      memcpy(&m_addr.sin_addr, &a, sizeof(struct in_addr));
   }*/


   ipv4_address::ipv4_address(sp(base_application) papp, const in_addr& a,port_t port) : element(papp), m_bValid(true)
   {
      memset(&m_addr, 0, sizeof(m_addr));
      m_addr.sin_family = AF_INET;
      m_addr.sin_port = htons( port );
      m_addr.sin_addr = a;
      m_bValid = true;
   }


   ipv4_address::ipv4_address(sp(base_application) papp, const string & host,port_t port) : element(papp), m_bValid(false)
   {
      memset(&m_addr, 0, sizeof(m_addr));
      m_addr.sin_family = AF_INET;
      m_addr.sin_port = htons( port );
      {
         in_addr a;
         if (System.net().convert(a, host))
         {
            m_addr.sin_addr = a;
            m_bValid = true;
         }
      }
   }


   ipv4_address::ipv4_address(sp(base_application) papp, const sockaddr_in& sa) : element(papp)
   {
      m_addr = sa;
      m_bValid = sa.sin_family == AF_INET;
   }

   ipv4_address::ipv4_address(const ipv4_address & addr) :
      element(addr.get_app())
   {
      memset(&m_addr, 0, sizeof(m_addr));
      m_addr.sin_family = AF_INET;
      m_addr.sin_port = htons(0);
      operator = (addr);
   }

   ipv4_address::~ipv4_address()
   {
   }


   /*
   ipv4_address::operator struct sockaddr *()
   {
      return (struct sockaddr *)&m_addr;
   }


   ipv4_address::operator socklen_t()
   {
      return sizeof(struct sockaddr_in);
   }
   */

   void ipv4_address::SetPort(port_t port)
   {
      m_addr.sin_port = htons( port );
   }


   port_t ipv4_address::GetPort()
   {
      return ntohs( m_addr.sin_port );
   }


/*   bool ipv4_address::Resolve(sp(base_application) papp, const string & hostname, in_addr& a)
   {
      if(Sys(papp->m_pplaneapp->m_psystem).net().isipv4(hostname))
      {
         if(!Sys(papp->m_pplaneapp->m_psystem).net().convert(a, hostname, AI_NUMERICHOST))
            return false;
         return true;
      }
      if(!Sys(papp->m_pplaneapp->m_psystem).net().convert(a, hostname))
         return false;
      return true;
   }


   bool ipv4_address::Reverse(sp(base_application) papp, in_addr& a,string & name)
   {
      return Sys(papp->m_pplaneapp->m_psystem).net().reverse(a, name);
   }


   string ipv4_address::Convert(bool include_port)
   {
      if (include_port)
         return Convert(get_app(), m_addr.sin_addr) + ":" + ::str::from(GetPort());
      return Convert(get_app(), m_addr.sin_addr);
   }
   */

   /*
   string ipv4_address::Convert(sp(base_application) papp, struct in_addr& a)
   {
      struct sockaddr_in sa;
      memset(&sa, 0, sizeof(sa));
      sa.sin_family = AF_INET;
      sa.sin_addr = a;
      string name;
     Sys(papp->m_pplaneapp->m_psystem).net().reverse((struct sockaddr *)&sa, sizeof(sa), name, NI_NUMERICHOST | NI_NUMERICSERV);
      return name;
   }*/


   void ipv4_address::SetAddress(struct sockaddr *sa)
   {
      memcpy(&m_addr, sa, sizeof(struct sockaddr_in));
   }


   int32_t ipv4_address::GetFamily()
   {
      return m_addr.sin_family;
   }


   bool ipv4_address::IsValid() const
   {
      return m_bValid;
   }


/*   bool ipv4_address::operator==(::net::address a)
   {
      if (a.GetFamily() != GetFamily())
         return false;
      if ((socklen_t)a != sizeof(m_addr))
         return false;
      struct sockaddr *sa = a;
      struct sockaddr_in *p = (struct sockaddr_in *)sa;
      if (p -> sin_port != m_addr.sin_port)
         return false;
      if (memcmp(&p -> sin_addr, &m_addr.sin_addr, 4))
         return false;
      return true;
   }*/

   string ipv4_address::Reverse()
   {
      string tmp;
      System.net().reverse((sockaddr *) &m_addr, sizeof(m_addr), tmp);
      return tmp;
   }

   bool ipv4_address::is_in_net(const ipv4_address & addr, const ipv4_address & mask) const
   {
#ifdef WINDOWS
      return (addr.m_addr.sin_addr.S_un.S_addr & mask.m_addr.sin_addr.S_un.S_addr) == (m_addr.sin_addr.S_un.S_addr & mask.m_addr.sin_addr.S_un.S_addr);
#else
      return (addr.m_addr.sin_addr.s_addr & mask.m_addr.sin_addr.s_addr) == (m_addr.sin_addr.s_addr & mask.m_addr.sin_addr.s_addr);
#endif
   }

   void ipv4_address::copy(const ipv4_address & addr)
   {
      if(&addr != this)
      {
         m_addr = addr.m_addr;
         m_bValid = addr.m_bValid;
      }
   }

   bool ipv4_address::is_equal(const ipv4_address &a ) const
   {

      if(!m_bValid || !a.m_bValid)
         return false;

      return !memcmp(&m_addr, &a.m_addr, sizeof(m_addr));

   }

   string ipv4_address::get_display_number() const
   {
      return ::to_vsstring(&m_addr.sin_addr);
   }

   string ipv4_address::get_canonical_name() const
   {
      string str;
      if(!System.net().convert(str, m_addr.sin_addr))
         return "";
      return str;
   }


} // namespace sockets




