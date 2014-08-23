#include "framework.h"


verisimple_exception::verisimple_exception(const string & strMessage):
element(::get_thread_app()),
::call_stack(::get_thread_app())
{
   
   m_strMessage = strMessage;
   
   printf(":verisimple(\"%s\")",strMessage.c_str());

}



verisimple_exception::~verisimple_exception()
{
}



CLASS_DECL_AURA ::file::output_stream & operator << (::file::output_stream & os,const verisimple_exception & e)
{

   return os << "verisimple_exception(" << e.m_strMessage << ")";

}