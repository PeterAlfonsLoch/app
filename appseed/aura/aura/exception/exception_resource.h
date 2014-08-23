#pragma once


class CLASS_DECL_AURA resource_exception : 
   virtual public simple_exception
{
public:


   resource_exception(sp(::aura::application) papp);
   virtual ~resource_exception();


};
