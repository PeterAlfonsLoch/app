#pragma once


class CLASS_DECL_BASE interface_only_exception : 
   virtual public not_implemented
{
public:


   interface_only_exception(sp(::base::application) papp, const char * pszTip = NULL);
   interface_only_exception(const interface_only_exception & e);
   virtual ~interface_only_exception();


};
