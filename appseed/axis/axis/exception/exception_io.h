#pragma once


class CLASS_DECL_BASE io_exception :
   virtual public simple_exception
{
public:


   io_exception(sp(::base::application) papp);
   io_exception(sp(::base::application) papp, const char * pszMessage);
   virtual ~io_exception();


};











