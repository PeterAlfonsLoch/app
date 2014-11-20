#pragma once


class CLASS_DECL_AURA os_exception : 
   virtual public simple_exception
{
public:


   os_exception(::aura::application * papp);
   os_exception(::aura::application * papp, const char * pszMessage);
   virtual ~os_exception();


};

