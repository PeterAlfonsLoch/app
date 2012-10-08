#pragma once


class CLASS_DECL_ca invalid_argument_exception :
   virtual public simple_exception
{
public:


   invalid_argument_exception(::ca::application * papp);
   invalid_argument_exception(::ca::application * papp, const char * pszMessage);
   virtual ~invalid_argument_exception();


};

