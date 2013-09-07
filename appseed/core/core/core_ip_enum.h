/*
Module : IPENUM.H
Purpose: Interface for an ca2 API class wrapper for IP address enumeration
Created: PJN / 21-04-1998
History: None

Copyright (ca) 1998 by PJ Naughter.  


*/


namespace ca2
{


   class CLASS_DECL_ca2 ip_enum :
      virtual public object
   {
   public:


      ip_enum(sp(base_application) papp);
      virtual ~ip_enum();


      virtual ::count enumerate(stringa & stra);


   };


   typedef smart_pointer < ip_enum > ip_enum_sp;


} // namespace ca2



