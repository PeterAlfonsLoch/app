#include "framework.h"


CLASS_DECL_c void ensure_file_size(HANDLE h, int64_t iSize)
{

   DWORD dwHi;

   DWORD dwLo = ::GetFileSize(h, &dwHi);

   if(((uint64_t) dwLo | ((int64_t)dwHi << 32)) != iSize)
   {
      LONG l = (iSize >> 32) & 0xffffffff;
      ::SetFilePointer(h, iSize & 0xffffffff, &l, SEEK_SET);
      SetEndOfFile(h);
   }

}

CLASS_DECL_c DWORD SetFilePointer(HANDLE h, LONG lMove, PLONG plHi, DWORD dwMeth)
{

   LARGE_INTEGER liMove;

   LARGE_INTEGER liRes;

   liRes.LowPart  = 0;

   liRes.HighPart = 0;

   liMove.LowPart = lMove;

   if(plHi != NULL)
   {

      liMove.HighPart = *plHi;

   }
   else
   {

      liMove.HighPart = 0;

   }

   if(!SetFilePointerEx(h, liMove, &liRes, dwMeth))
      throw "SetFilePointer error";

   if(plHi != NULL)
   {
      
      *plHi = liRes.HighPart;

   }

   return liMove.LowPart;


}

CLASS_DECL_c DWORD GetFileSize(HANDLE h, LPDWORD lpdwHi)
{

   FILE_STANDARD_INFO info;
   
   if(!GetFileInformationByHandleEx(h, FileStandardInfo, &info, sizeof(info)))
      throw "GetFileSize Error";

   if(lpdwHi != NULL)
   {
      *lpdwHi = info.EndOfFile.HighPart;
   }

   return info.EndOfFile.LowPart;

}


CLASS_DECL_c DWORD GetFileAttributes(const char * psz)
{

   wstring wstr(psz);
   
   WIN32_FILE_ATTRIBUTE_DATA data;
   
   if(!::GetFileAttributesEx(wstr, GetFileExInfoStandard, &data))
      return INVALID_FILE_ATTRIBUTES;

   return data.dwFileAttributes;

}



CLASS_DECL_c HANDLE FindFirstFile(const wchar_t * pwsz, WIN32_FIND_DATA * pdata)
{

   return FindFirstFileEx(pwsz, FindExInfoStandard, pdata, FindExSearchNameMatch, NULL, 0);

}


CLASS_DECL_c BOOL FileTimeToLocalFileTime(const FILETIME * lpFileTime, LPFILETIME lpLocalFileTime)
{

   SYSTEMTIME st;

   memset(&st, 0, sizeof(st));

   if(FileTimeToSystemTime(lpFileTime, &st))
      return FALSE;

   SYSTEMTIME stLocal;

   memset(&stLocal, 0, sizeof(stLocal));

   if(!SystemTimeToTzSpecificLocalTime(NULL, &st, &stLocal))
      return FALSE;

   if(!SystemTimeToFileTime(&stLocal, lpLocalFileTime))
      return FALSE;


   return TRUE;


}