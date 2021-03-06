#pragma once


class CLASS_DECL_AURA error_exception : 
   virtual public ::exception::base
{
   // aura class for resource-critical core API exceptions
   // handles ownership and initialization of an error message
public:
   
   
   string m_strError;


   error_exception(::aura::application * papp, const char * pszError);
   virtual ~error_exception();

   virtual bool get_error_message(string & str, PUINT pnHelpContext = NULL);


};


class CLASS_DECL_AURA index_out_of_bounds :
   virtual public error_exception
{
   // aura class for resource-critical core API exceptions
   // handles ownership and initialization of an error message
public:


   index_out_of_bounds(::aura::application * papp, const char * pszError = NULL);
   virtual ~index_out_of_bounds();


};
