/*
Module : IPENUM.H
Purpose: Interface for an core API class wrapper for IP address enumeration
Created: PJN / 21-04-1998
History: None

Copyright (ca) 1998 by PJ Naughter.


*/
#pragma once


namespace net
{

	class address;

   class CLASS_DECL_AURA ip_enum :
      virtual public ::object
   {
   public:


      ip_enum(::aura::application * papp);
      virtual ~ip_enum();


      virtual ::count enumerate(array < ::net::address > & ipa);


   };


   typedef smart_pointer < ip_enum > ip_enum_sp;


} // namespace net



