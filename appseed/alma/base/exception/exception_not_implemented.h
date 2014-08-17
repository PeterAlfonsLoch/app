#pragma once


class CLASS_DECL_BASE not_implemented : 
   virtual public ::exception::base
{
public:


   string m_strTip;


   not_implemented(sp(::base::application) papp, const char * pszTip = NULL);
   not_implemented(const not_implemented & e);
   virtual ~not_implemented();


};
