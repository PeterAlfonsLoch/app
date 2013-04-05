#pragma once


class CLASS_DECL_ca memory_exception : 
   virtual public simple_exception
{
public:


   memory_exception(::ca::applicationsp papp);
   memory_exception(::ca::applicationsp papp, const char * pszMessage);
   virtual ~memory_exception();


};
