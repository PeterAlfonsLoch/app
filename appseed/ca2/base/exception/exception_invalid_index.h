#pragma once


class CLASS_DECL_ca2 invalid_index_exception : 
   virtual public invalid_argument_exception
{
public:


   invalid_index_exception(sp(::ca2::application) papp);
   invalid_index_exception(sp(::ca2::application) papp, const char * pszMessage);
   virtual ~invalid_index_exception();


};

