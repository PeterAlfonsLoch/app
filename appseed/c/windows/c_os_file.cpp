#include "framework.h"


void ensure_file_size(HANDLE h, int iSize)
{

   if(::GetFileSize(h, &dwHi) != size)
   {
      LONG l = 0;
      ::SetFilePointer(h, size, &l, SEEK_SET);
      SetEndOfFile(h);
   }

}

