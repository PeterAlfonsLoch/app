#pragma once


class CLASS_DECL_ca2 os_exception : 
   virtual public simple_exception
{
public:


   os_exception(sp(::ca::application) papp);
   os_exception(sp(::ca::application) papp, const char * pszMessage);
   virtual ~os_exception();


};

