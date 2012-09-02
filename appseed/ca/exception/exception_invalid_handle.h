#pragma once


class CLASS_DECL_ca invalid_handle_exception : public os_exception
{
public:


   invalid_handle_exception();
   invalid_handle_exception(const char * pszMessage);
   virtual ~invalid_handle_exception();


};

