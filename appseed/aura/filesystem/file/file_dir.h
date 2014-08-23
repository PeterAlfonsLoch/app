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



   static CLASS_DECL_AURA string element(const char * path1 = NULL, const char * path2 = NULL, const char * path3 = NULL, const char * path4 = NULL);
   static CLASS_DECL_AURA string afterca2();
   static CLASS_DECL_AURA string module_folder(const char * path = NULL);
   static CLASS_DECL_AURA string path(const char * path1, const char * path2, const char * path3 = NULL, const char * path4 = NULL, const char * path5 = NULL);
   static CLASS_DECL_AURA string name(const char * path1);
   static CLASS_DECL_AURA string appdata(const char * lpcsz);
   static CLASS_DECL_AURA string userappdata(const char * lpcsz);
   static CLASS_DECL_AURA bool is(const char * path1);
   static CLASS_DECL_AURA bool mk(const char * lpcsz);
   static CLASS_DECL_AURA void ls(stringa & stra, const char *psz);
   static CLASS_DECL_AURA void ls_dir(stringa & stra, const char *psz);
   static CLASS_DECL_AURA void rls(stringa & stra, const char *psz);
   static CLASS_DECL_AURA void rls_dir(stringa & stra, const char *psz);
   static CLASS_DECL_AURA string get_ca2_module_folder();
   static CLASS_DECL_AURA string get_base_module_folder();
   static CLASS_DECL_AURA string default_os_user_path_prefix();
   static CLASS_DECL_AURA string usersystemappdata(const char * lpcszPrefix, const char * lpcsz, const char * lpcsz2);
   static CLASS_DECL_AURA string default_userappdata(const char * lpcszPrefix, const char * lpcszLogin, const char * pszRelativePath);
   static CLASS_DECL_AURA string default_userdata(const char * lpcszPrefix, const char * lpcszLogin, const char * pszRelativePath);
   static CLASS_DECL_AURA string default_userfolder(const char * lpcszPrefix, const char * lpcszLogin, const char * pszRelativePath);
   static CLASS_DECL_AURA string userfolder(const char * lpcsz, const char * lpcsz2 = NULL);
   static CLASS_DECL_AURA string pathfind(const char * pszEnv, const char * pszTopic, const char * pszMode);

   

};
