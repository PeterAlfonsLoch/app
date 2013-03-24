#pragma once


class CLASS_DECL_ca io_exception :
   virtual public simple_exception
{
public:


   io_exception(::ca::application * papp);
   io_exception(::ca::application * papp, const char * pszMessage);
   virtual ~io_exception();


};











