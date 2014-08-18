#pragma once


class CLASS_DECL_BASE error_exception : 
   virtual public ::exception::base
{
   // base class for resource-critical core API exceptions
   // handles ownership and initialization of an error message
public:
   
   
   string m_strError;


   error_exception(sp(::base::application) papp, const char * pszError);
   virtual ~error_exception();

   virtual bool get_error_message(string & str, PUINT pnHelpContext = NULL);


};
