/*
Module : IPENUM.H
Purpose: Interface for an ca2 API class wrapper for IP address enumeration
Created: PJN / 21-04-1998
History: None

Copyright (c) 1998 by PJ Naughter.  


Deep modification from callback to ip_array enumeration by Camilo on 14-04-2012
*/


namespace ca4
{


   class CLASS_DECL_ca ip_enum :
      virtual public ::radix::object
   {
   public:


      ip_enum(::ca::application * papp);
      virtual ~ip_enum();


      virtual ::count enumerate(stringa & stra);


   };


   typedef ::ca::smart_pointer < ip_enum > ip_enum_sp;


} // namespace ca4



