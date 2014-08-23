#include "framework.h"


thread_int_ptr < int_ptr > t_iAvoidNumericParserException;


numeric_parser_exception::numeric_parser_exception(sp(::aura::application) papp,const string & strMessage):
element(papp),
::call_stack(get_app()),
::exception::base(get_app()),
simple_exception(papp,strMessage)
{

}

numeric_parser_exception::~numeric_parser_exception()
{

}


CLASS_DECL_CORE bool get_avoid_numeric_parser_exception()
{

   return t_iAvoidNumericParserException != FALSE;

}

CLASS_DECL_CORE bool throw_numeric_parser_exception(const string & strMessage)
{

   if(get_avoid_numeric_parser_exception())
      return false;

   throw numeric_parser_exception(::get_thread_app(),strMessage);

   return true;

}



avoid_numeric_parser_exception::avoid_numeric_parser_exception()
{

   m_iBefore = t_iAvoidNumericParserException;

   t_iAvoidNumericParserException = TRUE;

}

avoid_numeric_parser_exception::~avoid_numeric_parser_exception()
{

   t_iAvoidNumericParserException = m_iBefore;

}


