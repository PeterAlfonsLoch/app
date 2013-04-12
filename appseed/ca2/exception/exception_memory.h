#pragma once


class CLASS_DECL_ca memory_exception : 
   virtual public simple_exception
{
public:


   memory_exception(sp(::ca::application) papp);
   memory_exception(sp(::ca::application) papp, const char * pszMessage);
   virtual ~memory_exception();


};
