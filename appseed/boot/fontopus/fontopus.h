#pragma once


#include "fontopus_user_authentication.h"
#include "fontopus_authentication_map.h"


CLASS_DECL_BOOT string url_get_server(const char * psz);
CLASS_DECL_BOOT string url_get_root(const char * psz);


namespace fontopus
{

   
   string CLASS_DECL_BOOT get_server(const char * pszUrl, int32_t iRetry);

   string CLASS_DECL_BOOT show_auth_window(string & strUsername, string & strSessId, string & strServerId, string & strLoginUrl, string strRequestingServer);


} // namespace fontopus