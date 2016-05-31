//#include "framework.h"


verisimple_exception::verisimple_exception(const string & strMessage):
object(::get_thread_app()),
::call_stack(::get_thread_app())
{
   
   m_strMessage = strMessage;
   
   debug_print(":verisimple(\"%s\")",strMessage.c_str());

}



verisimple_exception::~verisimple_exception()
{
}



CLASS_DECL_ACE ::file::ostream & operator << (::file::ostream & os,const verisimple_exception & e)
{

   return os << "verisimple_exception(" << e.m_strMessage << ")";

}