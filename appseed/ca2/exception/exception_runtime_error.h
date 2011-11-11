#pragma once


class CLASS_DECL_ca runtime_error : 
   public error_exception
{
   // base class for resource-critical ca2 API exceptions
   // handles ownership and initialization of an error message
public:
   
   
   runtime_error(const char * pszError);
   virtual ~runtime_error();

};
