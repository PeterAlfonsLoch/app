#pragma once


class CLASS_DECL_c overflow_error :
   virtual public error_exception
{
   // base class for resource-critical ca2 API exceptions
   // handles ownership and initialization of an error message
public:


   overflow_error(sp(::application) papp, const char * pszError);
   virtual ~overflow_error();


};



