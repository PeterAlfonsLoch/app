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
      virtual ~address() {}

      /** get a pointer to the address struct. */
      virtual operator struct sockaddr *() = 0;

      /** get length of address struct. */
      virtual operator socklen_t() = 0;

      /** Compare two addresses. */
      virtual bool operator==(address&) = 0;

      /** Set port number.
         \param port Port number in host byte order */
      virtual void SetPort(port_t port) = 0;

      /** get port number.
         \return Port number in host byte order. */
      virtual port_t GetPort() = 0;

      /** Set socket address.
         \param sa Pointer to either 'struct sockaddr_in' or 'struct sockaddr_in6'. */
      virtual void SetAddress(struct sockaddr *sa) = 0;

      /** Convert address to text. */
      virtual string Convert(bool include_port) = 0;

      /** Reverse lookup of address. */
      virtual string Reverse() = 0;

      /** get address family. */
      virtual int GetFamily() = 0;

      /** Address structure is valid. */
      virtual bool IsValid() = 0;

      /** get a copy of this sockets::address object. */
      virtual address * GetCopy();
   };

   typedef ::ca::smart_pointer < address > address_sp;

} // namespace sockets

