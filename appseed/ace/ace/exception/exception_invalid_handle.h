#pragma once


class CLASS_DECL_ACE invalid_handle_exception :
   virtual public os_exception
{
public:


   invalid_handle_exception(::ace::application * papp);
   invalid_handle_exception(::ace::application * papp, const char * pszMessage);
   virtual ~invalid_handle_exception();


};

