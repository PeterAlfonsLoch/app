#include "framework.h"


simple_exception::simple_exception(::ca::applicationsp papp) :
   ca(papp),
   ::call_stack(papp),
   ::base_exception(papp)
{
}

simple_exception::simple_exception(::ca::applicationsp papp, const char * pszMessage) :
   ca(papp),
   ::call_stack(papp),
   ::base_exception(papp)
{

   m_strMessage = pszMessage;

}

simple_exception::~simple_exception()
{

}

vsstring simple_exception::get_error_message()
{

   return m_strMessage;

}
