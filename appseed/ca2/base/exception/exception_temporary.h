#pragma once


class CLASS_DECL_ca2 temporary_exception : 
   virtual public base_exception
{
public:
   
   
   vsstring m_strTip;


   temporary_exception(sp(::ca2::application) papp, const char * pszTip = NULL);
   temporary_exception(const temporary_exception & e);
   virtual ~temporary_exception();


};


