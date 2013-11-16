#pragma once


#include "fontopus_user_authentication.h"
#include "fontopus_authentication_map.h"


CLASS_DECL_BOOT string url_get_server(const char * psz);
CLASS_DECL_BOOT string url_get_root(const char * psz);


namespace fontopus
{

   
   string CLASS_DECL_BOOT get_server(const char * pszUrl, int32_t iRetry);

   string CLASS_DECL_BOOT show_auth_window(LPRECT lprect, string & strUsername, string & strSessId, string & strServerId, string & strLoginUrl, string strRequestingServer);

   CLASS_DECL_BOOT void on_lbutton_up(int32_t x, int32_t y);
   CLASS_DECL_BOOT void on_lbutton_down(int32_t x, int32_t y);
   CLASS_DECL_BOOT void on_mouse_move(int32_t x, int32_t y);
   CLASS_DECL_BOOT void on_char(int32_t iKey, const string & strChar);

   CLASS_DECL_BOOT bool get_visible();

#ifdef METROWIN
   CLASS_DECL_BOOT void draw(ID2D1DeviceContext * pctx);
#endif


} // namespace fontopus