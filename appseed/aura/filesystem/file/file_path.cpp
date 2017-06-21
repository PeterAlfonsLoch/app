
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


   ::file::path app_app(string strPlatform)
   {

#ifdef WINDOWS

      return ::dir::app_app(strPlatform) / "app_app.exe";

#else

      return ::dir::app_app(strPlatform) / "app_app";

#endif

   }


   ::file::path app_appadmin(string strPlatform)
   {

      return ::dir::app_app(strPlatform) / "app_appadmin.exe";

   }


   ::file::path vcredist(string strPlatform)
   {

      return ::dir::app_app(strPlatform) / "vcredist.exe";

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
