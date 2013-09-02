#pragma once


class CLASS_DECL_c error_exception : 
   virtual public ::exception::base
{
   // base class for resource-critical ca2 API exceptions
   // handles ownership and initialization of an error message
public:
   
   
   vsstring m_strError;


   error_exception(sp(::application) papp, const char * pszError);
   virtual ~error_exception();

   virtual bool get_error_message(string & str, PUINT pnHelpContext = NULL);


};
