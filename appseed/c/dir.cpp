#include "StdAfx.h"
#ifdef WINDOWS
#include <Shlobj.h>
#else
#include <sys/types.h>
#include <sys/stat.h>
#endif

void get_ca2_module_folder_dup(char * lpszModuleFolder)
{

#ifdef WINDOWS

   char lpszModuleFilePath[MAX_PATH * 8];
   HMODULE hmodule = ::GetModuleHandleA("ca.dll");
   if(hmodule == NULL)
      hmodule = ::GetModuleHandleA("spalib.dll");
   GetModuleFileName(hmodule, lpszModuleFilePath, sizeof(lpszModuleFilePath));
   LPTSTR lpszModuleFileName;
   GetFullPathName(lpszModuleFilePath, sizeof(lpszModuleFilePath), lpszModuleFolder, &lpszModuleFileName);
   lpszModuleFolder[lpszModuleFileName - lpszModuleFolder] = '\0';
   if(strlen_dup(lpszModuleFolder) > 0)
   {
      if(lpszModuleFolder[strlen_dup(lpszModuleFolder) - 1] == '\\'
      || lpszModuleFolder[strlen_dup(lpszModuleFolder) - 1] == '/')
      {
         lpszModuleFolder[strlen_dup(lpszModuleFolder) - 1] = '\0';
      }
   }

#else

   strcpy_dup(lpszModuleFolder, "/ca2/");

#endif

}


vsstring dir::beforeca2()
{
   vsstring str;
#ifdef WINDOWS
   char * buf = (char *) ca2_alloc(4096);
   memset_dup(buf, 0, sizeof(buf));
   SHGetSpecialFolderPath(
      NULL,
      buf,
      CSIDL_PROGRAM_FILES,
      FALSE);
   str = buf;
   ca2_free(buf);
#endif
   return str;
}

vsstring dir::ca2(const char * path1, const char * path2, const char * path3, const char * path4)
{
   if(path1 == NULL && path2 == NULL && path3 == NULL && path4 == NULL)
      return dir::path(beforeca2(), "ca2");
   else
      return dir::path(ca2(), path1, path2, path3, path4);
}

bool dir::mk(LPCTSTR lpcsz)
{

#ifdef WINDOWS

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

