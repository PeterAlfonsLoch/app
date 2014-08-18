#pragma once


class CLASS_DECL_AXIS error_exception : 
   virtual public ::exception::axis
{
   // axis class for resource-critical core API exceptions
   // handles ownership and initialization of an error message
public:
   
   
   string m_strError;


   error_exception(sp(::axis::application) papp, const char * pszError);
   virtual ~error_exception();

   virtual bool get_error_message(string & str, PUINT pnHelpContext = NULL);


};
