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
   class CLASS_DECL_ca2 bsd_address :
      virtual public object
   {
   public:


      sp(ipv4_address)  m_pipv4;
      sp(ipv6_address)  m_pipv6;
      string            m_strServiceName;


      bsd_address(sp(base_application) papp);
      virtual ~bsd_address();

      virtual void construct(const in_addr & a, int32_t iPort = 0);
      virtual void construct(const in6_addr & a, int32_t iPort = 0);
      virtual void construct(const sockaddr & sa, int32_t sa_len);
      virtual void construct(const string & strAddress = "", const string & strServiceName = "");
      virtual void construct(const string & strAddress, int32_t iPort);


      bool create_address(const string & strAddress);


      void copy(const address_base & address);

      virtual string get_display_number() const;
      virtual string get_canonical_name() const;
      virtual string get_service_name() const;
      virtual int32_t    get_service_number() const;

      virtual bool set_service_number(int32_t iPort);


      int32_t     service_name_to_number(const char * psz) const;
      string  service_number_to_name(int32_t i) const;


      virtual bool is_in_net(const address_base & addr, const address_base & addrMask) const;
      bool is_equal(const address_base & address) const;

      virtual bool is_ipv4() const;
      virtual bool is_ipv6() const;


      int32_t GetFamily() const;

      bool is_valid() const;


      const sockaddr * sa() const;
      int32_t sa_len() const;


   };


} // namespace sockets







