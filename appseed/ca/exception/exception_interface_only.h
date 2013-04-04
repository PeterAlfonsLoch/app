#pragma once


class CLASS_DECL_ca interface_only_exception : 
   virtual public not_implemented
{
public:


   interface_only_exception(::ca::application * papp, const char * pszTip = ::null());
   interface_only_exception(const interface_only_exception & e);
   virtual ~interface_only_exception();


};
