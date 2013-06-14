#pragma once


class CLASS_DECL_ca2 runtime_error : 
   virtual public error_exception
{
   // base class for resource-critical ca2 API exceptions
   // handles ownership and initialization of an error message
public:
   
   
   runtime_error(sp(::ca2::application) papp, const char * pszError);
   virtual ~runtime_error();

};
