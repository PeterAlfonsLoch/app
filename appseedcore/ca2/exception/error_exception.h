#pragma once

#pragma once


class CLASS_DECL_ca error_exception : 
   public base_exception
{
   // base class for resource-critical ca2 API exceptions
   // handles ownership and initialization of an error message
public:
   
   
   string m_strError;


   error_exception(const char * pszError);
   virtual ~error_exception();

   virtual BOOL GetErrorMessage(string & str, PUINT pnHelpContext = NULL);


};
