#include "framework.h"



bool base_session::is_session()
{

   return true;

}

sp(::base_application) base_session::start_application(const char * pszType, const char * pszAppId, sp(::create_context) pcreatecontext)
{

   throw interface_only_exception(this);

   return NULL;

}
