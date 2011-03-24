#pragma once


class CLASS_DECL_ca assert_exception : public simple_exception
{
public:
   assert_exception(const assert_exception & e);
   assert_exception(const char * pszFile, long lLine);
   virtual ~assert_exception();

   string m_strFile;
   long m_lLine;
};
