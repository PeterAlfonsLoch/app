#pragma once


class CLASS_DECL_ACE runtime_error : 
   virtual public error_exception
{
   // ace class for resource-critical core API exceptions
   // handles ownership and initialization of an error message
public:
   

   runtime_error(const string & strError, ::ace::application * papp = ::get_thread_app());
   runtime_error(::ace::application * papp, const char * pszError);
   virtual ~runtime_error();

};
