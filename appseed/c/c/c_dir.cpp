#include "framework.h"
#ifdef WINDOWS
#define SECURITY_WIN32
#include <Shlobj.h>
#include <Security.h>
#else
#include <dirent.h>
#include <sys/stat.h>
#endif


#ifdef LINUX
#include <dlfcn.h>
#include <link.h>
#include <ctype.h>
#elif defined(MACOS)
#include <dlfcn.h>
#include <mach-o/dyld.h>
#endif



#ifdef WINDOWSEX


bool CLASS_DECL_c SHGetSpecialFolderPath(oswindow oswindow, vsstring &str, int32_t csidl, bool fCreate)
{

   return ::SHGetSpecialFolderPathW(oswindow, wstringtovss(str, MAX_PATH * 8), csidl, fCreate) != FALSE;

}


#endif


#ifdef WINDOWS


bool __win_file_find_is_dots(WIN32_FIND_DATA & data)
{

   if (data.cFileName[0] == '.')
   {

      if (data.cFileName[1] == '\0' ||
         (data.cFileName[1] == '.' &&
         data.cFileName[2] == '\0'))
      {

         return true;

      }

   }

   return false;

}


#endif


bool dir::get_ca2_module_folder_dup(char * lpszModuleFolder)
{

#if defined(METROWIN)

   return "";

   char lpszModuleFilePath[MAX_PATH * 8];

   HMODULE hmodule = ::LoadPackagedLibrary(L"ca.dll", 0);

   if(hmodule == NULL)
      hmodule = ::LoadPackagedLibrary(L"spalib.dll", 0);

   if(hmodule == NULL)
   {

      vsstring buf;

      throw metrowin_todo();
      //HRESULT hr = SHGetKnownFolderPath(FOLDERID_ProgramFiles, KF_FLAG_NO_ALIAS, NULL, wstringtovss(buf, 4096));
      //if(FAILED(hr))
      // throw "dir::get_ca2_module_folder_dup : SHGetKnownFolderPath failed";

      strcpy(lpszModuleFilePath, buf.m_psz);

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

   throw metrowin_todo();
   //GetModuleFileName(hmodule, lpszModuleFilePath, sizeof(lpszModuleFilePath));

   // xxx   LPTSTR lpszModuleFileName;

   throw metrowin_todo();
   //GetFullPathName(lpszModuleFilePath, sizeof(lpszModuleFilePath), lpszModuleFolder, &lpszModuleFileName);

   throw metrowin_todo();
   //lpszModuleFolder[lpszModuleFileName - lpszModuleFolder] = '\0';

   throw metrowin_todo();
   /*
   if(strlen_dup(lpszModuleFolder) > 0)
   {

   if(lpszModuleFolder[strlen_dup(lpszModuleFolder) - 1] == '\\' || lpszModuleFolder[strlen_dup(lpszModuleFolder) - 1] == '/')
   {

   lpszModuleFolder[strlen_dup(lpszModuleFolder) - 1] = '\0';

   }

   }
   */

   return true;

#elif defined(WINDOWS)

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


#else

   strcpy_dup(lpszModuleFolder, "/ca2/");



#endif

   return true;

}

bool eat_end_level_dup(vsstring & str, int32_t iLevelCount, const char * lpSeparator)
{

   strsize iLast = str.length() - 1;

   if(iLast < 0)
      return iLevelCount <= 0;

   while(str[iLast] == '/' || str[iLast] == '\\')
      iLast--;

   for(int32_t i = 0; i < iLevelCount; i++)
   {

      strsize iFind1 = str.rfind('/', iLast);

      strsize iFind2 = str.rfind('\\', iLast);

      strsize iFind = max(iFind1, iFind2);

      if(iFind >= iLast)
         return false;

      if(iFind < 0)
         return false;

      iLast = iFind;

      while(str[iLast] == '/' || str[iLast] == '\\')
         iLast--;

   }

   str = str.substr(0, iLast + 1);

   return true;

}


vsstring ca2_module_folder_dup()
{

#ifdef WINDOWSEX

   char lpszModuleFilePath[MAX_PATH + 1];
   GetModuleFileName(::GetModuleHandleA("ca.dll"), lpszModuleFilePath, MAX_PATH + 1);
   char lpszModuleFolder[MAX_PATH + 1];
   LPTSTR lpszModuleFileName;
   GetFullPathName(lpszModuleFilePath, MAX_PATH + 1, lpszModuleFolder, &lpszModuleFileName);
   return vsstring(lpszModuleFolder, lpszModuleFileName - lpszModuleFolder);

#elif defined(LINUX)

   void * handle = dlopen("libca2ca.so", RTLD_NOW);

   if(handle == NULL)
      return "";

   link_map * plm;

   dlinfo(handle, RTLD_DI_LINKMAP, &plm);

   vsstring strCa2ModuleFolder = ::dir::name(plm->l_name);

   dlclose(handle);

   return strCa2ModuleFolder;

#elif defined(METROWIN)

   return "";
   
#elif defined(MACOS)

   {
      
      char * pszCurDir = getcwd(NULL, 0);
      
      vsstring strCurDir = pszCurDir;
      
      free(pszCurDir);
      
      if(file_exists_dup(::dir::path(strCurDir, "libca2.dylib")))
      {
         return strCurDir;
      }
      
      
      return ::dir::name(::dir::pathfind(getenv("DYLD_LIBRARY_PATH"), "libca2.dylib", "rfs")); // readable - normal file - non zero sized
      
   }
   
#endif


}

vsstring dir::ca(const char * path1, const char * path2, const char * path3, const char * path4)
{

#ifdef WINDOWS

   if(path1 == NULL && path2 == NULL && path3 == NULL && path4 == NULL)
   {

      vsstring str;

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
      for(int32_t i = 0; i < stra.get_count(); i++)
      {
         str += stra[i];
         str += "\\";
      }

      return str;
   }
   else
   {

      return dir::path(ca(), path1, path2, path3, path4);

   }

#else

   vsstring strRelative = ca2_module_folder_dup();

   eat_end_level_dup(strRelative, 2, "/");

   vsstring str = path(getenv("HOME"), ".ca/appdata");

   return path(path(str, "ca2", strRelative), path1, path2, path3, path4);

#endif

}

bool dir::mk(const char * lpcsz)
{

#ifdef WINDOWS

   if(is(lpcsz))
      return true;

   vsstring url(lpcsz);
   vsstring tmp;
   vsstring dir;
   index oldpos = -1;
   index pos = url.find("\\");
   vsstring unc("\\\\?\\");
   while (pos >= 0)
   {
      tmp = url.substr(oldpos + 1, pos - oldpos -1 );
      dir += tmp + "\\";
      wstring wstr(unc + dir);
      uint32_t dw = ::GetFileAttributesW(wstr);
      if(dw == INVALID_FILE_ATTRIBUTES)
      {
         ::CreateDirectoryW(wstr, NULL);
      }
      oldpos = pos;
      pos = url.find("\\", oldpos + 1);

   }
   tmp = url.substr(oldpos + 1);
   dir += tmp + "\\";
   wstring wstr(unc + dir);
   if(::GetFileAttributesW(wstr) == INVALID_FILE_ATTRIBUTES)
   {
      ::CreateDirectoryW(wstr, NULL);
   }
   return true;

#else

   // stat -> Sir And Arthur - Serenato
   struct stat st;

   vsstring url(lpcsz);
   vsstring tmp;
   vsstring dir;
   ::index oldpos = -1;
   ::index pos = url.find("/");
   while (pos >= 0)
   {
      tmp = url.substr(oldpos + 1, pos - oldpos -1 );
      dir += tmp + "/";
      if(stat(dir, &st))
      {
         mkdir(dir, S_IRWXU | S_IRWXG | S_IRWXO);
      }
      oldpos = pos;
      pos = url.find("/", oldpos + 1);

   }
   tmp = url.substr(oldpos + 1);
   dir += tmp + "/";
   if(stat(dir, &st))
   {
      mkdir(dir, S_IRWXU | S_IRWXG | S_IRWXO);
   }
   return true;

#endif

}

vsstring dir::module_folder(const char * path1)
{

#ifdef WINDOWSEX

   char path[MAX_PATH * 4];
   if(!GetModuleFileName(NULL, path, sizeof(path)))
   {
      return path1;
   }
   else
   {
      return dir::path(name(path), path1);
   }

#elif defined(METROWIN)

   throw metrowin_todo();
   return path1;

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
#if defined(LINUX) || defined(MACOS)
   str.replace("\\", "/");
#else
   str.replace("/", "\\");
#endif
   return str;
}

bool dir::is(const char * path1)
{

#ifdef WINDOWS

   uint32_t dwFileAttributes = ::GetFileAttributesW(wstring("\\\\?\\") + wstring(path1));
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
#ifdef LINUX
   index iPos = str.rfind('/');
#else
   index iPos = str.rfind('\\');
#endif

   return str.substr(0, iPos + 1);

}

void dir::rls(stra_dup & stra, const char *psz)
{
   ::count start = stra.get_count();
   ls(stra, psz);
   ::count end = stra.get_count();
   for(::index i = start; i < end; i++)
   {
      if(is(stra[i]))
      {
         rls(stra, stra[i]);
      }
   }

}

void dir::rls_dir(stra_dup & stra, const char *psz)
{
   ::count start = stra.get_count();
   ls_dir(stra, psz);
   ::count end = stra.get_count();
   for(::index i = start; i < end; i++)
   {
      rls_dir(stra, stra[i]);
   }

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

      if(strcmp(dp->d_name, "..") == 0)
         continue;
      else if(strcmp(dp->d_name, ".") == 0)
         continue;
      stra.add(path(psz, dp->d_name));

   }

   closedir(dirp);

#elif defined(METROWIN)

   ::Windows::Storage::StorageFolder ^ folder = wait(::Windows::Storage::StorageFolder::GetFolderFromPathAsync(vsstring(psz)));

   if(folder == nullptr)
      return;

   ::Windows::Foundation::Collections::IVectorView < ::Windows::Storage::IStorageItem ^ > ^ a = wait(folder->GetItemsAsync());

   for(uint32_t ui = 0; ui < a->Size; ui++)
   {
      stra.add(begin(a->GetAt(ui)->Path));
   }


#else

   WIN32_FIND_DATA FindFileData;

   HANDLE hFind;

   hFind = FindFirstFile(psz, &FindFileData);

   if (hFind == INVALID_HANDLE_VALUE)
      return;

   while(true)
   {

      if(!__win_file_find_is_dots(FindFileData) && (FindFileData.dwFileAttributes != INVALID_FILE_ATTRIBUTES))
         stra.add(FindFileData.cFileName);

      if(!FindNextFile(hFind, &FindFileData))
         break;

   }

   FindClose(hFind);

#endif


}

void dir::ls_dir(stra_dup & stra, const char *psz)
{

#if defined(LINUX) || defined(MACOS)

   DIR * dirp = opendir(psz);

   if(dirp == NULL)
      return;

   dirent * dp;

   while ((dp = readdir(dirp)) != NULL)
   {
      if(dp->d_name[0] == '.')
      {
         if(dp->d_name[1] == '\0')
            continue;
         if(dp->d_name[1] == '.')
         {
            if(dp->d_name[2] == '\0')
               continue;
         }
      }
      if(is(dp->d_name))
      {
         stra.add(dp->d_name);
      }

   }

   closedir(dirp);

#elif defined(METROWIN)

   ::Windows::Storage::StorageFolder ^ folder = wait(::Windows::Storage::StorageFolder::GetFolderFromPathAsync(vsstring(psz)));

   ::Windows::Foundation::Collections::IVectorView < ::Windows::Storage::StorageFolder ^ > ^ a = wait(folder->GetFoldersAsync());

   for(uint32_t ui = 0; ui < a->Size; ui++)
   {
      stra.add(begin(a->GetAt(ui)->Path));
   }


#else

   WIN32_FIND_DATA FindFileData;

   HANDLE hFind;

   hFind = FindFirstFile(psz, &FindFileData);

   if (hFind == INVALID_HANDLE_VALUE)
      return;

   while(true)
   {

      if(!__win_file_find_is_dots(FindFileData) && (FindFileData.dwFileAttributes != INVALID_FILE_ATTRIBUTES) && (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0)
         stra.add(FindFileData.cFileName);


      stra.add(FindFileData.cFileName);

      if(!FindNextFile(hFind, &FindFileData))
         break;

   }

   FindClose(hFind);

#endif


}

vsstring dir::default_os_user_path_prefix()
{
#if defined(WINDOWSEX)
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

#elif defined(METROWIN)
   vsstring str(Windows::System::UserProfile::UserInformation::GetDomainNameAsync()->GetResults()->Data());
   return str;

#else

   simple_memory mem;

   mem.allocate(512);

retry:

   if(getlogin_r(mem.m_psz, mem.m_iSize))
   {

      if(errno == ERANGE)
      {

         if(mem.m_iSize < 65536)
         {

            mem.allocate(mem.m_iSize + 512);

            goto retry;

         }

      }

      return "";

   }

   return mem.m_psz;

#endif

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

#ifdef WINDOWSEX

   SHGetSpecialFolderPath(NULL, (vsstring &) str, CSIDL_PROFILE, false);

#elif defined(METROWIN)

   str = ::Windows::Storage::KnownFolders::DocumentsLibrary->Path;

#else

   str = getenv("HOME");

#endif

   vsstring strRelative;
   strRelative = ca();
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


vsstring dir::pathfind(const char * pszEnv, const char * pszTopic, const char * pszMode)
{

   stra_dup stra;

   stra.add_tokens(pszEnv, ":");

   vsstring strCandidate;

   for(int32_t i = 0; i < stra.get_count(); i++)
   {

      if(stra[i].is_empty())
         continue;

      strCandidate = path(stra[i], pszTopic);

      if(file_exists_dup(strCandidate))
      {
         return strCandidate;
      }

   }

   return "";

}
