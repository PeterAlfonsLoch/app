#pragma once


namespace libepp
{

   class NSIPAddr
   {
   public:

      
      string version;
      string addr;


      bool operator<(const NSIPAddr &ip) const
      {
         return addr < ip.addr;
      }

      string get_xml(::ca::application * papp) const;

   };


   class NSIPAddrArray :
      public comparable_array<NSIPAddr>
   {
   public:

      string get_xml(::ca::application * papp) const;

   };

   class NameServer 
   {
   public:


      string            name;
      NSIPAddrArray     ips;
      
      
      bool operator<(const NameServer &n) const 
      {
         return name < n.name;
      }

      string get_xml(::ca::application * papp) const;

   };

   class NameServerArray :
      public base_array < NameServer >
   {
   public:

      string get_xml(::ca::application * papp) const;

   };


} // namespace libepp