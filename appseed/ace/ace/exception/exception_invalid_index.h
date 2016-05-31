#pragma once


class CLASS_DECL_ACE invalid_index_exception : 
   virtual public invalid_argument_exception
{
public:


   invalid_index_exception(::ace::application * papp);
   invalid_index_exception(::ace::application * papp, const char * pszMessage);
   virtual ~invalid_index_exception();


};

