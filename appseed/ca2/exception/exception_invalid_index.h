#pragma once


class CLASS_DECL_ca invalid_index_exception : 
   virtual public invalid_argument_exception
{
public:


   invalid_index_exception(sp(::ca::application) papp);
   invalid_index_exception(sp(::ca::application) papp, const char * pszMessage);
   virtual ~invalid_index_exception();


};

