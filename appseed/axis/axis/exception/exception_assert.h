#pragma once


class CLASS_DECL_AXIS assert_exception : 
   virtual public simple_exception
{
public:


   string m_strFile;
   long m_lLine;


   assert_exception(const assert_exception & e);
   assert_exception(sp(::base::application) papp, const char * pszFile, long lLine);
   virtual ~assert_exception();

};
