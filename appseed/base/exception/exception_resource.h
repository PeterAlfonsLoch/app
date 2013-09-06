#pragma once


class CLASS_DECL_c resource_exception : 
   virtual public simple_exception
{
public:


   resource_exception(sp(base_application) papp);
   virtual ~resource_exception();


};
