#pragma once


class CLASS_DECL_ACE overflow_error :
   virtual public error_exception
{
   // ace class for resource-critical core API exceptions
   // handles ownership and initialization of an error message
public:


   overflow_error(::ace::application * papp, const char * pszError);
   virtual ~overflow_error();


};



