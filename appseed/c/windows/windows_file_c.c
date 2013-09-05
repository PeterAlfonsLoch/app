#include "framework_c.h"



void ensure_file_size(HANDLE h, uint64_t iSize)
{

   DWORD dwHi;

   DWORD dwLo = GetFileSize(h, &dwHi);

   if(((uint64_t) dwLo | ((uint64_t)dwHi << 32)) != iSize)
   {

      LONG l = (iSize >> 32) & 0xffffffff;

      SetFilePointer(h, iSize & 0xffffffff, &l, SEEK_SET);

      SetEndOfFile(h);

   }

}



int_bool close_handle(handle h)
{

   return CloseHandle(h) != FALSE;

}






























