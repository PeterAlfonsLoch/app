//#include "framework.h"
//#include <fcntl.h>


BEGIN_EXTERN_C

int32_t ansi_open(const char * psz,int32_t i)
{
   return _wopen(::str::international::utf8_to_unicode(psz),i);
}

void ansi_get_errno(int32_t * perrno)
{
   *perrno = errno;
}


FILE * ansi_fopen(const char * psz,const char * pszMode)
{
   return _wfopen(::str::international::utf8_to_unicode(psz),::str::international::utf8_to_unicode(pszMode));
}



int ansi_file_flag(int iFlag)
{

   int i = 0;

   if(iFlag & ::file::type_binary)
   {

      i |= _O_BINARY;

   }

   if(iFlag & ::file::mode_read)
   {

      if(iFlag & ::file::mode_write)
      {

         i |= _O_RDWR;

      }
      else
      {

         i |= _O_RDONLY;

      }

   }
   else if(iFlag & ::file::mode_write)
   {

      i |= _O_WRONLY;

   }

   return i;

}

void ansi_unlink(const char * psz)
{

   _unlink(psz);

}


END_EXTERN_C







