#pragma once


class CLASS_DECL_c os_exception : 
   virtual public simple_exception
{
public:


   os_exception(sp(base_application) papp);
   os_exception(sp(base_application) papp, const char * pszMessage);
   virtual ~os_exception();


};

