#include "framework.h"
#include "bzlib.h"

const int32_t g_iGzUncompressLen = 1024 * 1024;
char * g_pchGzUncompressBuffer = NULL;



int32_t bzuncompress(LPCSTR lpcszUncompressed, LPCSTR lpcszGzFileCompressed)
{
   if(g_pchGzUncompressBuffer == NULL)
   {
       g_pchGzUncompressBuffer = new char[g_iGzUncompressLen];
   }
   BZFILE * file = BZ2_bzopen(lpcszGzFileCompressed, "rb");
   if (file == NULL)
   {
      //fprintf_dup(stderr_dup, "bzopen error\n");
      return -2;
   }
   string strUn(lpcszUncompressed);
//   strUn += ".tmp";
   _FILE * fileUn = fopen_dup(strUn, "wb+");
   if (fileUn == NULL)
   {
      BZ2_bzclose(file);
      return -1;
   }
   int32_t uncomprLen;
   while((uncomprLen = BZ2_bzread(file, g_pchGzUncompressBuffer, g_iGzUncompressLen)) > 0)
   {
      fwrite_dup(g_pchGzUncompressBuffer, 1, uncomprLen, fileUn);
   }
   fclose_dup(fileUn);
   BZ2_bzclose(file);
//   ::CopyFile(strUn, lpcszUncompressed, FALSE);
//   ::DeleteFile(strUn);
   return 0;
}
