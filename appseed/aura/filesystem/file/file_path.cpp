
namespace path
{


   ::file::path app(string strPlatform)
   {

#ifdef WINDOWS

      return ::dir::stage(strPlatform) / "app.exe";

#else

      return ::dir::stage(strPlatform) / "app";

#endif

   }

   ::file::path app_install(string strPlatform)
   {

      return ::dir::app_install(strPlatform) / "app.install.exe";

   }


   ::file::path app_plugin_container(string strPlatform)
   {

      return ::dir::stage(strPlatform) / "app.plugin.container.exe";

   }


   ::file::path a_spa(string strPlatform)
   {

#ifdef WINDOWS

      return ::dir::a_spa(strPlatform) / "a_spa.exe";

#else

      return ::dir::a_spa(strPlatform) / "a_spa";

#endif

   }


   ::file::path a_spaadmin(string strPlatform)
   {

      return ::dir::a_spa(strPlatform) / "a_spaadmin.exe";

   }


   ::file::path vcredist(string strPlatform)
   {

      return ::dir::a_spa(strPlatform) / "vcredist.exe";

   }


   ::file::path module(HMODULE hmodule)
   {
#ifdef WINDOWSEX

      hwstring wstr(MAX_PATH * 8);

      GetModuleFileNameW(hmodule,wstr,(DWORD) wstr.count());

      return solve_relative_compressions(string(wstr));


#elif defined(METROWIN)

      return "m_app.exe";

#else

      char * lpszModuleFilePath = br_find_exe_dir("app");

      if(lpszModuleFilePath == NULL)
         return "";

      string strModuleFileName(lpszModuleFilePath);

      free(lpszModuleFilePath);

      return strModuleFileName;

#endif

   }

   ::file::path install_log(string strPlatform)
   {

      return dir::element() / ("install-" + strPlatform + ".log");

   }

   


} // namespace path
