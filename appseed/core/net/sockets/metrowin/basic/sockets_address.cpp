#include "framework.h"


namespace sockets
{

   winrt_address::winrt_address(sp(base_application) papp) :
      element(papp)
   {
      
      m_bValid = false;

   }

   void winrt_address::construct(const string & strAddress, const string & strServiceName)
   {

      if(strAddress.is_empty())
         m_hostname  = nullptr;
      else
         m_hostname  = ref new ::Windows::Networking::HostName(strAddress);

      m_strService   = strServiceName;

      sync_addr();


   }


   void winrt_address::construct(const string & strAddress, int iPort)
   {

      try
      {

         m_hostname     = ref new ::Windows::Networking::HostName(strAddress);

      }
      catch(...)
      {

         m_hostname = nullptr;

      }

      m_strService   = itoa_dup(iPort);

      sync_addr();

   }

   
   winrt_address::winrt_address(const winrt_address & winrt_address)
   {

      operator = (winrt_address);

   }


   winrt_address::~winrt_address()
   {

   }


   winrt_address & winrt_address::operator = (const winrt_address & winrt_address)
   {

      m_hostname        = winrt_address.m_hostname;
      m_strService      = winrt_address.m_strService;

      return *this;

   }


   bool winrt_address::operator == (const winrt_address & winrt_address) const
   {

      return m_hostname->IsEqual(winrt_address.m_hostname) && get_service_number() == winrt_address.get_service_number();

   }


   string winrt_address::get_display_number() const
   {

      return m_hostname->DisplayName;

   }


   string winrt_address::get_canonical_name() const
   {

      return m_hostname->CanonicalName;

   }


   string winrt_address::get_service_name() const
   {

      string strService = m_strService;

      if(::str::is_simple_natural(strService))
         return service_number_to_name(::str::to_int(strService));
      else
         return strService;

   }


   int winrt_address::get_service_number() const
   {

      string strService = m_strService;

      if(::str::is_simple_natural(strService))
         return ::str::to_int(strService);
      else
         return service_name_to_number(strService);
         

   }
   

   int winrt_address::service_name_to_number(const char * psz) const
   {

      return System.net().service_port(psz);

   }


   string  winrt_address::service_number_to_name(int iPort) const
   {

      return System.net().service_name(iPort);

   }

   
   bool winrt_address::is_ipv4() const
   {

      return System.net().isipv4(get_display_number());

   }

   bool winrt_address::is_ipv6() const
   {

      return System.net().isipv6(get_display_number());

   }


   bool winrt_address::is_in_net(const winrt_address & addr, const winrt_address & addrMask) const
   {

      if(is_ipv4() && addr.is_ipv4() && addrMask.is_ipv4())
      {
         
         in_addr a1;
         in_addr a2;
         in_addr aM;

         System.net().convert(a1, get_display_number());
         System.net().convert(a2, addr.get_display_number());
         System.net().convert(aM, addrMask.get_display_number());

         return (a1.S_un.S_addr & aM.S_un.S_addr) ==  (a2.S_un.S_addr & aM.S_un.S_addr);

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

   bool winrt_address::sync_addr()
   {

      ZERO(m_addr);
      if(is_ipv4())
      {

         m_addr.m_addr.sin_family = AF_INET;
         m_addr.m_addr.sin_port = htons( port );
         {
            in_addr a;
            if (System.net().convert(a, host))
            {
               m_addr.m_addr.sin_addr = a;
               m_bValid = true;
            }
         }
      }
      else
      {
         m_addr.m_addr6.sin6_family = AF_INET6;
         m_addr.m_addr6.sin6_port = htons( port );
         {
            struct in6_addr a;
            if(System.net().convert(a, host))
            {
               m_addr.m_addr6.sin6_addr = a;
               m_bValid = true;
            }
         }

      }

   }

} // namespace sockets




