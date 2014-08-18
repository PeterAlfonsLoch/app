#pragma once


class CLASS_DECL_AXIS overflow_error :
   virtual public error_exception
{
   // base class for resource-critical core API exceptions
   // handles ownership and initialization of an error message
public:


   overflow_error(sp(::base::application) papp, const char * pszError);
   virtual ~overflow_error();


};



