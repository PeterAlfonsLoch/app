#pragma once


class CLASS_DECL_AXIS invalid_handle_exception :
   virtual public os_exception
{
public:


   invalid_handle_exception(sp(::base::application) papp);
   invalid_handle_exception(sp(::base::application) papp, const char * pszMessage);
   virtual ~invalid_handle_exception();


};

