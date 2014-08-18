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



   static CLASS_DECL_BASE string element(const char * path1 = NULL, const char * path2 = NULL, const char * path3 = NULL, const char * path4 = NULL);
   static CLASS_DECL_BASE string afterca2();
   static CLASS_DECL_BASE string module_folder(const char * path = NULL);
   static CLASS_DECL_BASE string path(const char * path1, const char * path2, const char * path3 = NULL, const char * path4 = NULL, const char * path5 = NULL);
   static CLASS_DECL_BASE string name(const char * path1);
   static CLASS_DECL_BASE string appdata(const char * lpcsz);
   static CLASS_DECL_BASE string userappdata(const char * lpcsz);
   static CLASS_DECL_BASE bool is(const char * path1);
   static CLASS_DECL_BASE bool mk(const char * lpcsz);
   static CLASS_DECL_BASE void ls(stringa & stra, const char *psz);
   static CLASS_DECL_BASE void ls_dir(stringa & stra, const char *psz);
   static CLASS_DECL_BASE void rls(stringa & stra, const char *psz);
   static CLASS_DECL_BASE void rls_dir(stringa & stra, const char *psz);
   static CLASS_DECL_BASE string get_ca2_module_folder();
   static CLASS_DECL_BASE string get_base_module_folder();
   static CLASS_DECL_BASE string default_os_user_path_prefix();
   static CLASS_DECL_BASE string usersystemappdata(const char * lpcszPrefix, const char * lpcsz, const char * lpcsz2);
   static CLASS_DECL_BASE string default_userappdata(const char * lpcszPrefix, const char * lpcszLogin, const char * pszRelativePath);
   static CLASS_DECL_BASE string default_userdata(const char * lpcszPrefix, const char * lpcszLogin, const char * pszRelativePath);
   static CLASS_DECL_BASE string default_userfolder(const char * lpcszPrefix, const char * lpcszLogin, const char * pszRelativePath);
   static CLASS_DECL_BASE string userfolder(const char * lpcsz, const char * lpcsz2 = NULL);
   static CLASS_DECL_BASE string pathfind(const char * pszEnv, const char * pszTopic, const char * pszMode);

   

};
