#pragma once


class CLASS_DECL_AURA exit_exception : 
   virtual public simple_exception
{
public:

   int      m_iCheck;


   exit_exception(::aura::application * papp, const char * pszMessage = NULL);
   exit_exception(const exit_exception & e);
   virtual ~exit_exception();


};
