#pragma once


class CLASS_DECL_AURA runtime_error : 
   virtual public error_exception
{
   // aura class for resource-critical core API exceptions
   // handles ownership and initialization of an error message
public:
   

   runtime_error(const string & strError, sp(::aura::application) papp = ::get_thread_app());
   runtime_error(sp(::aura::application) papp, const char * pszError);
   virtual ~runtime_error();

};
