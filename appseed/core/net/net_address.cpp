#include "framework.h"


namespace net
{


   address::address()
   {

   }


   address::address(sp(base_application) papp, const in_addr & a, int32_t iPort) :
      element(papp),
      address_sp(allocer())
   {

      construct(a, iPort);

   }


   address::address(sp(base_application) papp, const in6_addr & a, int32_t iPort) :
      element(papp),
      address_sp(allocer())
   {

      construct(a, iPort);

   }


   address::address(sp(base_application) papp, const sockaddr & sa, int32_t sa_len) :
      element(papp),
      address_sp(allocer())
   {

      construct(sa, sa_len);

   }


   address::address(sp(base_application) papp, const string & strAddress, const string & strServiceName) :
      element(papp),
      address_sp(allocer())
   {

      construct(strAddress, strServiceName);

   }


   address::address(sp(base_application) papp, const string & strAddress, int32_t iPort) :
      element(papp),
      address_sp(allocer())
   {

      construct(strAddress, iPort);

   }

   address::address(const address & address)
   {

      if(address.is_null() || address.get_app() == NULL)
         return;

      set_app(address.get_app());
      
      address_sp::create(allocer());

      construct(*address.m_p);

   }

   address::~address()
   {

   }

   void address::construct(const in_addr & a, int32_t iPort)
   {
      m_p->construct(a, iPort);
   }

   void address::construct(const in6_addr & a, int32_t iPort)
   {
      m_p->construct(a, iPort);
   }

   void address::construct(const sockaddr & sa, int32_t sa_len)
   {
      m_p->construct(sa, sa_len);
   }

   void address::construct(const string & strAddress, const string & pszServiceName)
   {
      m_p->construct(strAddress, pszServiceName);
   }

   void address::construct(const string & strAddress, int iPort)
   {
      m_p->construct(strAddress, iPort);
   }

   void address::construct(const address_base & addr)
   {
      m_p->construct(addr);
   }

   void address::copy(const address_base & address)
   {

      if(this == &address || m_p == &address)
         return;

      address_sp::create(allocer());

      m_p->copy(address);
      
   }


   address & address::operator = (const address_base & address)
   {

      if(&address == this || &address == m_p)
         return *this;

      address_sp::release();

      address_sp::create(allocer());

      m_p->construct(address);

      return * this;

   }


   bool address::operator == (const address_base & address) const
   {

      if(&address == this || &address == m_p)
         return true;

      return m_p->is_equal(address);

   }


   string address::get_display_number() const
   {

      if(m_p == NULL)
         return "";

      return m_p->get_display_number();


   }


   string address::get_canonical_name() const
   {

      if(m_p == NULL)
         return "";

      return m_p->get_canonical_name();

   }


   string address::get_service_name() const
   {

      if(m_p == NULL)
         return "";

      return m_p->get_service_name();

   }


   int32_t address::get_service_number() const
   {

      if(m_p == NULL)
         return -1;

      return m_p->get_service_number();

   }

   bool address::set_service_number(int32_t iPort)
   {

      if(m_p == NULL)
         return false;

     return m_p->set_service_number(iPort);

   }


   int32_t address::service_name_to_number(const char * psz) const
   {

      if(m_p == NULL)
         return -1;

      return m_p->service_name_to_number(psz);

   }


   string  address::service_number_to_name(int32_t iPort) const
   {

      if(m_p == NULL)
         return "";

      return m_p->service_number_to_name(iPort);

   }


   bool address::is_ipv4() const
   {

      if(m_p == NULL)
         return false;

      return m_p->is_ipv4();

   }

   bool address::is_ipv6() const
   {

      if(m_p == NULL)
         return false;

      return m_p->is_ipv6();

   }


   e_family address::get_family() const
   {

      if(m_p == NULL)
         return family_none;

      return m_p->get_family();

   }

   int32_t address::get_bsd_family() const
   {

      if(m_p == NULL)
         return 0;

      return m_p->get_bsd_family();

   }

   const sockaddr * address::sa() const
   {

      if(m_p == NULL)
         return NULL;

      return m_p->sa();

   }

   int32_t address::sa_len() const
   {

      if(m_p == NULL)
         return 0;

      return m_p->sa_len();

   }


   bool address::is_in_net(const ::net::address_base & addr, const ::net::address_base & addrMask) const
   {

      if(m_p == NULL)
         return false;

      return m_p->is_in_net(addr, addrMask);

   }

   bool address::is_equal(const address_base & addr) const
   {

      if(m_p == NULL)
         return false;

      return m_p->is_equal(addr);

   }

   bool address::is_valid() const
   {

      if(m_p == NULL)
         return false;

      return m_p->is_valid();

   }


} // namespace net




