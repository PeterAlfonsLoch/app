#pragma once


class CLASS_DECL_ca misc_exception : 
   public simple_exception
{
public:
   misc_exception(const misc_exception & e);
   misc_exception(const char * pszMessage);
   virtual ~misc_exception();
   virtual BOOL GetErrorMessage(string & str, PUINT pnHelpContext = NULL);

   string m_strMessage;
};
