#pragma once


class CLASS_DECL_ACE error_exception : 
   virtual public ::exception::base
{
   // ace class for resource-critical core API exceptions
   // handles ownership and initialization of an error message
public:
   
   
   string m_strError;


   error_exception(::ace::application * papp, const char * pszError);
   virtual ~error_exception();

   virtual bool get_error_message(string & str, PUINT pnHelpContext = NULL);


};


class CLASS_DECL_ACE index_out_of_bounds :
   virtual public error_exception
{
   // ace class for resource-critical core API exceptions
   // handles ownership and initialization of an error message
public:


   index_out_of_bounds(::ace::application * papp, const char * pszError = NULL);
   virtual ~index_out_of_bounds();


};
