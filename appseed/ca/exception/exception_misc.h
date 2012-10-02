#pragma once


class CLASS_DECL_ca misc_exception : 
   virtual public simple_exception
{
public:


   vsstring m_strMessage;


   misc_exception(const misc_exception & e);
   misc_exception(::ca::application * papp, const char * pszMessage);
   virtual ~misc_exception();

   virtual bool GetErrorMessage(string & str, PUINT pnHelpContext = NULL);

   
};
