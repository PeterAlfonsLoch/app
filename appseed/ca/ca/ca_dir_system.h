#pragma once


#if defined(METROWIN) || defined(MACOS)
   
#define MATTER_CACHE_FROM_HTTP_SERVER

#endif


namespace zip
{


   class Util;


}


namespace ca
{


   class CLASS_DECL_ca path :
      virtual public ::ca::object

   {
   public:
      virtual bool  is_equal(const char * lpszFilPathA, const char * lpszFilPathB);
   };


   namespace dir
   {


      class CLASS_DECL_ca system :
         virtual public ::ca::object
      {
      public:



         class CLASS_DECL_ca is_dir
         {
         public:


            bool        m_bIsDir;
            uint32_t       m_dwLastCheck;
            uint32_t       m_dwError;


         };


         class CLASS_DECL_ca is_dir_map :
            virtual public string_map < is_dir >
         {
         public:


            mutex             m_mutex;
            uint32_t             m_dwTimeOut;


            is_dir_map(::ca::applicationsp papp);


            bool lookup(const string & strPath, bool &bIsDir, uint32_t & dwLastError);
            bool lookup(const string & strPath, bool &bIsDir, uint32_t & dwLastError, int32_t iLast);
            bool lookup(const char * pszPath, bool &bIsDir, uint32_t &dwLastError);
            void set(const char * pszPath, bool bIsDir, uint32_t dwLastError);
            void set(const string & strPath, bool bIsDir, uint32_t dwLastError);


         };


         zip::Util *       m_pziputil;
         is_dir_map        m_isdirmap;
         mutex             m_mutex;


         system(::ca::applicationsp papp);
         virtual ~system();


         virtual class path & path();


         virtual string path(const string & strFolder, const string & strRelative, bool bUrl);
         virtual string path(const string & strFolder, const string & strRelative, const string & str2, bool bUrl);

         virtual string path(const char * pszFolder, strsize iLenFolder, const char * pszRelative, strsize iLenRelative, const char * psz2, strsize iLen2, bool bUrl);

         virtual string path(const string & strFolder, const string & strRelative);
         virtual string path(const string & strFolder, const string & strRelative, const char * psz2);
         virtual string path(const string & strFolder, const string & strRelative, const string & str2);

         virtual string path(const char * pszFolder, strsize iLenFolder, const char * pszRelative, strsize iLenRelative, const char * psz2, strsize iLen2);

         virtual string simple_path(const string & str1, const string & str2);
         virtual string simple_path(const string & str1, const string & str2, const string & str3);


         virtual string relpath(const char * lpcszSource, const char * lpcszRelative, const char * lpcsz2 = ::null());
         virtual void  ls_pattern(::ca::applicationsp papp, const char * lpcsz, const char * lpcszPattern, stringa * pstraPath = ::null(), stringa * pstraTitle = ::null(), array < bool, bool > * pbaIsDir = ::null(), array < int64_t, int64_t > * piaSize = ::null());
         virtual void  ls(::ca::applicationsp papp, const char * lpcsz, stringa * pstraPath = ::null(), stringa * pstraTitle = ::null(), array < bool, bool > * pbaIsDir = ::null(), array < int64_t, int64_t > * piaSize = ::null());
         virtual void  rls_pattern(::ca::applicationsp papp, const char * lpcsz, const char * lpcszPattern, stringa * pstraPath = ::null(), stringa * pstraTitle = ::null(), stringa * pstraRelative = ::null(), array < bool, bool > * pbaIsDir = ::null(), array < int64_t, int64_t > * piaSize = ::null(), e_extract eextract = extract_first);
         virtual void  rls(::ca::applicationsp papp, const char * lpcsz, stringa * pstraPath = ::null(), stringa * pstraTitle = ::null(), stringa * pstraRelative = ::null(), e_extract eextract = extract_first);
         virtual void  rls_dir(::ca::applicationsp papp, const char * lpcsz, stringa * pstraPath = ::null(), stringa * pstraTitle = ::null(), stringa * pstraRelative = ::null());
         virtual void  ls_dir(::ca::applicationsp papp, const char * lpcsz, stringa * pstraPath = ::null(), stringa * pstraTitle = ::null());
         virtual bool  has_subdir(::ca::applicationsp papp, const char * lpcsz);
         virtual void  ls_file(::ca::applicationsp papp, const char * lpcsz, stringa * pstraPath = ::null(), stringa * pstraTitle = ::null());

         virtual bool  is(const char * lpcsz, ::ca::applicationsp papp);
         virtual bool  is(const string & str, ::ca::applicationsp papp);
         virtual bool  is(const var & var, ::ca::applicationsp papp);

         virtual bool  name_is(const char * lpcsz, ::ca::applicationsp papp);
         virtual bool  name_is(const string & str, ::ca::applicationsp papp);
         virtual bool  name_is(const var & var, ::ca::applicationsp papp);

         virtual bool  is_inside(const char * lpcszDir, const char * lpcszPath, ::ca::applicationsp papp);
         virtual bool  is_inside_time(const char * lpcsz, ::ca::applicationsp papp);
         virtual void  root_ones(stringa & stra, ::ca::applicationsp papp);
         virtual bool  mk(const char * lpcsz, ::ca::applicationsp papp);
         virtual bool  rm(::ca::applicationsp papp, const char * psz, bool bRecursive = true);

         virtual string name(const char * psz);

         virtual string time(const char * lpcsz = ::null(), const char * lpcsz2 = ::null());
         virtual string stage(const char * lpcsz = ::null(), const char * lpcsz2 = ::null());
         virtual string stageapp(const char * lpcsz = ::null(), const char * lpcsz2 = ::null());
         virtual string netseed(const char * lpcsz = ::null(), const char * lpcsz2 = ::null());

         virtual string ca2(const char * lpcsz, const char * lpcsz2 = ::null());
         virtual string ca2();
         virtual string ca2(const string & str);
         virtual string ca2(const string & str, const string & str2);
         virtual string ca2(const char * lpcsz, const string & str2);
         virtual string ca2(const string & str, const char * lpcsz2);

         virtual string module(const char * lpcsz = ::null(), const char * lpcsz2 = ::null());
         virtual string ca2module(const char * lpcsz = ::null(), const char * lpcsz2 = ::null());
         virtual void time_square(string &str);
         virtual string time_log(const char * pszId);

         virtual string locale_schema(::ca::applicationsp papp, const string & strLocale, const string & strStyle);
         virtual string locale_schema_matter(::ca::applicationsp papp, const string & strLocale, const string & strStyle);
         virtual string locale_schema_matter(const string & strLocator, const string & strLocale, const string & strStyle);
         virtual string matter(::ca::applicationsp papp, const stringa & stra, bool bDir = false);
         virtual string matter(::ca::applicationsp papp, const string & str, const string & str2, bool bDir = false);
         virtual string matter(::ca::applicationsp papp, const string & str, const char * psz, bool bDir = false);
         virtual string matter(::ca::applicationsp papp, const char * psz, const string & str, bool bDir = false);
         virtual string matter(::ca::applicationsp papp, const char * psz, const char * psz2, bool bDir = false);
         virtual string matter(::ca::applicationsp papp, const string & str, bool bDir = false);
         virtual string matter(::ca::applicationsp papp, const char * psz, bool bDir = false);

         virtual void   matter_ls(::ca::applicationsp papp, const string & str, stringa & stra);
         virtual void   matter_ls_file(::ca::applicationsp papp, const string & str, stringa & stra);

         virtual string matter(::ca::applicationsp papp);

         virtual string matter_from_locator(::user::str_context * pcontext, const string & strLocator);
         virtual string matter_from_locator(::user::str_context * pcontext, const string & strLocator, const string & str);
         virtual string matter_from_locator(::user::str_context * pcontext, const string & strLocator, const string & str, const string & str2);
         virtual void appmatter_locators(string & strRoot, string & strDomain, ::ca::applicationsp papp);
         virtual void appmatter_locators(string & strRoot, string & strDomain, const string & strLibraryName, const string & strAppName);
         virtual void appmatter_locators(string & strRoot, string & strDomain, const string & strAppName);
         virtual string appmatter_locator(::ca::applicationsp papp);
         virtual string appmatter_locator(const string & strLibraryName, const string & strAppName);
         virtual string appmatter_locator(const string & strAppName);
         virtual string base_appmatter_locator(const string & strBase, const string & strLibraryName, const string & strAppName);
         virtual string base_appmatter_locator(const string & strBase, const string & strAppName);



         virtual string trash_that_is_not_trash(const char * psz);

         virtual string appdata(const char * lpcsz = ::null(), const char * lpcsz2 = ::null());

         virtual string usersystemappdata(::ca::applicationsp papp, const char * lpcszPrefix, const char * lpcsz = ::null(), const char * lpcsz2 = ::null());
         virtual string userappdata(::ca::applicationsp papp, const char * lpcsz = ::null(), const char * lpcsz2 = ::null());
         virtual string userdata(::ca::applicationsp papp, const char * lpcsz = ::null(), const char * lpcsz2 = ::null());
         virtual string userfolder(::ca::applicationsp papp, const char * lpcsz = ::null(), const char * lpcsz2 = ::null());
         virtual string default_os_user_path_prefix(::ca::applicationsp papp);
         virtual string default_userappdata(::ca::applicationsp papp, const char * lpcszPrefix, const char * lpcszLogin , const char * pszRelativePath = ::null());
         virtual string default_userdata(::ca::applicationsp papp, const char * lpcszPrefix, const char * lpcszLogin, const char * pszRelativePath = ::null());
         virtual string default_userfolder(::ca::applicationsp papp, const char * lpcszPrefix, const char * lpcszLogin, const char * pszRelativePath = ::null());
         virtual string userquicklaunch(::ca::applicationsp papp, const char * pszRelativePath = ::null(), const char * lpcsz2 = ::null());
         virtual string userprograms(::ca::applicationsp papp, const char * pszRelativePath = ::null(), const char * lpcsz2 = ::null());

         virtual string commonprograms(const char * pszRelativePath = ::null(), const char * lpcsz2 = ::null());

         virtual string pathfind(const char * pszEnv, const char * pszTopic, const char * pszMode, ::ca::applicationsp papp);

         virtual bool initialize();
      };

      typedef ::ca::smart_pointer < system > system_sp;


   } // namespace dir


} // namespace ca
