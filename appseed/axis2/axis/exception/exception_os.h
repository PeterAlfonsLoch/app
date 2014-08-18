#pragma once


class CLASS_DECL_AXIS os_exception : 
   virtual public simple_exception
{
public:


   os_exception(sp(::axis::application) papp);
   os_exception(sp(::axis::application) papp, const char * pszMessage);
   virtual ~os_exception();


};

