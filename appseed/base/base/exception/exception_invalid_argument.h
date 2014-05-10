#pragma once


class CLASS_DECL_BASE invalid_argument_exception :
   virtual public simple_exception
{
public:


   invalid_argument_exception(sp(::base::application) papp);
   invalid_argument_exception(sp(::base::application) papp, const char * pszMessage);
   virtual ~invalid_argument_exception();


};

