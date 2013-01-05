#include "framework.h"


vsstring crypt_nessie(const char * psz)
{
   vsstring strFormat;
   vsstring str;
//      int32_t i;
   NESSIEstruct ns;
   uint8_t digest[NESSIE_DIGESTBYTES];
   NESSIEinit(&ns);
   NESSIEadd((const byte *) psz, (uint32_t long) (8*strlen(psz)), &ns);
   NESSIEfinalize(&ns, digest);
   char * pszOut = str.alloc(NESSIE_DIGESTBYTES * 2);
   lo_hex_from(pszOut, digest, NESSIE_DIGESTBYTES);
   pszOut[NESSIE_DIGESTBYTES * 2] = '\0';
   return str;
}

   /*
   string file::nessie(const char * psz)
   {
      ex1::filesp spfile(get_app());
      try
      {
         if(!spfile->open(psz, ::ex1::file::type_binary | ::ex1::file::mode_read))
            return "";
      }
      catch(ex1::file_exception * pe)
      {
         gen::del(pe);
         return "";
      }
      return nessie(spfile);
   }

   string file::nessie(ex1:: file * pfile)
   {
      int32_t iBufSize = 1024 * 256;
      uchar * buf = new uchar[iBufSize];
      NESSIEstruct ns;
      NESSIEinit(&ns);
      uint64_t iRead;
      while((iRead = pfile->read(buf, iBufSize)) > 0)
      {
         NESSIEadd(buf, 8*iBufSize, &ns);
      }
      u8 digest[DIGESTBYTES];
      NESSIEfinalize(&ns, digest);
      string str;
      string strFormat;
      for(int32_t i = 0; i < DIGESTBYTES; i++)
      {
         strFormat.Format("%02x", digest[i]);
         str += strFormat;
      }
      delete [] buf;
      return str;
   }

*/



