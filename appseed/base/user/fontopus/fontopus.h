#pragma once


#include "fontopus_user_authentication.h"
#include "fontopus_authentication_map.h"


CLASS_DECL_BASE string url_get_server(const char * psz);
CLASS_DECL_BASE string url_get_root(const char * psz);


namespace fontopus
{


   string CLASS_DECL_BASE show_auth_window(::base::application * papp, LPRECT lprect, string & strUsername, string & strSessId, string & strServerId, string & strLoginUrl, string strRequestingServer);
   string CLASS_DECL_BASE get_cred(::base::application * papp, LPRECT lprect, string & strUsername, string & strPassword, string strToken, string strTitle);
   string CLASS_DECL_BASE get_cred(::base::application * papp, string & strUsername, string & strPassword, string strToken);
   void CLASS_DECL_BASE set_cred(::base::application * papp, string strToken, bool bOk, const char * pszUsername = NULL, const char * pszPassword = NULL);


} // namespace fontopus




#include "fontopus_user.h"
#include "fontopus_usera.h"
#include "fontopus_contact_list.h"
#include "fontopus_user_set.h"
#include "fontopus_license.h"
#include "fontopus_validate.h"


#include "fontopus_fontopus.h"







#include "fontopus_login.h"


#include "fontopus_simple_ui.h"




