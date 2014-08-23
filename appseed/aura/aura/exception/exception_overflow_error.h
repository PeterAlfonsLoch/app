#pragma once


class CLASS_DECL_AURA overflow_error :
   virtual public error_exception
{
   // aura class for resource-critical core API exceptions
   // handles ownership and initialization of an error message
public:


   overflow_error(sp(::aura::application) papp, const char * pszError);
   virtual ~overflow_error();


};



