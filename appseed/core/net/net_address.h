#pragma once


namespace net
{


   class address :
      virtual public address_base,
      public address_sp
   {
   public:


      address(sp(base_application) papp, const in_addr & a, int32_t iPort = 0);
      address(sp(base_application) papp, const in6_addr & a, int32_t iPort = 0);
      address(sp(base_application) papp, const sockaddr & sa, int32_t sa_len);
      address(sp(base_application) papp, const string & strAddress = "", const string & pszServiceName = "");
      address(sp(base_application) papp, const string & strAddress, int iPort);
      address(const address & address);
      virtual ~address();


      virtual void construct(const in_addr & a, int32_t iPort = 0);
      virtual void construct(const in6_addr & a, int32_t iPort = 0);
      virtual void construct(const sockaddr & sa, int32_t sa_len);
      virtual void construct(const string & strAddress = "", const string & pszServiceName = "");
      virtual void construct(const string & strAddress, int iPort);
      virtual void construct(const address_base & addr);



      address & operator = (const address & address);
      bool operator == (const address & address) const;

      virtual string get_display_number() const;
      virtual string get_canonical_name() const;
      virtual string get_service_name() const;
      virtual int    get_service_number() const;


      int     service_name_to_number(const char * psz) const;
      string  service_number_to_name(int i) const;


      virtual bool is_in_net(const address_base & addr, const address_base & addrMask) const;
      virtual bool is_equal(const address_base & addr) const;

      virtual bool is_ipv4() const;
      virtual bool is_ipv6() const;

      virtual void copy(const address & address);

      int32_t GetFamily() const;

      const sockaddr * sa() const;

      int32_t sa_len() const;


   };


} // namespace sockets





