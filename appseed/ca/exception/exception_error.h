#pragma once


class CLASS_DECL_ca error_exception : 
   virtual public base_exception
{
   // base class for resource-critical ca2 API exceptions
   // handles ownership and initialization of an error message
public:
   
   
   vsstring m_strError;


   error_exception(::ca::application * papp, const char * pszError);
   virtual ~error_exception();

   virtual bool GetErrorMessage(string & str, PUINT pnHelpContext = NULL);


};
