#include "framework.h"


namespace ca2
{


   string crypt::nessie(const char * psz)
   {

      string strFormat;
      string str;
//      int32_t i;
      NESSIEstruct ns;
      uint8_t digest[NESSIE_DIGESTBYTES];
      NESSIEinit(&ns);
      NESSIEadd((const byte *) psz, (uint_ptr) (8 * strlen(psz)), &ns);
      NESSIEfinalize(&ns, digest);
      return ::ca2::hex::lo_from(digest, NESSIE_DIGESTBYTES);

   }


   string file_system::nessie(const char * psz)
   {

      ::ca2::filesp spfile(allocer());
      try
      {
         if(!spfile->open(psz, ::ca2::file::type_binary | ::ca2::file::mode_read))
            return "";
      }
      catch(::ca2::file_exception &)
      {
         return "";
      }
      return nessie(spfile);

   }


   string file_system::nessie(sp(::ca2::file) pfile)
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
      uint8_t digest[NESSIE_DIGESTBYTES];
      NESSIEfinalize(&ns, digest);
	  return ::ca2::hex::lo_from(digest, NESSIE_DIGESTBYTES);

   }


} // namespace ca2




