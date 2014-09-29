#pragma once


#include "fontopus_user_authentication.h"
#include "fontopus_authentication_map.h"


CLASS_DECL_BASE string url_get_server(const char * psz);
CLASS_DECL_BASE string url_get_root(const char * psz);


namespace fontopus
{


   string CLASS_DECL_BASE get_cred(::aura::application * papp, const string & strRequestUrl, const RECT & rect, string & strUsername, string & strPassword, string strToken, string strTitle, bool bInteractive);
   string CLASS_DECL_BASE get_cred(::aura::application * papp, string & strUsername, string & strPassword, string strToken);
   void CLASS_DECL_BASE set_cred(::aura::application * papp,string strToken,const char * pszUsername,const char * pszPassword);
   void CLASS_DECL_BASE set_cred_ok(::aura::application * papp,string strToken,bool bOk);


} // namespace fontopus




#include "fontopus_user.h"
#include "fontopus_usera.h"
#include "fontopus_contact_list.h"
#include "fontopus_user_set.h"
#include "fontopus_licensing.h"
#include "fontopus_validate.h"


#include "fontopus_fontopus.h"







#include "fontopus_login.h"


#include "fontopus_simple_ui.h"




