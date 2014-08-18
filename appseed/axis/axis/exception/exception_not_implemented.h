#pragma once


class CLASS_DECL_AXIS not_implemented : 
   virtual public ::exception::axis
{
public:


   string m_strTip;


   not_implemented(sp(::axis::application) papp, const char * pszTip = NULL);
   not_implemented(const not_implemented & e);
   virtual ~not_implemented();


};
