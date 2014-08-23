#pragma once


class CLASS_DECL_AURA invalid_handle_exception :
   virtual public os_exception
{
public:


   invalid_handle_exception(sp(::aura::application) papp);
   invalid_handle_exception(sp(::aura::application) papp, const char * pszMessage);
   virtual ~invalid_handle_exception();


};

