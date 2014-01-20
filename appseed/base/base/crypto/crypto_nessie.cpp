#include "framework.h"


string crypt_nessie(const char * psz)
{

   NESSIEstruct ns;
   
   uint8_t digest[NESSIE_DIGESTBYTES];
   
   NESSIEinit(&ns);
   
   NESSIEadd((const byte *) psz, (uint_ptr) (8*strlen(psz)), &ns);
   
   NESSIEfinalize(&ns, digest);

   return hex::lower_from(digest, NESSIE_DIGESTBYTES);

}


   /*
   string file::nessie(const char * psz)
   {
      ::ca::binary_buffer_sp spfile(allocer());
      try
      {
         if(!spfile->open(psz, ::ca::file::type_binary | ::ca::file::mode_read))
            return "";
      }
      catch(::ca::file_exception * pe)
      {
         ::ca::del(pe);
         return "";
      }
      return nessie(spfile);
   }

   string file::nessie(::ca:: file * pfile)
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





namespace crypto
{


   string crypto::nessie(const char * psz)
   {

      string strFormat;
      string str;
      //      int32_t i;
      NESSIEstruct ns;
      uint8_t digest[NESSIE_DIGESTBYTES];
      NESSIEinit(&ns);
      NESSIEadd((const byte *)psz, (uint_ptr)(8 * strlen(psz)), &ns);
      NESSIEfinalize(&ns, digest);
      return ::hex::lower_from(digest, NESSIE_DIGESTBYTES);

   }



} // namespace crypto


namespace file
{

   string system::nessie(const char * psz)
   {

      ::file::binary_buffer_sp spfile(allocer());
      try
      {
         if (!spfile->open(psz, ::file::type_binary | ::file::mode_read))
            return "";
      }
      catch (::file::exception &)
      {
         return "";
      }
      return nessie(spfile);

   }


   string system::nessie(::file::buffer_sp  pfile)
   {

      int32_t iBufSize = 1024 * 256;
      uchar * buf = new uchar[iBufSize];
      NESSIEstruct ns;
      NESSIEinit(&ns);
      uint64_t iRead;
      while ((iRead = pfile->read(buf, iBufSize)) > 0)
      {
         NESSIEadd(buf, 8 * iBufSize, &ns);
      }
      uint8_t digest[NESSIE_DIGESTBYTES];
      NESSIEfinalize(&ns, digest);
      return ::hex::lower_from(digest, NESSIE_DIGESTBYTES);

   }

} // namespace file