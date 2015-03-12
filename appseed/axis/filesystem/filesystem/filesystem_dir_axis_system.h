#pragma once

#ifdef WINDOWSEX
#include "aura/node/windows/windows_dir.h"

#endif


namespace zip
{


   class Util;


}


namespace file
{


   namespace dir
   {


      namespace axis
      {


         class CLASS_DECL_AXIS system:
            virtual public ::file::dir::system
         {
         public:


            zip::Util *       m_pziputil;


            system(::aura::application * papp);
            virtual ~system();


//            virtual class ::file::path & path();


            /*virtual string path(const string & strFolder,const string & strRelative,bool bUrl);
            virtual string path(const string & strFolder,const string & strRelative,const string & str2,bool bUrl);

            virtual string path(const char * pszFolder,strsize iLenFolder,const char * pszRelative,strsize iLenRelative,const char * psz2,strsize iLen2,bool bUrl);
            virtual string path(const char * pszFolder,strsize iLenFolder,const char * pszRelative,strsize iLenRelative,bool bUrl);

            virtual string path(const string & strFolder,const string & strRelative);
            virtual string path(const string & strFolder,const string & strRelative,const char * psz2);
            virtual string path(const string & strFolder,const string & strRelative,const string & str2);

            virtual string path(const char * pszFolder,strsize iLenFolder,const char * pszRelative,strsize iLenRelative,const char * psz2,strsize iLen2);*/

            //virtual string simple_path(const string & str1,const string & str2);
            //virtual string simple_path(const string & str1,const string & str2,const string & str3);

            virtual ::file::listing & ls(::aura::application * papp,listing & listing) override;



            virtual bool  is(const ::file::path & str,::aura::application * papp);

            //virtual bool  has_subdir(::aura::application * papp,const char * lpcsz);

            virtual bool  is_or_definitively_not(bool & bIs,const ::file::path & lpcsz,::aura::application * papp);

            virtual bool  name_is(const ::file::path & str,::aura::application * papp);

            //virtual bool  is_inside(const char * lpcszDir,const char * lpcszPath,::aura::application * papp);
            //virtual bool  is_inside_time(const char * lpcsz,::aura::application * papp);
            //virtual void  root_ones(stringa & patha,stringa & straTitle,::aura::application * papp);
            //virtual bool  mk(const char * lpcsz,::aura::application * papp);
            //virtual bool  rm(::aura::application * papp,const char * psz,bool bRecursive = true);

            //virtual string name(const char * psz);

            //virtual string time(const char * lpcsz = NULL,const char * lpcsz2 = NULL);
            //virtual string stage(const char * lpcsz = NULL,const char * lpcsz2 = NULL);
            //virtual string stageapp(const char * lpcsz = NULL,const char * lpcsz2 = NULL);
            //virtual string netseed(const char * lpcsz = NULL,const char * lpcsz2 = NULL);

            //virtual string element(const char * lpcsz,const char * lpcsz2 = NULL);
            //virtual string element();
            //virtual string element(const string & str);
            //virtual string element(const string & str,const string & str2);
            //virtual string element(const char * lpcsz,const string & str2);
            //virtual string element(const string & str,const char * lpcsz2);

            //virtual string module(const char * lpcsz = NULL,const char * lpcsz2 = NULL);
            //virtual string ca2module(const char * lpcsz = NULL,const char * lpcsz2 = NULL);
            //virtual void time_square(string &str);
            //virtual string time_log(const char * pszId);

            virtual ::file::path locale_schema(::aura::application * papp,const string & strLocale,const string & strStyle);
            virtual ::file::patha locale_schema_matter(::aura::application * papp,const string & strLocale,const string & strStyle,const ::file::path & pathRoot = cnull,const ::file::path & pathDomain = cnull);
            virtual ::file::patha locale_schema_matter(const string & strLocator,const string & strLocale,const string & strStyle);
            virtual ::file::path matter(::aura::application * papp,const ::file::patha & stra,bool bDir = false,const ::file::path & pathRoot = cnull,const ::file::path & pathDomain = cnull);
            virtual ::file::path matter(::aura::application * papp,const ::file::path & str,bool bDir = false,const ::file::path & pathRoot = cnull,const ::file::path & pathDomain = cnull);
            virtual ::file::path matter(::aura::application * papp,const string & str,bool bDir = false,const ::file::path & pathRoot = cnull,const ::file::path & pathDomain = cnull);

            virtual void   matter_ls(::aura::application * papp,const ::file::path & str,::file::patha & stra);
            virtual void   matter_ls_file(::aura::application * papp,const ::file::path & str,::file::patha & stra);

            virtual ::file::path matter(::aura::application * papp);

            //virtual ::file::path matter_from_locator(::aura::str_context * pcontext,const string & strLocator);
            virtual ::file::path matter_from_locator(::aura::str_context * pcontext,const string & strLocator,const ::file::path & str);
            //virtual ::file::path matter_from_locator(::aura::str_context * pcontext,const string & strLocator,const string & str,const string & str2);
            virtual void appmatter_locators(string & strRoot,string & strDomain,::aura::application * papp);
            virtual void appmatter_locators(string & strRoot,string & strDomain,const string & strLibraryName,const string & strAppName);
            virtual void appmatter_locators(string & strRoot,string & strDomain,const string & strAppName);
            virtual ::file::path appmatter_locator(::aura::application * papp);
            virtual ::file::path appmatter_locator(const string & strLibraryName,const string & strAppName);
            virtual ::file::path appmatter_locator(const string & strAppName);
            virtual ::file::path base_appmatter_locator(const ::file::path & strBase,const string & strLibraryName,const string & strAppName);
            virtual ::file::path base_appmatter_locator(const ::file::path & strBase,const string & strAppName);



            //virtual string trash_that_is_not_trash(const char * psz);

            //virtual string appdata(const char * lpcsz = NULL,const char * lpcsz2 = NULL);
            //virtual string commonappdata();
            //virtual string commonappdata(const char * lpcsz,const char * lpcsz2 = NULL);
            //virtual string element_commonappdata(const string & strElement,const char * lpcsz = NULL,const char * lpcsz2 = NULL);

            //virtual string usersystemappdata(::aura::application * papp,const char * lpcszPrefix,const char * lpcsz = NULL,const char * lpcsz2 = NULL);
            //virtual string userappdata(::aura::application * papp,const char * lpcsz = NULL,const char * lpcsz2 = NULL);
            //virtual string userdata(::aura::application * papp,const char * lpcsz = NULL,const char * lpcsz2 = NULL);
            //virtual string userfolder(::aura::application * papp,const char * lpcsz = NULL,const char * lpcsz2 = NULL);
            //virtual string default_os_user_path_prefix(::aura::application * papp);
            //virtual string default_userappdata(::aura::application * papp,const char * lpcszPrefix,const char * lpcszLogin,const char * pszRelativePath = NULL);
            //virtual string default_userdata(::aura::application * papp,const char * lpcszPrefix,const char * lpcszLogin,const char * pszRelativePath = NULL);
            //virtual string default_userfolder(::aura::application * papp,const char * lpcszPrefix,const char * lpcszLogin,const char * pszRelativePath = NULL);
            //virtual string userquicklaunch(::aura::application * papp,const char * pszRelativePath = NULL,const char * lpcsz2 = NULL);
            //virtual string userprograms(::aura::application * papp,const char * pszRelativePath = NULL,const char * lpcsz2 = NULL);

            //virtual string commonprograms(const char * pszRelativePath = NULL,const char * lpcsz2 = NULL);

            //virtual string pathfind(const char * pszEnv,const char * pszTopic,const char * pszMode,::aura::application * papp);

            //virtual bool initialize();

            virtual ::file::path get_api_cc();

         };

         

      } // namespace axis


   } // namespace dir


} // namespace file




















