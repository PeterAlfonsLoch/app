

namespace sz
{

   const char * trim_left(const char * psz,const char * pszTrimmer)
   {

      if(psz == NULL)
         return NULL;

      while((*psz != 0) && (strchr(pszTrimmer,*psz) != NULL))
      {
         psz = ::str::__utf8_inc(psz);
      }

      return psz;

   }

   const char * trim_left_path_sep(const char * psz)
   {

      if(psz == NULL)
         return NULL;

      while((*psz != 0) && (*psz == '\\' || *psz == '/'))
      {
         psz++;
      }

      return psz;

   }

} // namespace sz