#pragma once


// http://www.alhem.net/
/** from C++ Sockets Library \file Utility.h
**/


namespace sockets
{


   /**
   This class and its subclasses is intended to be used as replacement
   for the internal data type 'ipaddr_t' and various implementations of
   IPv6 addressing found throughout the library.
   'ipaddr_t' is an IPv4 address in network byte order.
   'port_t' is the portnumber in host byte order.
   'struct in6_addr' is an IPv6 address.
   'struct in_addr' is an IPv4 address.
   \ingroup basic
   */
   class winrt_address :
      virtual public ::object
   {
   public:


      ::Windows::Networking::HostName ^      m_hostname;
      ::Platform::String ^                   m_strService;
      bool                                   m_bValid;

      union
      {
         struct sockaddr_in      m_addr;
         struct sockaddr_in6     m_addr6;
      } m_addr;
      

      winrt_address(sp(base_application) papp);
      virtual ~winrt_address();

      virtual void construct(const in_addr & a, int32_t iPort = 0) = 0;
      virtual void construct(const in6_addr & a, int32_t iPort = 0) = 0;
      virtual void construct(const sockaddr & sa, int32_t sa_len) = 0;
      virtual void construct(const string & strAddress = "", const string & pszServiceName = "");
      virtual void construct(const string & strAddress, int iPort);

      virtual void copy(const ::net::address_base & address);

      virtual string get_display_number() const;
      virtual string get_canonical_name() const;
      virtual string get_service_name() const;
      virtual int    get_service_number() const;


      virtual int    service_name_to_number(const char * psz) const;
      virtual string service_number_to_name(int i) const;


      virtual bool is_in_net(const ::net::address_base & addr, const ::net::address_base & addrMask) const;
      virtual bool is_equal(const ::net::address_base & address) const;

      virtual bool is_ipv4() const;
      virtual bool is_ipv6() const;


      virtual void sync_addr();


   };


} // namespace sockets





