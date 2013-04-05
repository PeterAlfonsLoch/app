#pragma once


class CLASS_DECL_ca invalid_handle_exception :
   virtual public os_exception
{
public:


   invalid_handle_exception(::ca::applicationsp papp);
   invalid_handle_exception(::ca::applicationsp papp, const char * pszMessage);
   virtual ~invalid_handle_exception();


};

