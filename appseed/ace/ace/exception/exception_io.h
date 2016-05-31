#pragma once


class CLASS_DECL_AURA io_exception :
   virtual public simple_exception
{
public:


   io_exception(::ace::application * papp);
   io_exception(::ace::application * papp, const char * pszMessage);
   virtual ~io_exception();


};











