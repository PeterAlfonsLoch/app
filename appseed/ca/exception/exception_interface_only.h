#pragma once


class CLASS_DECL_ca interface_only_exception : 
   virtual public not_implemented_exception
{
public:


   interface_only_exception(::ca::application * papp, const char * pszTip = NULL);
   interface_only_exception(const interface_only_exception & e);
   virtual ~interface_only_exception();


};
