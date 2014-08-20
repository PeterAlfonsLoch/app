#include "framework.h"
#include "openssl/whrlpool.h"


string crypt_nessie(const char * psz)
{

   WHIRLPOOL_CTX ns;
   
   unsigned char digest[WHIRLPOOL_DIGEST_LENGTH];
   
   WHIRLPOOL_Init(&ns);
   
   WHIRLPOOL_Update(&ns, psz, strlen(psz));
   
   WHIRLPOOL_Final(digest,&ns);

   return hex::lower_from(digest,WHIRLPOOL_DIGEST_LENGTH);

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

      return ::crypt_nessie(psz);

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

      ::primitive::memory mem(get_app());

      mem.allocate(1024 * 256);

      WHIRLPOOL_CTX ns;

      WHIRLPOOL_Init(&ns);

      file_size iRead;

      while((iRead = pfile->read(mem.get_data(),mem.get_size())) > 0)
      {

         WHIRLPOOL_Update(&ns,mem.get_data(),iRead);

      }

      unsigned char digest[WHIRLPOOL_DIGEST_LENGTH];

      WHIRLPOOL_Final(digest,&ns);

      return ::hex::lower_from(digest,WHIRLPOOL_DIGEST_LENGTH);

   }

} // namespace file