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

