#pragma once


class CLASS_DECL_BASE resource_exception : 
   virtual public simple_exception
{
public:


   resource_exception(sp(::base::application) papp);
   virtual ~resource_exception();


};
