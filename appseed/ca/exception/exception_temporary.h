#pragma once


class CLASS_DECL_ca temporary_exception : 
   virtual public base_exception
{
public:
   
   
   vsstring m_strTip;


   temporary_exception(::ca::application * papp, const char * pszTip = NULL);
   temporary_exception(const temporary_exception & e);
   virtual ~temporary_exception();


};


