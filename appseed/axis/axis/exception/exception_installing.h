#pragma once


//#include "exception_installing.h"


class CLASS_DECL_AXIS installing_exception : 
   virtual public temporary_exception
{
public:


   installing_exception(sp(::base::application) papp, const char * pszTip = NULL);
   installing_exception(const installing_exception & e);
   virtual ~installing_exception();


};
