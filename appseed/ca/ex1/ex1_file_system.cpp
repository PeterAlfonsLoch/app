#include "framework.h"


namespace ex1
{

   file_system::file_system()
   {
   }

   file_system::~file_system()
   {
   }

   bool file_system::ComparePath(const char * lpcsz1, const char * lpcsz2)
   {
      UNREFERENCED_PARAMETER(lpcsz1);
      UNREFERENCED_PARAMETER(lpcsz2);
      return false;
   }

   bool file_system::FullPath(string & str, const char * lpszFileIn)
   {
      if(gen::str::begins_ci(lpszFileIn, "uifs://"))
      {
         str = lpszFileIn;
         return true;
      }
      return false;
   }

   bool file_system::FullPath(wstring & wstrFullPath, const wstring & wstrPath)
   {
      
      if(gen::str::begins_ci_iws(wstrPath, L"uifs://"))
      {
         wstrFullPath = wstrPath;
         return true;
      }

      return false;
   }

   UINT file_system::GetFileTitle(const char * lpszPathName, string & str)
   {
      UNREFERENCED_PARAMETER(lpszPathName);
      UNREFERENCED_PARAMETER(str);
      return 0;
   }

   UINT file_system::GetFileName(const char * lpszPathName, string & str)
   {
      UNREFERENCED_PARAMETER(lpszPathName);
      UNREFERENCED_PARAMETER(str);
      return 0;
   }

   void file_system::GetModuleShortFileName(HINSTANCE hInst, string & strShortName)
   {
      UNREFERENCED_PARAMETER(hInst);
      UNREFERENCED_PARAMETER(strShortName);
   }

   void file_system::normalize(string & str)
   {
      if(str.is_empty())
         return;
      while(str.has_char() &&
         (str.Right(1) == "\\" ||
         str.Right(1) == "/"))
      {
         str = str.Left(str.get_length() - 1);
      }
   }

   int file_system::cmp(const char * psz1, const char * psz2)
   {
      string str1(psz1);
      normalize(str1);
      string str2(psz2);
      normalize(str2);
      return str1.CompareNoCase(str2);
   }


} // namespace ex1