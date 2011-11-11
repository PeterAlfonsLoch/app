/*
Module : IPENUM.H
Purpose: Interface for an ca2 API class wrapper for IP address enumeration
Created: PJN / 21-04-1998
History: None

Copyright (c) 1998 by PJ Naughter.  


*/


////////////////////////////////// Macros ///////////////////////////

class CLASS_DECL_ca ip_enum :
   virtual public ::radix::object
{
public:
//constructors / Destructors
  ip_enum(::ca::application * papp);
  virtual ~ip_enum();

//methods
  BOOL enumerate();

protected:
  virtual BOOL EnumCallbackFunction(int nAdapter, const in_addr& address) = 0;
  BOOL m_bWinsockInitialied;
};
