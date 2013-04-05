#pragma once


class CLASS_DECL_ca os_exception : 
   virtual public simple_exception
{
public:


   os_exception(::ca::applicationsp papp);
   os_exception(::ca::applicationsp papp, const char * pszMessage);
   virtual ~os_exception();


};

