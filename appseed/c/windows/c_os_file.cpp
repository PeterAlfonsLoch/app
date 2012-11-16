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



CLASS_DECL_c handle create_file(const char * lpcszFileName, dword dwDesiredAccess, dword dwShareMode, LPSECURITY_ATTRIBUTES lpSA, dword dwCreationDisposition, dword dwFlagsAndAttributes, HANDLE hTemplateFile)
{
   
   return CreateFileW(wstring(lpcszFileName), dwDesiredAccess, dwShareMode, lpSA, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);

}


CLASS_DECL_c bool close_handle(handle h)
{

   return ::CloseHandle(h) != FALSE;

}



CLASS_DECL_c vsstring get_sys_temp_path()
{
   
   wchar_t  wsz[MAX_PATH * 4];
   
   wsz[GetTempPathW(sizeof(wsz) / sizeof(wsz[0]), wsz)] = L'\0';

   return vsstring(wsz);

}



