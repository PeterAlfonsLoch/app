#include "framework.h"


error_exception::error_exception(::ca::application * papp, const char * pszError) :
   ca(papp),
   ::call_stack(papp),
   ::base_exception(papp)
{
   m_strError = pszError;
}

error_exception::~error_exception()
{
}

bool error_exception::get_error_message(string & str, PUINT pnHelpContext)
{

   UNREFERENCED_PARAMETER(pnHelpContext);

   str = m_strError;

   return TRUE;
}

