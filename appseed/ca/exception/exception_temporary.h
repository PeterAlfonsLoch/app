#pragma once


#include "base_exception.h"


class CLASS_DECL_ca temporary_exception : 
   public base_exception
{
public:
   
   
   vsstring m_strTip;


   temporary_exception(const char * pszTip = NULL);
   temporary_exception(const temporary_exception & e);
   virtual ~temporary_exception();


};


