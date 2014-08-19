#pragma once


class CLASS_DECL_BASE runtime_error : 
   virtual public error_exception
{
   // base class for resource-critical core API exceptions
   // handles ownership and initialization of an error message
public:
   
   
   runtime_error(sp(::axis::application) papp, const char * pszError);
   virtual ~runtime_error();

};
