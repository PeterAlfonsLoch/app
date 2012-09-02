#pragma once


class CLASS_DECL_ca invalid_index_exception : public invalid_argument_exception
{
public:


   invalid_index_exception();
   invalid_index_exception(const char * pszMessage);
   virtual ~invalid_index_exception();


};

