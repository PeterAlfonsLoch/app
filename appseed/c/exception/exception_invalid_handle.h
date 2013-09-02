#pragma once


class CLASS_DECL_c invalid_handle_exception :
   virtual public os_exception
{
public:


   invalid_handle_exception(sp(::application) papp);
   invalid_handle_exception(sp(::application) papp, const char * pszMessage);
   virtual ~invalid_handle_exception();


};

