#pragma once


class CLASS_DECL_ca not_implemented_exception : public base_exception
{
public:
   vsstring m_strTip;

   not_implemented_exception(const char * pszTip = NULL);
   not_implemented_exception(const not_implemented_exception & e);
   virtual ~not_implemented_exception();
};
