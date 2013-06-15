#pragma once

#if defined(WINDOWS)
#define PATH_SEPARATOR "\\"
#else
#define PATH_SEPARATOR "/"
#endif


class stra_dup;

class dir
{
public:



   static CLASS_DECL_ca vsstring ca2(const char * path1 = NULL, const char * path2 = NULL, const char * path3 = NULL, const char * path4 = NULL);
   static CLASS_DECL_ca vsstring afterca2();
   static CLASS_DECL_ca vsstring module_folder(const char * path = NULL);
   static CLASS_DECL_ca vsstring path(const char * path1, const char * path2, const char * path3 = NULL, const char * path4 = NULL, const char * path5 = NULL);
   static CLASS_DECL_ca vsstring name(const char * path1);
   static CLASS_DECL_ca vsstring appdata(const char * lpcsz);
   static CLASS_DECL_ca vsstring userappdata(const char * lpcsz);
   static CLASS_DECL_ca bool is(const char * path1);
   static CLASS_DECL_ca bool mk(const char * lpcsz);
   static CLASS_DECL_ca void ls(stra_dup & stra, const char *psz);
   static CLASS_DECL_ca void ls_dir(stra_dup & stra, const char *psz);
   static CLASS_DECL_ca void rls(stra_dup & stra, const char *psz);
   static CLASS_DECL_ca void rls_dir(stra_dup & stra, const char *psz);
   static CLASS_DECL_ca bool get_ca2_module_folder_dup(char * lpszModuleFolder);
   static CLASS_DECL_ca vsstring default_os_user_path_prefix();
   static CLASS_DECL_ca vsstring usersystemappdata(const char * lpcszPrefix, const char * lpcsz, const char * lpcsz2);
   static CLASS_DECL_ca vsstring default_userappdata(const char * lpcszPrefix, const char * lpcszLogin, const char * pszRelativePath);
   static CLASS_DECL_ca vsstring default_userdata(const char * lpcszPrefix, const char * lpcszLogin, const char * pszRelativePath);
   static CLASS_DECL_ca vsstring default_userfolder(const char * lpcszPrefix, const char * lpcszLogin, const char * pszRelativePath);
   static CLASS_DECL_ca vsstring userfolder(const char * lpcsz, const char * lpcsz2 = NULL);
   static CLASS_DECL_ca vsstring pathfind(const char * pszEnv, const char * pszTopic, const char * pszMode);

   

};
