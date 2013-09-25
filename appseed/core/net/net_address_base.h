#pragma once


namespace net
{

   enum e_family
   {

      family_none,
      family_ipv4,
      family_ipv6

   };


   class address_base :
      virtual public ::object
   {
   public:


      virtual void construct(const in_addr & a, int32_t iPort = 0) = 0;
      virtual void construct(const in6_addr & a, int32_t iPort = 0) = 0;
      virtual void construct(const sockaddr & sa, int32_t sa_len) = 0;
      virtual void construct(const string & strAddress = "", const string & pszServiceName = "") = 0;
      virtual void construct(const string & strAddress, int iPort) = 0;
      virtual void construct(const address_base & addr) = 0;

      
      virtual void copy(const address_base & addr) = 0;

      
      virtual bool set_service_number(int32_t iPort) = 0;


      virtual string get_display_number() const = 0;
      virtual string get_canonical_name() const = 0;
      virtual string get_service_name() const = 0;
      virtual int    get_service_number() const = 0;


      virtual int     service_name_to_number(const char * psz) const = 0;
      virtual string  service_number_to_name(int i) const = 0;

      virtual bool is_in_net(const address_base & addr, const address_base & addrMask) const = 0;
      virtual bool is_equal(const address_base & addr) const = 0;


      virtual bool is_ipv4() const = 0;
      virtual bool is_ipv6() const = 0;

      
      virtual bool is_valid() const = 0;

      
      virtual int32_t get_bsd_family() const;
      virtual e_family get_family() const;


      virtual const sockaddr * sa() const = 0;
      virtual int32_t sa_len() const = 0;


   };


   typedef sp(address_base) address_sp;


} // namespace sockets





