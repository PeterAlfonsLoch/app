#pragma once


class CLASS_DECL_ca operation_canceled_exception : 
   virtual public simple_exception
{
public:


   operation_canceled_exception(::ca::applicationsp papp);
   operation_canceled_exception(::ca::applicationsp papp, const char * pszMessage);
   virtual ~operation_canceled_exception();


};

