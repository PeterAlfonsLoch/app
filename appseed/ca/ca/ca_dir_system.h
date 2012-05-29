#pragma once


namespace zip
{


   class Util;


}


namespace ca
{


   class CLASS_DECL_ca path :
      virtual public ::radix::object

   {
   public:
      virtual bool  is_equal(const char * lpszFilPathA, const char * lpszFilPathB);
   };


   namespace dir
   {


      class CLASS_DECL_ca system :
         virtual public ::radix::object
      {
      public:



         class CLASS_DECL_ca is_dir
         {
         public:


            bool        m_bIsDir;
            DWORD       m_dwLastCheck;


         };


         class CLASS_DECL_ca is_dir_map :
            virtual public ::collection::string_map < is_dir >
         {
         public:


            mutex             m_mutex;
            DWORD             m_dwTimeOut;


            is_dir_map();


            bool lookup(const string & strPath, bool &bIsDir);
            bool lookup(const string & strPath, bool &bIsDir, int iLast);
            bool lookup(const char * pszPath, bool &bIsDir);
            void set(const char * pszPath, bool bIsDir);
            void set(const string & strPath, bool bIsDir);


         };


         zip::Util *       m_pziputil;
         is_dir_map        m_isdirmap;
         mutex             m_mutex;


         system(::ca::application * papp);
         virtual ~system();


         virtual class path & path();


         virtual string path(const string & strFolder, const string & strRelative, bool bUrl);
         virtual string path(const string & strFolder, const string & strRelative, const string & str2, bool bUrl);

         virtual string path(const char * pszFolder, int iLenFolder, const char * pszRelative, int iLenRelative, const char * psz2, int iLen2, bool bUrl);

         virtual string path(const string & strFolder, const string & strRelative);
         virtual string path(const string & strFolder, const string & strRelative, const char * psz2);
         virtual string path(const string & strFolder, const string & strRelative, const string & str2);

         virtual string path(const char * pszFolder, int iLenFolder, const char * pszRelative, int iLenRelative, const char * psz2, int iLen2);

         virtual string simple_path(const string & str1, const string & str2);
         virtual string simple_path(const string & str1, const string & str2, const string & str3);


         virtual string relpath(const char * lpcszSource, const char * lpcszRelative, const char * lpcsz2 = NULL);
         virtual void  ls_pattern(::ca::application * papp, const char * lpcsz, const char * lpcszPattern, stringa * pstraPath = NULL, stringa * pstraTitle = NULL, base_array < bool, bool > * pbaIsDir = NULL, base_array < int64_t, int64_t > * piaSize = NULL);
         virtual void  ls(::ca::application * papp, const char * lpcsz, stringa * pstraPath = NULL, stringa * pstraTitle = NULL, base_array < bool, bool > * pbaIsDir = NULL, base_array < int64_t, int64_t > * piaSize = NULL);
         virtual void  rls_pattern(::ca::application * papp, const char * lpcsz, const char * lpcszPattern, stringa * pstraPath = NULL, stringa * pstraTitle = NULL, stringa * pstraRelative = NULL, base_array < bool, bool > * pbaIsDir = NULL, base_array < int64_t, int64_t > * piaSize = NULL, e_extract eextract = extract_first);
         virtual void  rls(::ca::application * papp, const char * lpcsz, stringa * pstraPath = NULL, stringa * pstraTitle = NULL, stringa * pstraRelative = NULL, e_extract eextract = extract_first);
         virtual void  rls_dir(::ca::application * papp, const char * lpcsz, stringa * pstraPath = NULL, stringa * pstraTitle = NULL, stringa * pstraRelative = NULL);
         virtual void  ls_dir(::ca::application * papp, const char * lpcsz, stringa * pstraPath = NULL, stringa * pstraTitle = NULL);
         virtual bool  has_subdir(::ca::application * papp, const char * lpcsz);
         virtual void  ls_file(::ca::application * papp, const char * lpcsz, stringa * pstraPath = NULL, stringa * pstraTitle = NULL);

         virtual bool  is(const char * lpcsz, ::ca::application * papp);
         virtual bool  is(const string & str, ::ca::application * papp);
         virtual bool  is(const var & var, ::ca::application * papp);

         virtual bool  name_is(const char * lpcsz, ::ca::application * papp);
         virtual bool  name_is(const string & str, ::ca::application * papp);
         virtual bool  name_is(const var & var, ::ca::application * papp);

         virtual bool  is_inside(const char * lpcszDir, const char * lpcszPath, ::ca::application * papp);
         virtual bool  is_inside_time(const char * lpcsz, ::ca::application * papp);
         virtual void  root_ones(stringa & stra, ::ca::application * papp);
         virtual bool  mk(const char * lpcsz, ::ca::application * papp);
         virtual bool  rm(::ca::application * papp, const char * psz, bool bRecursive = true);

         virtual string name(const char * psz);

         virtual string votagus(const char * lpcsz = NULL, const char * lpcsz2 = NULL);
         virtual string time(const char * lpcsz = NULL, const char * lpcsz2 = NULL);
         virtual string stage(const char * lpcsz = NULL, const char * lpcsz2 = NULL);
         virtual string stageapp(const char * lpcsz = NULL, const char * lpcsz2 = NULL);
         virtual string netseed(const char * lpcsz = NULL, const char * lpcsz2 = NULL);

         // stage in ccvotagus spalib
         virtual string ca2(const char * lpcsz, const char * lpcsz2 = NULL);
         virtual string ca2();
         virtual string ca2(const string & str);
         virtual string ca2(const string & str, const string & str2);
         virtual string ca2(const char * lpcsz, const string & str2);
         virtual string ca2(const string & str, const char * lpcsz2);

         virtual string sensitive_ccvotagus(const char * lpcsz = NULL, const char * lpcsz2 = NULL);
         virtual string module(const char * lpcsz = NULL, const char * lpcsz2 = NULL);
         virtual string ca2module(const char * lpcsz = NULL, const char * lpcsz2 = NULL);
         virtual void time_square(string &str);
         virtual string time_log(const char * pszId);

         virtual string locale_schema(::ca::application * papp, const string & strLocale, const string & strStyle);
         virtual string locale_schema_matter(::ca::application * papp, const string & strLocale, const string & strStyle);
         virtual string locale_schema_matter(const string & strLocator, const string & strLocale, const string & strStyle);
         virtual string matter(::ca::application * papp, const string & str, const string & str2);
         virtual string matter(::ca::application * papp, const string & str);
         virtual string matter(::ca::application * papp);
         virtual string matter_from_locator(::user::str_context * pcontext, const string & strLocator);
         virtual string matter_from_locator(::user::str_context * pcontext, const string & strLocator, const string & str);
         virtual string matter_from_locator(::user::str_context * pcontext, const string & strLocator, const string & str, const string & str2);
         virtual void appmatter_locators(string & strRoot, string & strDomain, ::ca::application * papp);
         virtual void appmatter_locators(string & strRoot, string & strDomain, const string & strLibraryName, const string & strAppName);
         virtual void appmatter_locators(string & strRoot, string & strDomain, const string & strAppName);
         virtual string appmatter_locator(::ca::application * papp);
         virtual string appmatter_locator(const string & strLibraryName, const string & strAppName);
         virtual string appmatter_locator(const string & strAppName);
         virtual string base_appmatter_locator(const string & strBase, const string & strLibraryName, const string & strAppName);
         virtual string base_appmatter_locator(const string & strBase, const string & strAppName);



         virtual string trash_that_is_not_trash(const char * psz);

         virtual string appdata(const char * lpcsz = NULL, const char * lpcsz2 = NULL);

         virtual string usersystemappdata(::ca::application * papp, const char * lpcszPrefix, const char * lpcsz = NULL, const char * lpcsz2 = NULL);
         virtual string userappdata(::ca::application * papp, const char * lpcsz = NULL, const char * lpcsz2 = NULL);
         virtual string userdata(::ca::application * papp, const char * lpcsz = NULL, const char * lpcsz2 = NULL);
         virtual string userfolder(::ca::application * papp, const char * lpcsz = NULL, const char * lpcsz2 = NULL);
         virtual string default_os_user_path_prefix(::ca::application * papp);
         virtual string default_userappdata(::ca::application * papp, const char * lpcszPrefix, const char * lpcszLogin , const char * pszRelativePath = NULL);
         virtual string default_userdata(::ca::application * papp, const char * lpcszPrefix, const char * lpcszLogin, const char * pszRelativePath = NULL);
         virtual string default_userfolder(::ca::application * papp, const char * lpcszPrefix, const char * lpcszLogin, const char * pszRelativePath = NULL);
         virtual string userquicklaunch(::ca::application * papp, const char * pszRelativePath = NULL, const char * lpcsz2 = NULL);
         virtual string userprograms(::ca::application * papp, const char * pszRelativePath = NULL, const char * lpcsz2 = NULL);

         virtual string commonprograms(const char * pszRelativePath = NULL, const char * lpcsz2 = NULL);
         
         virtual string pathfind(const char * pszEnv, const char * pszTopic, const char * pszMode, ::ca::application * papp);

         virtual bool initialize();
      };

      typedef ::ca::smart_pointer < system > system_sp;


   } // namespace dir


} // namespace ca
