#pragma once


class CLASS_DECL_ca2 resource_exception : 
   virtual public simple_exception
{
public:


   resource_exception(sp(::ca2::application) papp);
   virtual ~resource_exception();


};
