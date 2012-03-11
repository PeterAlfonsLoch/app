#pragma once


#include "simple_exception.h"


class CLASS_DECL_ca resource_exception : 
   public simple_exception
{
public:


   resource_exception();
   explicit resource_exception(BOOL bAutoDelete);
   resource_exception(BOOL bAutoDelete, UINT nResourceID);
   virtual ~resource_exception();


};
