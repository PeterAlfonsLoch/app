#pragma once


class CLASS_DECL_ca2 invalid_handle_exception :
   virtual public os_exception
{
public:


   invalid_handle_exception(sp(::ca::application) papp);
   invalid_handle_exception(sp(::ca::application) papp, const char * pszMessage);
   virtual ~invalid_handle_exception();


};

