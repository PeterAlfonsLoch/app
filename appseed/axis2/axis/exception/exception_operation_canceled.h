#pragma once


class CLASS_DECL_AXIS operation_canceled_exception : 
   virtual public simple_exception
{
public:


   operation_canceled_exception(sp(::axis::application) papp);
   operation_canceled_exception(sp(::axis::application) papp, const char * pszMessage);
   virtual ~operation_canceled_exception();


};

