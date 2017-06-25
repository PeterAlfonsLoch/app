#pragma once

CLASS_DECL_AXIS bool send_short_message_to_installer(const char * psz, bool bLaunch)
CLASS_DECL_AXIS void installer_call_sync(const char * path, const char * param);
CLASS_DECL_AXIS int32_t app-install.exe(const char * param);
CLASS_DECL_AXIS void send_spaboot_install_response(const char * param);





