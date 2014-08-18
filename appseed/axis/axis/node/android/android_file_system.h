#pragma once


namespace android
{



   class CLASS_DECL_AXIS file_system :
      virtual public ::file::system
   {
   public:


      class CLASS_DECL_AXIS path :
        virtual public ::file::system::path
      {
      public:
         bool is_equal(const char * lpszFilPathA, const char * lpszFilPathB);
         bool eat_end_level(string & str, int32_t iLevelCount, const char * lpSeparator);
         void split(stringa & stra, const char * lpcszPath);
         bool is_relative(const char * psz);
      };

      class file_system::path m_path;


      file_system(sp(::base::application) papp);

      path & path();

      virtual void copy(const char * pszNew, const char * psz, bool bFailIfExists, e_extract eextract, sp(::base::application) app);
      virtual void move(const char * pszNew, const char * psz);
      virtual void del(const char * psz);
      virtual string copy(const char * psz, sp(::base::application) papp);
      virtual string paste(const char * pszLocation, const char * path, sp(::base::application) papp);

      virtual void trash_that_is_not_trash(const char * psz, sp(::base::application) papp);
      virtual void trash_that_is_not_trash(stringa & stra, sp(::base::application) papp);

      virtual string title_(const char * path);
      virtual string name_(const char * path);
      virtual string extension(const char * path);

      virtual var length(const char * path);

      virtual void replace(const char * pszContext, const char * pszFind, const char * pszReplace, sp(::base::application) papp);

      virtual bool exists(const char * path, sp(::base::application) papp);
      virtual bool exists(const string & path, sp(::base::application) papp);

      void  get_ascendants_path(const char * lpcsz, stringa & stra);
      void  get_ascendants_name(const char * lpcsz, stringa & stra);


      string time(sp(::base::application) papp, const char * pszBasePath, int32_t iDepth, const char * pszPrefix = NULL, const char * pszSuffix = NULL);
      string time_square(sp(::base::application) papp, const char * pszPrefix = NULL, const char * pszSuffix = NULL);
      string time_log(sp(::base::application) papp, const char * pszId);

      virtual ::file::buffer_sp time_square_file(sp(::base::application) papp, const char * pszPrefix = NULL, const char * pszSuffix = NULL);
      virtual ::file::buffer_sp get(const char * name, sp(::base::application) papp);


      int32_t filterex_time_square(const char * pszPrefix, stringa & stra);
      bool mk_time(const char * lpcszcandidate);

      string as_string(var varFile, sp(::base::application) papp);
      string as_string(var varFile, var & varQuery, sp(::base::application) papp);
      void as_memory(var varFile, primitive::memory_base & mem, sp(::base::application) papp);
      void lines(stringa & stra, var varFile, sp(::base::application) papp);

      bool put_contents(var varFile, const void * pvoidContents, count count, sp(::base::application) papp);
      bool put_contents(var varFile, const char * lpcszContents, sp(::base::application) papp);
      bool put_contents(var varFile, ::file::reader & file, sp(::base::application) papp);
      bool put_contents(var varFile, primitive::memory & mem, sp(::base::application) papp);
      bool put_contents_utf8(var varFile, const char * lpcszContents, sp(::base::application) papp);

      bool is_read_only(const char * psz);

      string sys_temp(const char * pszName, const char * pszExtension, sp(::base::application) papp);
      string sys_temp_unique(const char * pszName);


      string replace_extension(const char * pszFile, const char * pszExtension);
      void set_extension(string & str, const char * pszExtension);


   };


} // namespace ca2


