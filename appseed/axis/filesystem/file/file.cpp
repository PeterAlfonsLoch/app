#include "framework.h"

//string file_md5_dup(const char * psz)
//{
//   unsigned char * bufMd5 = NULL;
//   FILE * f = fopen(psz,"rb");
//   if(!f)
//      return "";
//   int iBufSize = 1024 * 1024;
//   if(bufMd5 == NULL)
//   {
//      bufMd5 = new unsigned char[iBufSize];
//   }
//   unsigned char * buf = bufMd5;
//   MD5_CTX ctx;
//   MD5_Init(&ctx);
//   UINT_PTR iRead;
//   while((iRead = fread(buf,1,iBufSize,f)) > 0)
//   {
//      MD5_Update(&ctx,buf,iBufSize);
//   }
//   char chbuf[32];
//   MD5_Final((unsigned char *) chbuf, &ctx);
//   fclose(f);
//   string str;
//   for(int i = 0; i < 16; i++)
//   {
//      sprintf(chbuf,"%02x",chbuf[i]);
//      str += chbuf;
//   }
//   return str;
//}
//
