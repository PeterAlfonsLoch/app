#pragma once


class CLASS_DECL_ca invalid_argument_exception : public simple_exception
{
   
public:
   invalid_argument_exception();

// Implementation
public:
   invalid_argument_exception(BOOL bAutoDelete);
   invalid_argument_exception(BOOL bAutoDelete, UINT nResourceID);
   virtual ~invalid_argument_exception();
};

