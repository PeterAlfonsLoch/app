#pragma once


class CLASS_DECL_ca resource_exception : 
   virtual public simple_exception
{
public:


   resource_exception(sp(::ca::application) papp);
   virtual ~resource_exception();


};
