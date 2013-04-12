#pragma once


class CLASS_DECL_ca2 io_exception :
   virtual public simple_exception
{
public:


   io_exception(sp(::ca::application) papp);
   io_exception(sp(::ca::application) papp, const char * pszMessage);
   virtual ~io_exception();


};











