#pragma once


class CLASS_DECL_AXIS temporary_exception : 
   virtual public ::exception::base
{
public:
   
   
   string m_strTip;


   temporary_exception(sp(::base::application) papp, const char * pszTip = NULL);
   temporary_exception(const temporary_exception & e);
   virtual ~temporary_exception();


};


