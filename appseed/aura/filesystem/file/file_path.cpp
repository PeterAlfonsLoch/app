
namespace path
{

   
   ::file::path app_install()
   {

      return ::dir::app_install() / "app.install.exe";

   }

   ::file::path a_spa()
   {

      return ::dir::a_spa() / "a_spa.exe";

   }


   ::file::path a_spaadmin()
   {

      return ::dir::a_spa() / "a_spaadmin.exe";

   }

   ::file::path module()
   {
#ifdef WINDOWSEX

      wchar_t lpszModuleFilePath[MAX_PATH + 1];

      GetModuleFileNameW(NULL,lpszModuleFilePath,MAX_PATH + 1);

      string strModuleFileName(lpszModuleFilePath);

      return strModuleFileName;

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



} // namespace path