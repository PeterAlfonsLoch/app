#pragma once


class CLASS_DECL_ca resource_exception : 
   virtual public simple_exception
{
public:


   resource_exception(::ca::applicationsp papp);
   virtual ~resource_exception();


};
