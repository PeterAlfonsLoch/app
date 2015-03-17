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


   void path::split(patha & patha)
   {
      stringa straSeparator;
      straSeparator.add("\\");
      straSeparator.add("/");
      patha.add_smallest_tokens(*this,straSeparator,FALSE);
   }

   patha & path::ascendants_path(patha & straParam) const
   {

      ::file::patha stra;

      ascendants_name(stra);

      ::file::path str;

      if(stra.get_count() > 0)
      {
         str = stra[0];
         straParam.add(str);
      }

      for(int32_t i = 1; i < stra.get_size(); i++)
      {
         str /= stra[i];
         straParam.add(str);
      }
      
      return straParam;

   }


   patha & path::ascendants_name(patha & straParam) const
   {

      stringa straSeparator;

      straSeparator.add("/");
      straSeparator.add("\\");

      straParam.add_smallest_tokens(*this,straSeparator,FALSE);
      if(straParam.get_count() > 0)
      {
         strsize iFind = straParam[0].find(':');
         //if(iFind >= 2)
         //{
         //   straParam[0] += "//";
         //}
         //else if(iFind == 1)
         //{
         //   straParam[0] += "\\";
         //}
      }

      return straParam;

   }


   path path::folder(int i) const
   { 
      
      ::file::path path(*this);
      
      while(i > 0)
      { 
         
         path = path.folder(); 
         
         i--;

      } 
      
      return path;
   
   }

   
   path & path::go_up()
   {

      return *this = folder();

   }


   path & path::go_up(int i)
   {

      while(i > 0)
      {

         go_up();

         i--;

      }

      return *this;

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