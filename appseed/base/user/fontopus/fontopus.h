#pragma once


#include "fontopus_user_authentication.h"
#include "fontopus_authentication_map.h"


CLASS_DECL_BASE string url_get_server(const char * psz);
CLASS_DECL_BASE string url_get_root(const char * psz);


namespace fontopus
{


   string CLASS_DECL_BASE show_auth_window(base_application * papp, LPRECT lprect, string & strUsername, string & strSessId, string & strServerId, string & strLoginUrl, string strRequestingServer);


} // namespace fontopus




#include "fontopus_user.h"
#include "fontopus_usera.h"
#include "fontopus_contact_list.h"
#include "fontopus_user_set.h"
#include "fontopus_license.h"
#include "fontopus_validate.h"


#include "fontopus_fontopus.h"




#include "base/base/simple/simple_ui_style.h"
#include "base/user/simple/simple_ui.h"
#include "base/user/simple/simple_label.h"
#include "base/user/simple/simple_edit_box.h"
#include "base/user/simple/simple_password.h"
#include "base/user/simple/simple_tap.h"



#include "fontopus_login.h"



#ifdef WINDOWSEX
#include "base/os/windows/windows_simple_ui.h"
#endif

