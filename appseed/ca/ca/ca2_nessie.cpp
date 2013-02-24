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
      return gen::hex::lo_from(digest, NESSIE_DIGESTBYTES);

   }


   string file::nessie(const char * psz)
   {

      gen::filesp spfile(get_app());
      try
      {
         if(!spfile->open(psz, ::gen::file::type_binary | ::gen::file::mode_read))
            return "";
      }
      catch(gen::file_exception * pe)
      {
         gen::del(pe);
         return "";
      }
      return nessie(spfile);

   }


   string file::nessie(gen:: file * pfile)
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
	  return gen::hex::lo_from(digest, NESSIE_DIGESTBYTES);

   }


} // namespace ca2




