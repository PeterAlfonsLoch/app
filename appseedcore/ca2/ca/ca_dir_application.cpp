#include "StdAfx.h"

namespace zip
{
   class Util;
}

namespace ca
{

   namespace dir
   {

      application::application()
      {
      }

      application::~application()
      {
      }

      string application::usersystemappdata(const char * lpcszPrefix, const char * lpcsz, const char * lpcsz2)
      {
         return System.dir().usersystemappdata(get_app(), lpcszPrefix, lpcsz, lpcsz2);
      }

      string application::userappdata(const char * lpcsz, const char * lpcsz2)
      {
         return System.dir().userappdata(get_app(), lpcsz, lpcsz2);
      }

      string application::userdata(const char * lpcsz, const char * lpcsz2)
      {
         return System.dir().userdata(get_app(), lpcsz, lpcsz2);
      }

      string application::userfolder(const char * lpcsz, const char * lpcsz2)
      {
         return System.dir().userfolder(get_app(), lpcsz, lpcsz2);
      }

      string application::default_os_user_path_prefix()
      {
         return System.dir().default_os_user_path_prefix(get_app());
      }

      string application::default_userappdata(const char * lpcszPrefix, const char * lpcszLogin , const char * pszRelativePath)
      {
         return System.dir().default_userappdata(get_app(), lpcszPrefix, lpcszLogin, pszRelativePath);
      }

      string application::default_userdata(const char * lpcszPrefix, const char * lpcszLogin, const char * pszRelativePath)
      {
         return System.dir().default_userdata(get_app(), lpcszPrefix, lpcszLogin, pszRelativePath);
      }

      string application::default_userfolder(const char * lpcszPrefix, const char * lpcszLogin, const char * pszRelativePath)
      {
         return System.dir().default_userfolder(get_app(), lpcszPrefix, lpcszLogin, pszRelativePath);
      }

      string application::userquicklaunch(const char * pszRelativePath, const char * lpcsz2)
      {
         return System.dir().userquicklaunch(get_app(), pszRelativePath, lpcsz2);
      }

      string application::userprograms(const char * pszRelativePath, const char * lpcsz2)
      {
         return System.dir().userprograms(get_app(), pszRelativePath, lpcsz2);
      }


   } // namespace dir

} // namespace ca