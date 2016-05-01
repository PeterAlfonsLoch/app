#pragma once


#if defined(WINDOWS)
#define PATH_SEPARATOR "\\"
#else
#define PATH_SEPARATOR "/"
#endif


namespace dir
{

   CLASS_DECL_AURA string name(string path);
   CLASS_DECL_AURA ::file::path element();
   CLASS_DECL_AURA ::file::path afterca2();
   CLASS_DECL_AURA ::file::path beforeca2();
   CLASS_DECL_AURA ::file::path module();
   CLASS_DECL_AURA ::file::path appdata();
   CLASS_DECL_AURA ::file::path userappdata();
   CLASS_DECL_AURA ::file::path system();
   CLASS_DECL_AURA bool is(const ::file::path & path);
   CLASS_DECL_AURA bool mk(const  ::file::path & path);
   CLASS_DECL_AURA void ls(::file::patha & patha,const ::file::path & path);
   CLASS_DECL_AURA void ls_dir(::file::patha & patha,const ::file::path & path);
   CLASS_DECL_AURA void rls(::file::patha & patha,const ::file::path & path);
   CLASS_DECL_AURA void rls_dir(::file::patha & patha,const ::file::path & path);
   CLASS_DECL_AURA ::file::path ca2_module();
   CLASS_DECL_AURA ::file::path base_module();
   CLASS_DECL_AURA ::file::path default_os_user_path_prefix();
   CLASS_DECL_AURA ::file::path usersystemappdata(const string & lpcszPrefix);
   CLASS_DECL_AURA ::file::path default_userappdata(const string & lpcszPrefix,const string & lpcszLogin);
   CLASS_DECL_AURA ::file::path default_userdata(const string & lpcszPrefix,const string & lpcszLogin);
   CLASS_DECL_AURA ::file::path default_user(const string & lpcszPrefix,const string & lpcszLogin);
   CLASS_DECL_AURA ::file::path user();
   CLASS_DECL_AURA ::file::path pathfind(const string & pszEnv, const string & pszTopic, const string & pszMode);
   CLASS_DECL_AURA ::file::path program_files_x86();
   CLASS_DECL_AURA ::file::path a_spa();
   CLASS_DECL_AURA ::file::path stage();
   CLASS_DECL_AURA ::file::path app_install(string strPlatform = "");
   CLASS_DECL_AURA ::file::path sys_temp();

} // namespace dir





