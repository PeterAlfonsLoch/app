#pragma once


class CLASS_DECL_ACE invalid_argument_exception :
   virtual public simple_exception
{
public:


   invalid_argument_exception(::ace::application * papp);
   invalid_argument_exception(::ace::application * papp, const char * pszMessage);
   virtual ~invalid_argument_exception();


};

