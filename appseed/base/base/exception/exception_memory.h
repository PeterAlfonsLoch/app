#pragma once


class CLASS_DECL_BASE memory_exception : 
   virtual public simple_exception
{
public:


   memory_exception(sp(base_application) papp);
   memory_exception(sp(base_application) papp, const char * pszMessage);
   virtual ~memory_exception();


};




