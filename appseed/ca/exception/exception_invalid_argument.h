#pragma once


class CLASS_DECL_ca invalid_argument_exception : public simple_exception
{
public:


   invalid_argument_exception();
   invalid_argument_exception(const char * pszMessage);
   virtual ~invalid_argument_exception();


};

