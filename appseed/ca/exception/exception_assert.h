#pragma once


class CLASS_DECL_ca assert_exception : 
   virtual public simple_exception
{
public:


   vsstring m_strFile;
   long m_lLine;


   assert_exception(const assert_exception & e);
   assert_exception(::ca::application * papp, const char * pszFile, long lLine);
   virtual ~assert_exception();

};
