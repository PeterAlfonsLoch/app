#pragma once


class CLASS_DECL_AURA os_exception : 
   virtual public simple_exception
{
public:


   os_exception(sp(::aura::application) papp);
   os_exception(sp(::aura::application) papp, const char * pszMessage);
   virtual ~os_exception();


};

