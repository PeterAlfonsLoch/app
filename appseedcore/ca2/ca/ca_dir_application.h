#pragma once

namespace zip
{
   class Util;
}

namespace ca
{

   namespace dir
   {

      class CLASS_DECL_ca application :
         virtual public ::radix::object
      {
      public:

         application();
         virtual ~application();

         virtual string usersystemappdata(const char * lpcszPrefix, const char * lpcsz = NULL, const char * lpcsz2 = NULL);
         virtual string userappdata(const char * lpcsz = NULL, const char * lpcsz2 = NULL);
         virtual string userdata(const char * lpcsz = NULL, const char * lpcsz2 = NULL);
         virtual string userfolder(const char * lpcsz = NULL, const char * lpcsz2 = NULL);
         virtual string default_os_user_path_prefix();
         virtual string default_userappdata(const char * lpcszPrefix, const char * lpcszLogin , const char * pszRelativePath = NULL);
         virtual string default_userdata(const char * lpcszPrefix, const char * lpcszLogin, const char * pszRelativePath = NULL);
         virtual string default_userfolder(const char * lpcszPrefix, const char * lpcszLogin, const char * pszRelativePath = NULL);
         virtual string userquicklaunch(const char * pszRelativePath = NULL, const char * lpcsz2 = NULL);
         virtual string userprograms(const char * pszRelativePath = NULL, const char * lpcsz2 = NULL);

      };

   } // namespace dir

} // namespace ca