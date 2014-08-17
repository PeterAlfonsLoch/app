#include "framework.h"


thread_int_ptr < int_ptr > t_iAvoidParsingException;


parsing_exception::parsing_exception(sp(::base::application) papp,const string & strMessage) :
   element(papp),
   ::call_stack(get_app()),
   ::exception::base(get_app()),
   simple_exception(papp, strMessage)
{

}

parsing_exception::~parsing_exception()
{

}


CLASS_DECL_BASE bool get_avoid_parsing_exception()
{

   return t_iAvoidParsingException != FALSE;

}

CLASS_DECL_BASE bool throw_parsing_exception(const string & strMessage)
{
   
   if(get_avoid_parsing_exception())
      return false;

   throw parsing_exception(::get_thread_app(),strMessage);

   return true;

}



avoid_parsing_exception::avoid_parsing_exception()
{

   m_iBefore = t_iAvoidParsingException;

   t_iAvoidParsingException = TRUE;

}

avoid_parsing_exception::~avoid_parsing_exception()
{

   t_iAvoidParsingException = m_iBefore;

}


