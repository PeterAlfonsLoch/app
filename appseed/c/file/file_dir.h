#pragma once

#if defined(WINDOWS)
#define PATH_SEPARATOR "\\"
#else
#define PATH_SEPARATOR "/"
#endif


class stringa;

class dir
{
public:



   static CLASS_DECL_c string element(const char * path1 = NULL, const char * path2 = NULL, const char * path3 = NULL, const char * path4 = NULL);
   static CLASS_DECL_c string afterca2();
   static CLASS_DECL_c string module_folder(const char * path = NULL);
   static CLASS_DECL_c string path(const char * path1, const char * path2, const char * path3 = NULL, const char * path4 = NULL, const char * path5 = NULL);
   static CLASS_DECL_c string name(const char * path1);
   static CLASS_DECL_c string appdata(const char * lpcsz);
   static CLASS_DECL_c string userappdata(const char * lpcsz);
   static CLASS_DECL_c bool is(const char * path1);
   static CLASS_DECL_c bool mk(const char * lpcsz);
   static CLASS_DECL_c void ls(stringa & stra, const char *psz);
   static CLASS_DECL_c void ls_dir(stringa & stra, const char *psz);
   static CLASS_DECL_c void rls(stringa & stra, const char *psz);
   static CLASS_DECL_c void rls_dir(stringa & stra, const char *psz);
   static CLASS_DECL_c bool get_ca2_module_folder_dup(char * lpszModuleFolder);
   static CLASS_DECL_c string default_os_user_path_prefix();
   static CLASS_DECL_c string usersystemappdata(const char * lpcszPrefix, const char * lpcsz, const char * lpcsz2);
   static CLASS_DECL_c string default_userappdata(const char * lpcszPrefix, const char * lpcszLogin, const char * pszRelativePath);
   static CLASS_DECL_c string default_userdata(const char * lpcszPrefix, const char * lpcszLogin, const char * pszRelativePath);
   static CLASS_DECL_c string default_userfolder(const char * lpcszPrefix, const char * lpcszLogin, const char * pszRelativePath);
   static CLASS_DECL_c string userfolder(const char * lpcsz, const char * lpcsz2 = NULL);
   static CLASS_DECL_c string pathfind(const char * pszEnv, const char * pszTopic, const char * pszMode);

   

};
