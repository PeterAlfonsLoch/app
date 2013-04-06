#pragma once


class CLASS_DECL_ca operation_canceled_exception : 
   virtual public simple_exception
{
public:


   operation_canceled_exception(sp(::ca::application) papp);
   operation_canceled_exception(sp(::ca::application) papp, const char * pszMessage);
   virtual ~operation_canceled_exception();


};

