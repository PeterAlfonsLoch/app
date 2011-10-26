#include "StdAfx.h"


CLASS_DECL_ca void throw_error_exception(const char * psz)
{
   throw error_exception(psz);
}


error_exception::error_exception(const char * pszError)
{
   m_strError = pszError;
}

error_exception::~error_exception()
{
}

BOOL error_exception::GetErrorMessage(string & str, PUINT pnHelpContext)
{

   UNREFERENCED_PARAMETER(pnHelpContext);

   str = m_strError;

   return TRUE;
}

