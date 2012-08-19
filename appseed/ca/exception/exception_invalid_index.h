#pragma once


class CLASS_DECL_ca invalid_index_exception : public invalid_argument_exception
{
public:


   invalid_index_exception();
   invalid_index_exception(const char * pszMessage);
   invalid_index_exception(bool bAutoDelete);
   invalid_index_exception(bool bAutoDelete, UINT nResourceID);
   virtual ~invalid_index_exception();


};

