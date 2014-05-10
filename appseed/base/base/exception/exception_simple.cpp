#include "framework.h"


simple_exception::simple_exception(sp(::base::application) papp) :
   element(papp),
   ::call_stack(papp),
   ::exception::base(papp)
{
}

simple_exception::simple_exception(sp(::base::application) papp, const char * pszMessage) :
   element(papp),
   ::call_stack(papp),
   ::exception::base(papp)
{

   m_strMessage = pszMessage;

}

simple_exception::~simple_exception()
{

}

bool simple_exception::get_error_message(string & str, PUINT pnHelpContext)
{

   str = what();

   return true;

}
