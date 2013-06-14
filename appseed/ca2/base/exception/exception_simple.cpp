#include "framework.h"


simple_exception::simple_exception(sp(::ca2::application) papp) :
   ca2(papp),
   ::call_stack(papp),
   ::base_exception(papp)
{
}

simple_exception::simple_exception(sp(::ca2::application) papp, const char * pszMessage) :
   ca2(papp),
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
