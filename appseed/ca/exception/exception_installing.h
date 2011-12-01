#pragma once


#include "exception_installing.h"


class CLASS_DECL_ca installing_exception : 
   public temporary_exception
{
public:


   installing_exception(const char * pszTip = NULL);
   installing_exception(const installing_exception & e);
   virtual ~installing_exception();


};
