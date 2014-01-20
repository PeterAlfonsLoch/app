#pragma once


class CLASS_DECL_BASE os_exception : 
   virtual public simple_exception
{
public:


   os_exception(sp(base_application) papp);
   os_exception(sp(base_application) papp, const char * pszMessage);
   virtual ~os_exception();


};

