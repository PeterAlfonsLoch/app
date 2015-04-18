

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
#ifdef _M_X64
      strAppPath += "stage\\x64\\";
#else
      strAppPath += "stage\\x86\\";
#endif

      strAppPath += "app.exe";

      get_program_files_x86(strAppPath);

      return strAppPath;

   }

   string simple_app_launcher::get_params()
   {

      string strParameters;

      strParameters = " : app=" + m_strApp;

      return strParameters;

   }


} // namespace aura

