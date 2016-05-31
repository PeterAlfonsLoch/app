#pragma once


class CLASS_DECL_ACE resource_exception : 
   virtual public simple_exception
{
public:


   resource_exception(::ace::application * papp);
   virtual ~resource_exception();


};
