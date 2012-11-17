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
   class address :
      virtual public ::radix::object
   {
   public:


      ::Windows::Networking::HostName ^      m_hostname;
      ::Platform::String ^                   m_strService;
      

      address(::ca::application * papp, const char * pszAddress = NULL, const char * pszServiceName = NULL);
      address(::ca::application * papp, const char * pszAddress, int iPort);
      address(const address & address);
      virtual ~address();


      address & operator = (const address & address);
      bool operator == (const address & address) const;

      virtual string get_display_number() const;
      virtual string get_canonical_name() const;
      virtual string get_service_name() const;
      virtual int    get_service_number() const;


      int     service_name_to_number(const char * psz) const;
      string  service_number_to_name(int i) const;


      virtual bool is_in_net(const address & addr, const address & addrMask) const;

      virtual bool is_ipv4() const;
      virtual bool is_ipv6() const;


   };


} // namespace sockets





