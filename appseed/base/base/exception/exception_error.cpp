#include "framework.h"


error_exception::error_exception(sp(::base::application) papp, const char * pszError) :
   element(papp),
   ::call_stack(papp),
   ::exception::base(papp)
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

