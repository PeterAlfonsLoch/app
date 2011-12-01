#pragma once


CLASS_DECL_c bool spa_get_admin();
CLASS_DECL_c void spa_set_admin(bool bSet);
CLASS_DECL_c vsstring spa_get_id();
CLASS_DECL_c void spa_set_id(const char * psz);
CLASS_DECL_c vsstring spa_get_platform();
CLASS_DECL_c bool is_installed(const char * psz);
