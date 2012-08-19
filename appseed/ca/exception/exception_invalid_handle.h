#pragma once


class CLASS_DECL_ca invalid_handle_exception : public os_exception
{
public:


   invalid_handle_exception();
   invalid_handle_exception(const char * pszMessage);
   invalid_handle_exception(bool bAutoDelete);
   invalid_handle_exception(bool bAutoDelete, UINT nResourceID);
   virtual ~invalid_handle_exception();


};

