/*
Module : IPENUM.H
Purpose: Interface for an ca API class wrapper for IP address enumeration
Created: PJN / 21-04-1998
History: None

Copyright (c) 1998 by PJ Naughter.  


*/


namespace ca
{


   class CLASS_DECL_ca2 ip_enum :
      virtual public ::ca::object
   {
   public:


      ip_enum(sp(::ca::application) papp);
      virtual ~ip_enum();


      virtual ::count enumerate(stringa & stra);


   };


   typedef ::ca::smart_pointer < ip_enum > ip_enum_sp;


} // namespace ca



