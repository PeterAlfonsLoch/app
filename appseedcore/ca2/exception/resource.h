#pragma once


class CLASS_DECL_ca resource_exception : public simple_exception    // resource failure
{
   
public:
   resource_exception();

// Implementation
public:
   explicit resource_exception(BOOL bAutoDelete);
   resource_exception(BOOL bAutoDelete, UINT nResourceID);
   virtual ~resource_exception();
};
