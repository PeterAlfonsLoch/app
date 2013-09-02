#pragma once


class CLASS_DECL_c temporary_exception : 
   virtual public ::exception::base
{
public:
   
   
   vsstring m_strTip;


   temporary_exception(sp(::application) papp, const char * pszTip = NULL);
   temporary_exception(const temporary_exception & e);
   virtual ~temporary_exception();


};


