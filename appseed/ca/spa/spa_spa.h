#pragma once


CLASS_DECL_ca bool spa_get_admin();
CLASS_DECL_ca void spa_set_admin(bool bSet);
CLASS_DECL_ca string spa_get_id();
CLASS_DECL_ca void spa_set_id(const char * psz);
CLASS_DECL_ca string spa_get_platform();
CLASS_DECL_ca string get_latest_build_number(const char * pszVersion);
CLASS_DECL_ca string fetch_latest_build_number(const char * pszVersion);
CLASS_DECL_ca bool is_installed(const char * pszVersion, const char * pszBuild, const char * pszType, const char * psz, const char * pszLocale, const char * pszSchema);
