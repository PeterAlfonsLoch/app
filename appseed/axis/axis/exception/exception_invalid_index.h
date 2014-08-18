#pragma once


class CLASS_DECL_AXIS invalid_index_exception : 
   virtual public invalid_argument_exception
{
public:


   invalid_index_exception(sp(::base::application) papp);
   invalid_index_exception(sp(::base::application) papp, const char * pszMessage);
   virtual ~invalid_index_exception();


};

