#pragma once


class CLASS_DECL_AXIS resource_exception : 
   virtual public simple_exception
{
public:


   resource_exception(sp(::axis::application) papp);
   virtual ~resource_exception();


};
