#include "framework.h"


namespace sockets
{

   bsd_address::bsd_address(sp(base_application) papp) :
      element(papp)
   {
   }

   void bsd_address::construct(const in_addr & a, int32_t iPort)
   {

      m_pipv4 = canew(ipv4_address(get_app(), a, iPort));

   }


   void bsd_address::construct(const in6_addr & a, int32_t iPort)
   {

      m_pipv6 = canew(ipv6_address(get_app(), a, iPort));

   }


   void bsd_address::construct(const sockaddr & sa, int32_t sa_len)
   {

      if (sa_len == sizeof(struct sockaddr_in6))
      {
         struct sockaddr_in6 *p = (struct sockaddr_in6 *)&sa;
         if(p -> sin6_family == AF_INET6)
         {
            m_pipv6 = canew(ipv6_address(get_app(), p -> sin6_addr,ntohs(p -> sin6_port)));
            m_pipv6->SetFlowinfo(p -> sin6_flowinfo);
#ifndef _WIN32
            m_pipv6->SetScopeId(p -> sin6_scope_id);
#endif
            m_strServiceName = itoa_dup(p->sin6_port);
         }
      }
      if (sa_len == sizeof(struct sockaddr_in))
      {
         struct sockaddr_in *p = (struct sockaddr_in *)&sa;
         if (p -> sin_family == AF_INET)
         {
            m_pipv4 = canew(ipv4_address(get_app(), p->sin_addr, ntohs(p->sin_port)));
            m_strServiceName = itoa_dup(p->sin_port);
         }

      }

   }


   void bsd_address::construct(const string & strAddress, const string & strServiceName)
   {

      m_strServiceName = strServiceName;

      create_address(strAddress);

   }


   void bsd_address::construct(const string & strAddress, int32_t iPort)
   {


      m_strServiceName = ::str::from(iPort);

      if(!create_address(strAddress))
         throw "failed to create socket bsd_address";

   }

   void bsd_address::construct(const address_base & address)
   {

      copy(address);

   }


   bsd_address::~bsd_address()
   {

   }

   bool bsd_address::create_address(const string & strAddress)
   {

      m_pipv4.release();
      m_pipv6.release();


      if(System.net().isipv4(strAddress))
         m_pipv4 = new ipv4_address(get_app(), strAddress, System.net().service_port(m_strServiceName));
      else if(System.net().isipv6(strAddress))
         m_pipv6 = new ipv6_address(get_app(), strAddress, System.net().service_port(m_strServiceName));
      else
      {
         in6_addr in6;
         in_addr in;
         if(System.net().convert(in6,strAddress))
         {
            m_pipv6 = new ipv6_address(get_app(), in6, System.net().service_port(m_strServiceName));
         }
         else if(System.net().convert(in, strAddress))
         {
            m_pipv4 = new ipv4_address(get_app(), in, System.net().service_port(m_strServiceName));
         }
         else
         {
            return false;
         }
      }

      return true;

   }



   void bsd_address::copy(const bsd_address & bsd_address)
   {

      m_pipv4.release();
      m_pipv6.release();

      if(bsd_address.m_pipv6 != NULL)
      {
         m_pipv6 = canew(ipv6_address(*bsd_address.m_pipv6));
      }
      else if(bsd_address.m_pipv4 != NULL)
      {
         m_pipv4 = canew(ipv4_address(*bsd_address.m_pipv4));
      }

      m_strServiceName      = bsd_address.m_strServiceName;

   }


   bool bsd_address::is_equal(const bsd_address & bsd_address) const
   {

      if(m_pipv6 == NULL)
      {
         if(m_pipv4 == NULL)
         {
            return false;
         }
         else
         {
            if(bsd_address.m_pipv4 != NULL)
            {
               if(!m_pipv4->is_equal(*bsd_address.m_pipv4))
                  return false;
            }
            else
            {
               return false;
            }
         }
      }
      else if(m_pipv4 == NULL)
      {
         if(bsd_address.m_pipv6 != NULL)
         {
            if(!m_pipv6->is_equal(*bsd_address.m_pipv6))
               return false;
         }
         else
         {
            return false;
         }
      }

      return get_service_number() == bsd_address.get_service_number();

   }


   string bsd_address::get_display_number() const
   {

      if(m_pipv6 != NULL)
         return m_pipv6->get_display_number();
      else if(m_pipv4 != NULL)
         return m_pipv4->get_display_number();
      else
         return "";

   }


   string bsd_address::get_canonical_name() const
   {

      if(m_pipv6 != NULL)
         return m_pipv6->get_canonical_name();
      else if(m_pipv4 != NULL)
         return m_pipv4->get_canonical_name();
      else
         return "";

   }


   string bsd_address::get_service_name() const
   {

      string strService = m_strServiceName;

      if(::str::is_simple_natural(strService))
         return service_number_to_name(::str::to_int(strService));
      else
         return strService;

   }


   int32_t bsd_address::get_service_number() const
   {

      string strService = m_strServiceName;

      if(::str::is_simple_natural(strService))
         return service_name_to_number(strService);
      else
         return ::str::to_int(strService);

   }

   bool bsd_address::set_service_number(int32_t iPort)
   {

      if(iPort < 0 || iPort >= 65536)
         return false;

      m_strServiceName.Format("%d", iPort);

      return true;

   }


   int32_t bsd_address::service_name_to_number(const char * psz) const
   {

      return System.net().service_port(psz);

   }


   string  bsd_address::service_number_to_name(int32_t iPort) const
   {

      return System.net().service_name(iPort);

   }


   bool bsd_address::is_ipv4() const
   {

      return System.net().isipv4(get_display_number());

   }

   bool bsd_address::is_ipv6() const
   {

      return System.net().isipv6(get_display_number());

   }


   bool bsd_address::is_valid() const
   {

      try
      {

         if(m_pipv6 != NULL)
            return m_pipv6->IsValid();

         if(m_pipv4 != NULL)
            return m_pipv4->IsValid();

      }
      catch(...)
      {
      }

      return false;

   }

   bool bsd_address::is_in_net(const bsd_address & addr, const bsd_address & addrMask) const
   {

      if(is_ipv4() && addr.is_ipv4() && addrMask.is_ipv4())
      {

         in_addr a1;
         in_addr a2;
         in_addr aM;

         System.net().convert(a1, get_display_number());
         System.net().convert(a2, addr.get_display_number());
         System.net().convert(aM, addrMask.get_display_number());

         memand_dup(&a1, &a1, &aM, sizeof(a1));
         memand_dup(&a2, &a2, &aM, sizeof(a2));

         return memcmp(&a1, &a2, sizeof(aM)) == 0;

      }
      else if(is_ipv6() && addr.is_ipv6() && addrMask.is_ipv6())
      {

         in6_addr a1;
         in6_addr a2;
         in6_addr aM;

         System.net().convert(a1, get_display_number());
         System.net().convert(a2, addr.get_display_number());
         System.net().convert(aM, addrMask.get_display_number());

         memand_dup(&a1, &a1, &aM, sizeof(a1));
         memand_dup(&a2, &a2, &aM, sizeof(a2));

         return memcmp(&a1, &a2, sizeof(aM)) == 0;

      }
      else
      {
         return false;
      }

   }

   ::net::e_family bsd_address::get_family() const
   {

      if(m_pipv4 != NULL && m_pipv4->m_bValid)
      {
         return ::net::family_ipv4;
      }
      else if(m_pipv6 != NULL && m_pipv6->m_bValid)
      {
         return ::net::family_ipv6;
      }
      else
      {
         return ::net::family_none;
      }

   }

   int32_t bsd_address::get_bsd_family() const
   {

      if(m_pipv4 != NULL && m_pipv4->m_bValid)
      {
         return AF_INET;
      }
      else if(m_pipv6 != NULL && m_pipv6->m_bValid)
      {
         return AF_INET6;
      }
      else
      {
         return 0;
      }

   }

   const sockaddr * bsd_address::sa() const
   {

      if(m_pipv4 != NULL && m_pipv4->m_bValid)
      {
         return (sockaddr *) &m_pipv4->m_addr;
      }
      else if(m_pipv6 != NULL && m_pipv6->m_bValid)
      {
         return (sockaddr *) &m_pipv6->m_addr;
      }
      else
      {
         return NULL;
      }

   }

   int32_t bsd_address::sa_len() const
   {

      if(m_pipv4 != NULL && m_pipv4->m_bValid)
      {
         return sizeof(m_pipv4->m_addr);
      }
      else if(m_pipv6 != NULL && m_pipv6->m_bValid)
      {
         return sizeof(m_pipv6->m_addr);
      }
      else
      {
         return 0;
      }

   }

   void bsd_address::copy(const address_base & address)
   {

      copy(dynamic_cast < const bsd_address & > (address));

   }

   bool bsd_address::is_in_net(const address_base & address, const address_base & addressMask) const
   {

      return is_in_net(dynamic_cast < const bsd_address & > (address), dynamic_cast < const bsd_address & > (addressMask));

   }


   bool bsd_address::is_equal(const address_base & address) const
   {

      return is_equal(dynamic_cast < const bsd_address & > (address));

   }


} // namespace sockets




