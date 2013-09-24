#include "framework.h"


namespace net
{


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

   address::address(const address & address) :
      element(address.get_app()),
      address_sp(allocer())
   {

      copy(address);

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


   void address::copy(const address & address)
   {
      UNREFERENCED_PARAMETER(address);
   }


   address & address::operator = (const address_base & address)
   {

      if(&address == this || address.m_p == m_p)
         return *this;

      address_sp::release();

      address_sp::create(allocer());

      m_p->copy(address);

      return * this;

   }


   bool address::operator == (const address & address) const
   {

      if(&address == this || address.m_p == m_p)
         return true;

      return m_p->is_equal(address);

   }


   string address::get_display_number() const
   {

      return m_p->get_display_number();


   }


   string address::get_canonical_name() const
   {

      return m_p->get_canonical_name();

   }


   string address::get_service_name() const
   {

      return m_p->get_service_name();

   }


   int32_t address::get_service_number() const
   {

      return m_p->get_service_number();

   }

   bool address::set_service_number(int32_t iPort)
   {

     return m_p->set_service_number(iPort);

   }


   int32_t address::service_name_to_number(const char * psz) const
   {

      return m_p->service_name_to_number(psz);

   }


   string  address::service_number_to_name(int32_t iPort) const
   {

      return m_p->service_number_to_name(iPort);

   }


   bool address::is_ipv4() const
   {

      return m_p->is_ipv4();

   }

   bool address::is_ipv6() const
   {

      return m_p->is_ipv6();

   }


   bool address::is_valid() const
   {
   
      return m_p->is_valid();

   }

   bool address::is_in_net(const address & addr, const address & addrMask) const
   {

      return m_p->is_in_net(addr, addrMask);

   }

   int32_t address::GetFamily() const
   {

      return m_p->GetFamily();

   }

   const sockaddr * address::sa() const
   {

      return m_p->sa();

   }

   int32_t address::sa_len() const
   {

      return m_p->sa_len();

   }


   bool address::is_in_net(const ::net::address_base & addr, const ::net::address_base & addrMask) const
   {

      return m_p->is_in_net(addr, addrMask);

   }

   bool address::is_equal(const address_base & addr) const
   {
      return m_p->is_equal(addr);
   }
} // namespace net




