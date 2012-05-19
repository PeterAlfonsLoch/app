#pragma once


class CLASS_DECL_ca resource_exception : 
   public simple_exception
{
public:


   resource_exception();
   explicit resource_exception(bool bAutoDelete);
   resource_exception(bool bAutoDelete, UINT nResourceID);
   virtual ~resource_exception();


};
