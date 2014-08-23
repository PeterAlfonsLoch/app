#pragma once


class CLASS_DECL_AURA operation_canceled_exception : 
   virtual public simple_exception
{
public:


   operation_canceled_exception(sp(::aura::application) papp);
   operation_canceled_exception(sp(::aura::application) papp, const char * pszMessage);
   virtual ~operation_canceled_exception();


};

