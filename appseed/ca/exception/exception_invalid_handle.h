#pragma once


class CLASS_DECL_ca invalid_handle_exception :
   virtual public os_exception
{
public:


   invalid_handle_exception(::ca::application * papp);
   invalid_handle_exception(::ca::application * papp, const char * pszMessage);
   virtual ~invalid_handle_exception();


};

