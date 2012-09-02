#pragma once


class CLASS_DECL_ca memory_exception : 
   public simple_exception
{
public:


   memory_exception();
   memory_exception(const char * pszMessage);
   virtual ~memory_exception();


};
