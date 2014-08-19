#pragma once


class CLASS_DECL_BASE range_error : 
   virtual public error_exception
{
   // base class for resource-critical core API exceptions
   // handles ownership and initialization of an error message
public:
   
   
   range_error(sp(::axis::application) papp, const char * pszError);
   virtual ~range_error();


};



