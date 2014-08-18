#include "framework.h"

int_bool dir_mk(const char * lpcsz)
{

#ifdef WINDOWS

   if(dir_is(lpcsz))
      return true;

   string url(lpcsz);
   string tmp;
   string dir;
   index oldpos = -1;
   index pos = url.find("\\");
   string unc("\\\\?\\");
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

   string url(lpcsz);
   string tmp;
   string dir;
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


int_bool dir_is(const char * path1)
{

#ifdef WINDOWS
   string str;

   str = "\\\\?\\";
   str += path1;

   while(str_ends_dup(str, "\\") || str_ends_dup(str, "/"))
   {
      str = str.substr(0, str.length() - 1);
   }

   uint32_t dwFileAttributes = ::GetFileAttributesW(wstring(str));
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

