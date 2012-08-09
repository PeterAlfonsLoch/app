#include "framework.h"
#ifdef WINDOWS
#define SECURITY_WIN32
#include <Shlobj.h>
#include <Security.h>
#else
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#endif

bool CLASS_DECL_c SHGetSpecialFolderPath(HWND hwnd, vsstring &str, int csidl, bool fCreate)
{
   return ::SHGetSpecialFolderPathW(hwnd, wstringtovss(str, MAX_PATH * 8), csidl, fCreate) != FALSE;
}


bool dir::get_ca2_module_folder_dup(char * lpszModuleFolder)
{

#ifdef WINDOWS

   char lpszModuleFilePath[MAX_PATH * 8];

   HMODULE hmodule = ::GetModuleHandleA("ca.dll");

   if(hmodule == NULL)
      hmodule = ::GetModuleHandleA("spalib.dll");

   if(hmodule == NULL)
   {

      SHGetSpecialFolderPath(
         NULL,
         lpszModuleFilePath,
         CSIDL_PROGRAM_FILES,
         FALSE);
      if(lpszModuleFilePath[strlen_dup(lpszModuleFilePath) - 1] == '\\'
      || lpszModuleFilePath[strlen_dup(lpszModuleFilePath) - 1] == '/')
      {
         lpszModuleFilePath[strlen_dup(lpszModuleFilePath) - 1] = '\0';
      }
      strcat_dup(lpszModuleFilePath, "\\ca2\\");
#ifdef X86
      strcat_dup(lpszModuleFilePath, "stage\\x86\\");
#else
      strcat_dup(lpszModuleFilePath, "stage\\x64\\");
#endif

      strcpy_dup(lpszModuleFolder, lpszModuleFilePath);

      return true;

   }

   GetModuleFileName(hmodule, lpszModuleFilePath, sizeof(lpszModuleFilePath));

   LPTSTR lpszModuleFileName;

   GetFullPathName(lpszModuleFilePath, sizeof(lpszModuleFilePath), lpszModuleFolder, &lpszModuleFileName);

   lpszModuleFolder[lpszModuleFileName - lpszModuleFolder] = '\0';

   if(strlen_dup(lpszModuleFolder) > 0)
   {

      if(lpszModuleFolder[strlen_dup(lpszModuleFolder) - 1] == '\\' || lpszModuleFolder[strlen_dup(lpszModuleFolder) - 1] == '/')
      {

         lpszModuleFolder[strlen_dup(lpszModuleFolder) - 1] = '\0';

      }

   }

   return true;

#else

   strcpy_dup(lpszModuleFolder, "/ca2/");

#endif

}


vsstring dir::ca2(const char * path1, const char * path2, const char * path3, const char * path4)
{
   if(path1 == NULL && path2 == NULL && path3 == NULL && path4 == NULL)
   {
      vsstring str;
   #ifdef WINDOWS
      char lpszModuleFilePath[MAX_PATH * 10];
      get_ca2_module_folder_dup(lpszModuleFilePath);
      str = lpszModuleFilePath;
      stra_dup stra;
   
      str.replace("/", "\\");
      stra.add_tokens(str, "\\");
      if(stra.get_count() <= 0)
         return "";
      if(stra[stra.get_count() - 1].is_empty())
      {
         stra.remove_at(stra.get_count() - 1);
      }
      if(stra.get_count() <= 0)
         return "";
      stra.remove_at(stra.get_count() - 1);
      if(stra.get_count() <= 0)
         return "";
      stra.remove_at(stra.get_count() - 1);
      if(stra.get_count() <= 0)
         return "";
      str = "";
      for(int i = 0; i < stra.get_count(); i++)
      {
         str += stra[i];
         str += "\\";
      }
   #endif
      return str;
   }
   else
      return dir::path(ca2(), path1, path2, path3, path4);
}

bool dir::mk(LPCTSTR lpcsz)
{

#ifdef WINDOWS

   if(exists(lpcsz))
      return true;

   vsstring url(lpcsz);
   vsstring tmp;
   vsstring dir;
   index oldpos = -1;
   index pos = url.find("\\");
	while (pos >= 0)
	{
      tmp = url.substr(oldpos + 1, pos - oldpos -1 );
		dir += tmp + "\\";
      DWORD dw = GetFileAttributes(dir);
      if(dw == INVALID_FILE_ATTRIBUTES)
      {
         ::CreateDirectory(dir, NULL);
      }
      oldpos = pos;
      pos = url.find("\\", oldpos + 1);

	}
   tmp = url.substr(oldpos + 1);
	dir += tmp + "\\";
   if(GetFileAttributes(dir) == INVALID_FILE_ATTRIBUTES)
   {
      ::CreateDirectory(dir, NULL);
   }
   return true;

#else

// stat -> Sir And Arthur - Serenato
   struct stat st;

   vsstring url(lpcsz);
   vsstring tmp;
   vsstring dir;
   int oldpos = -1;
   int pos = url.find("\\");
	while (pos >= 0)
	{
      tmp = url.substr(oldpos + 1, pos - oldpos -1 );
		dir += tmp + "\\";
      if(stat(dir, &st))
      {
         mkdir(dir, S_IRWXU | S_IRWXG | S_IRWXO);
      }
      oldpos = pos;
      pos = url.find("\\", oldpos + 1);

	}
   tmp = url.substr(oldpos + 1);
	dir += tmp + "\\";
   if(stat(dir, &st))
   {
      mkdir(dir, S_IRWXU | S_IRWXG | S_IRWXO);
   }
   return true;

#endif

}

vsstring dir::module_folder(const char * path1)
{

#ifdef WINDOWS

   char path[MAX_PATH * 4];
   if(!GetModuleFileName(NULL,
      path,
      sizeof(path)))
      return path1;
   else
   {
      return dir::path(name(path), path1);
   }

#else

   return dir::path("/ca2/stage", path1);

#endif

}

vsstring dir::path(const char * path1, const char * path2, const char * path3, const char * path4, const char * path5)
{
   vsstring str(path1);
   if(str.substr(str.length() - 1, 1) == PATH_SEPARATOR)
   {
      str = str.substr(0, str.length() - 1);
   }
   if(path2 != NULL)
   {
      vsstring strAdd(path2);
      if(strAdd.substr(0, 1) != PATH_SEPARATOR)
      {
         strAdd = PATH_SEPARATOR + strAdd;
      }
      str += strAdd;
   }
   if(path3 != NULL)
   {
      vsstring strAdd(path3);
      if(strAdd.substr(0, 1) != PATH_SEPARATOR)
      {
         strAdd = PATH_SEPARATOR + strAdd;
      }
      str += strAdd;
   }
   if(path4 != NULL)
   {
      vsstring strAdd(path4);
      if(strAdd.substr(0, 1) != PATH_SEPARATOR)
      {
         strAdd = PATH_SEPARATOR + strAdd;
      }
      str += strAdd;
   }
   if(path5 != NULL)
   {
      vsstring strAdd(path5);
      if(strAdd.substr(0, 1) != PATH_SEPARATOR)
      {
         strAdd = PATH_SEPARATOR + strAdd;
      }
      str += strAdd;
   }
   str.replace("/", "\\");
   return str;
}

bool dir::exists(const char * path1)
{

#ifdef WINDOWS

   DWORD dwFileAttributes = ::GetFileAttributes(path1);
   if(dwFileAttributes != INVALID_FILE_ATTRIBUTES &&
      dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
      return true;
   else
      return false;

#else

   // dedicaverse stat -> Sir And Arthur - Cesar Serenato

   struct stat st;

   if(stat(path1, &st))
      return false;

   if(!(st.st_mode & S_IFDIR))
      return false;

   return true;

#endif

}

vsstring dir::name(const char * path1)
{
   
   vsstring str;

   str = path1;
   
   index iPos = str.rfind('\\');
   
   return str.substr(0, iPos + 1);

}




void dir::ls(stra_dup & stra, const char *psz)
{

#if defined(LINUX) || defined(MACOS)

   DIR * dirp = opendir(psz);

   if(dirp == NULL)
      return;

   dirent * dp;

   while ((dp = readdir(dirp)) != NULL)
   {

      stra.add(dp->d_name);

   }

   closedir(dirp);

#else

   WIN32_FIND_DATA FindFileData;

   HANDLE hFind;

   hFind = FindFirstFile(psz, &FindFileData);

   if (hFind == INVALID_HANDLE_VALUE) 
      return;

   while(true)
   {

      stra.add(FindFileData.cFileName);

      if(!FindNextFile(hFind, &FindFileData))
         break;

   }

   FindClose(hFind);

#endif


}

vsstring dir::default_os_user_path_prefix()
{
   wchar_t buf[MAX_PATH];
   ULONG ulSize = sizeof(buf) / sizeof(wchar_t);
   if(!::GetUserNameExW(NameCanonical, buf, &ulSize))
   {
      if(!::GetUserNameW(buf, &ulSize))
      {
         memset(buf, 0, sizeof(buf));
      }
   }
   vsstring str;
   str.attach(utf16_to_8(buf));
   return str;
}



vsstring dir::usersystemappdata(const char * lpcszPrefix, const char * lpcsz, const char * lpcsz2)
{
   return path(appdata(lpcszPrefix), lpcsz, lpcsz2);
}



vsstring dir::default_userappdata(const char * lpcszPrefix, const char * lpcszLogin, const char * pszRelativePath)
{
   return path(default_userfolder(lpcszPrefix, lpcszLogin, "appdata"), pszRelativePath);
}

vsstring dir::default_userdata(const char * lpcszPrefix, const char * lpcszLogin, const char * pszRelativePath)
{
   return path(default_userfolder(lpcszPrefix, lpcszLogin, "data"), pszRelativePath);
}

vsstring dir::default_userfolder(const char * lpcszPrefix, const char * lpcszLogin, const char * pszRelativePath)
{

   return userfolder(pszRelativePath);

}



vsstring dir::userfolder(const char * lpcsz, const char * lpcsz2)
{

   vsstring str;
   SHGetSpecialFolderPath(
      NULL,
      (vsstring &) str,
      CSIDL_PROFILE,
      false);


   vsstring strRelative;
   strRelative = ca2();
   index iFind = strRelative.find(':');
   if(iFind >= 0)
   {
      ::index iFind1 = strRelative.rfind('\\', iFind);
      ::index iFind2 = strRelative.rfind('/', iFind);
      ::index iStart = max(iFind1 + 1, iFind2 + 1);
      strRelative = strRelative.substr(0, iFind - 1) + "_" + strRelative.substr(iStart, iFind - iStart) + strRelative.substr(iFind + 1);
   }

   vsstring strUserFolderShift;

   /*if(App(papp).directrix().m_varTopicQuery.has_property("user_folder_relative_path"))
   {
      strUserFolderShift = path(strRelative, App(papp).directrix().m_varTopicQuery["user_folder_relative_path"].get_string());
   }
   else*/
   {
      strUserFolderShift = strRelative;
   }

   return path(path(str, "ca2", strUserFolderShift), lpcsz, lpcsz2);

//      return path(path(str, "ca2"), lpcsz);
/*      if(&AppUser(papp) == NULL)
   {
      string str;
      SHGetSpecialFolderPath(
         NULL,
         str,
         CSIDL_PROFILE,
         FALSE);
      return path(path(str, "ca2\\_____default"), lpcsz);
   }
   else
   {
      return path(AppUser(papp).m_strPath, lpcsz, lpcsz2);
   }*/
}
