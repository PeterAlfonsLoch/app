#pragma once


class CLASS_DECL_ca2 invalid_argument_exception :
   virtual public simple_exception
{
public:


   invalid_argument_exception(sp(::ca2::application) papp);
   invalid_argument_exception(sp(::ca2::application) papp, const char * pszMessage);
   virtual ~invalid_argument_exception();


};

