#include "framework.h"


simple_exception::simple_exception(sp(base_application) papp) :
   element(papp),
   ::call_stack(papp),
   ::exception::base(papp)
{
}

simple_exception::simple_exception(sp(base_application) papp, const char * pszMessage) :
   element(papp),
   ::call_stack(papp),
   ::exception::base(papp)
{

   m_strMessage = pszMessage;

}

simple_exception::~simple_exception()
{

}

string simple_exception::get_error_message()
{

   return m_strMessage;

}
