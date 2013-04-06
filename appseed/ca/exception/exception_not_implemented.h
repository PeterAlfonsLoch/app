#pragma once


class CLASS_DECL_ca not_implemented : 
   virtual public base_exception
{
public:


   vsstring m_strTip;


   not_implemented(sp(::ca::application) papp, const char * pszTip = ::null());
   not_implemented(const not_implemented & e);
   virtual ~not_implemented();


};
