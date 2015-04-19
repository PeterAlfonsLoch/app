

#ifdef WINDOWS

#include <Shlobj.h>


void get_program_files_x86(string &str)
{

   hwstring lpszModuleFolder(sizeof(wchar_t) * 8);

   hwstring lpszModuleFilePath(sizeof(wchar_t) * 8);

   SHGetSpecialFolderPathW(
      NULL,
      lpszModuleFilePath,
      CSIDL_PROGRAM_FILES,
      FALSE);
   if(lpszModuleFilePath[wcslen(lpszModuleFilePath) - 1] == '\\'
      || lpszModuleFilePath[wcslen(lpszModuleFilePath) - 1] == '/')
   {
      lpszModuleFilePath[wcslen(lpszModuleFilePath) - 1] = '\0';
   }

   wcscpy(lpszModuleFolder,lpszModuleFilePath);

   str = string(lpszModuleFolder) + str;

}


#endif



namespace aura
{


   string simple_app_launcher::get_executable_path()
   {

      string strAppPath;

      strAppPath = "\\ca2\\";
//#ifdef _M_X64
  //    strAppPath += "stage\\x64\\";
//#else
  //    strAppPath += "stage\\x86\\";
//#endif

  //    strAppPath += "app.exe";
      strAppPath += "spa\\spa.exe";

      get_program_files_x86(strAppPath);

      return strAppPath;

   }

   string simple_app_launcher::get_params()
   {

      string strParameters;

      strParameters = " : app=" + m_strApp;

      return strParameters;

   }


   bool simple_app_launcher::start()
   {

      wstring wstrApp(get_executable_path());

      wstring wstrDir(dir::name(string(wstrApp)));

      wstring wstrParams = get_params();

      STARTUPINFOW si;
      memset(&si,0,sizeof(si));
      si.cb = sizeof(si);
      si.dwFlags = STARTF_USESHOWWINDOW;
      si.wShowWindow = SW_SHOWNORMAL;
      PROCESS_INFORMATION pi;
      memset(&pi,0,sizeof(pi));

      wstring wstrCmdLine = (L"\"" + wstrApp + L"\"" + wstrParams).c_str();

      if(::CreateProcessW((wchar_t *)wstrApp.c_str(),(wchar_t *)wstrCmdLine.c_str(),
         NULL,NULL,FALSE,0,NULL,wstrDir,
         &si,&pi))
         return true;

      return false;

   }


} // namespace aura




