#pragma once


class CLASS_DECL_ca runtime_error : 
   virtual public error_exception
{
   // base class for resource-critical ca API exceptions
   // handles ownership and initialization of an error message
public:
   
   
   runtime_error(::ca::application * papp, const char * pszError);
   virtual ~runtime_error();

};
