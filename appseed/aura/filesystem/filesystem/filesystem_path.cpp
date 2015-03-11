#include "framework.h"


namespace file
{

#ifdef WINDOWS
   const char * path::s_pszDirSep = "\\/";
   const char * path::s_pszOtherDirSep = "/\\";

#else
   const char * path::s_pszDirSep = "/\\";
   const char * path::s_pszOtherDirSep = "/\\";
#endif


   bool path::is_equal(const path & path) const
   {

      if(((const string &)*this).operator == ((const string &)path)) // undoubtely eaqual...
         return true;

      // find extend equalitys..

      return false;

   }


} // namespace file

namespace url
{

   bool url::is_equal(const url & url) const
   {

      if(((const string &)*this).operator == ((const string &)url)) // undoubtely eaqual...
         return true;

      // find extend equalitys..

      return true;

   }


} // namespace url