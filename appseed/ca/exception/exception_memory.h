#pragma once


class CLASS_DECL_ca memory_exception : 
   public simple_exception
{
   
public:
   memory_exception();

// Implementation
public:
   explicit memory_exception(bool bAutoDelete);
   memory_exception(bool bAutoDelete, UINT nResourceID);
   virtual ~memory_exception();
};
