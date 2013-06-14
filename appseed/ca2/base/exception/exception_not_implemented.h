#pragma once


class CLASS_DECL_ca2 not_implemented : 
   virtual public base_exception
{
public:


   vsstring m_strTip;


   not_implemented(sp(::ca2::application) papp, const char * pszTip = NULL);
   not_implemented(const not_implemented & e);
   virtual ~not_implemented();


};
