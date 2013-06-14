#pragma once


class CLASS_DECL_ca2 memory_exception : 
   virtual public simple_exception
{
public:


   memory_exception(sp(::ca2::application) papp);
   memory_exception(sp(::ca2::application) papp, const char * pszMessage);
   virtual ~memory_exception();


};
