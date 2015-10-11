

/////////////////////////////////////////////////////
//
//    md5 implementation
//    intentional duplication because spa
//    needs md5
//
string file_md5_dup(const char * psz)
{
   unsigned char * bufMd5 = NULL;
   FILE * f = fopen(psz,"rb");
   if(!f)
      return "";
   int iBufSize = 1024 * 1024;
   if(bufMd5 == NULL)
   {
      bufMd5 = new unsigned char[iBufSize];
   }
   unsigned char * buf = bufMd5;
   aura::md5 alg;
   UINT_PTR iRead;
   while((iRead = fread(buf,1,iBufSize,f)) > 0)
   {
      alg.update(buf,iRead);
   }
   alg.finalize();
   fclose(f);
   string str;
   char chbuf[32];
   for(int i = 0; i < 16; i++)
   {
      sprintf(chbuf,"%02x",alg.digest()[i]);
      str += chbuf;
   }
   return str;
}
