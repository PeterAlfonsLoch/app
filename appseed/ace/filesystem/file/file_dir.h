#pragma once


#if defined(WINDOWS)
#define PATH_SEPARATOR "\\"
#else
#define PATH_SEPARATOR "/"
#endif


namespace dir
{

   CLASS_DECL_ACE string name(string path);
   CLASS_DECL_ACE ::file::path element();
   CLASS_DECL_ACE ::file::path afterca2();
   CLASS_DECL_ACE ::file::path beforeca2();
   CLASS_DECL_ACE ::file::path module();
   CLASS_DECL_ACE ::file::path app_relative();
   CLASS_DECL_ACE ::file::path appdata(); // appdata
   CLASS_DECL_ACE ::file::path userappdata();
   CLASS_DECL_ACE ::file::path app(); // appdata *root* (common to all apps in system or bundle)
   CLASS_DECL_ACE ::file::path system();
   CLASS_DECL_ACE ::file::path root(); // writable root (non-bin, non-exe)
   CLASS_DECL_ACE bool is(const ::file::path & path);
   CLASS_DECL_ACE bool mk(const  ::file::path & path);
   CLASS_DECL_ACE void ls(::file::patha & patha,const ::file::path & path);
   CLASS_DECL_ACE void ls_dir(::file::patha & patha,const ::file::path & path);
   CLASS_DECL_ACE void rls(::file::patha & patha,const ::file::path & path);
   CLASS_DECL_ACE void rls_dir(::file::patha & patha,const ::file::path & path);
   CLASS_DECL_ACE ::file::path ca2_module();
   CLASS_DECL_ACE ::file::path base_module();
   CLASS_DECL_ACE ::file::path default_os_user_path_prefix();
   CLASS_DECL_ACE ::file::path usersystemappdata(const string & lpcszPrefix);
   CLASS_DECL_ACE ::file::path default_userappdata(const string & lpcszPrefix,const string & lpcszLogin);
   CLASS_DECL_ACE ::file::path default_userdata(const string & lpcszPrefix,const string & lpcszLogin);
   CLASS_DECL_ACE ::file::path default_user(const string & lpcszPrefix,const string & lpcszLogin);
   CLASS_DECL_ACE ::file::path user();
   CLASS_DECL_ACE ::file::path pathfind(const string & pszEnv, const string & pszTopic, const string & pszMode);
   CLASS_DECL_ACE ::file::path program_files_x86();
   CLASS_DECL_ACE ::file::path a_spa();
   CLASS_DECL_ACE ::file::path stage();
   CLASS_DECL_ACE ::file::path app_install(string strPlatform = "");
   CLASS_DECL_ACE ::file::path sys_temp();

} // namespace dir





