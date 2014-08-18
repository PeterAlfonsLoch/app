#pragma once

class dir
{
public:



   static CLASS_DECL_AXIS string element(const char * path1 = NULL, const char * path2 = NULL, const char * path3 = NULL, const char * path4 = NULL);
   static CLASS_DECL_AXIS string afterca2();
   static CLASS_DECL_AXIS string module_folder(const char * path = NULL);
   static CLASS_DECL_AXIS string path(const char * path1, const char * path2, const char * path3 = NULL, const char * path4 = NULL, const char * path5 = NULL);
   static CLASS_DECL_AXIS string name(const char * path1);
   static CLASS_DECL_AXIS string appdata(const char * lpcsz);
   static CLASS_DECL_AXIS string userappdata(const char * lpcsz);
   static CLASS_DECL_AXIS void ls(string_array & stra, const char *psz);
   static CLASS_DECL_AXIS void ls_dir(string_array & stra, const char *psz);
   static CLASS_DECL_AXIS void rls(string_array & stra, const char *psz);
   static CLASS_DECL_AXIS void rls_dir(string_array & stra, const char *psz);
   static CLASS_DECL_AXIS string get_ca2_module_folder();
   static CLASS_DECL_AXIS string get_base_module_folder();
   static CLASS_DECL_AXIS string default_os_user_path_prefix();
   static CLASS_DECL_AXIS string usersystemappdata(const char * lpcszPrefix, const char * lpcsz, const char * lpcsz2);
   static CLASS_DECL_AXIS string default_userappdata(const char * lpcszPrefix, const char * lpcszLogin, const char * pszRelativePath);
   static CLASS_DECL_AXIS string default_userdata(const char * lpcszPrefix, const char * lpcszLogin, const char * pszRelativePath);
   static CLASS_DECL_AXIS string default_userfolder(const char * lpcszPrefix, const char * lpcszLogin, const char * pszRelativePath);
   static CLASS_DECL_AXIS string userfolder(const char * lpcsz, const char * lpcsz2 = NULL);
   static CLASS_DECL_AXIS string pathfind(const char * pszEnv, const char * pszTopic, const char * pszMode);

   

};
