#pragma once

#pragma once


/*
CLASS_DECL_AXIS void ensure_file_size(int fd, int64_t iSize);
CLASS_DECL_AXIS int64_t get_file_size(int fd);
*/




namespace ios
{
   
   
   class CLASS_DECL_AXIS file_system :
      public ::file::system
   {
   public:
      
      
      class CLASS_DECL_AXIS path :
         public ::file::system::path
      {
      public:
         bool is_equal(const char * lpszFilPathA, const char * lpszFilPathB);
         bool eat_end_level(string & str, int32_t iLevelCount, const char * lpSeparator);
         void split(stringa & stra, const char * lpcszPath);
         bool is_relative(const char * psz);
      };
      

      class file_system::path m_path;
 
      
      file_system(::axis::application * papp);
      
      
      path & path();
      
      
      virtual void copy(const char * pszNew, const char * psz, bool bFailIfExists, e_extract eextract, ::axis::application * papp);
      virtual void move(const char * pszNew, const char * psz);
      virtual void del(const char * psz);
      virtual string copy(const char * psz, ::axis::application * papp);
      virtual string paste(const char * pszLocation, const char * path, ::axis::application * papp);
      
      virtual void trash_that_is_not_trash(const char * psz, ::axis::application * papp);
      virtual void trash_that_is_not_trash(stringa & stra, ::axis::application * papp);
      
      virtual string title_(const char * path);
      virtual string name_(const char * path);
      virtual string extension(const char * path);
      
      virtual var length(const char * path);
      
      virtual void replace(const char * pszContext, const char * pszFind, const char * pszReplace, ::axis::application * papp);
      
      virtual bool exists(const char * path, ::axis::application * papp);
      virtual bool exists(const string & path, ::axis::application * papp);
      
      void  get_ascendants_path(const char * lpcsz, stringa & stra);
      void  get_ascendants_name(const char * lpcsz, stringa & stra);
      
      
      string time(::axis::application * papp, const char * pszBasePath, int32_t iDepth, const char * pszPrefix = NULL, const char * pszSuffix = NULL);
      string time_square(::axis::application * papp, const char * pszPrefix = NULL, const char * pszSuffix = NULL);
      string time_log(::axis::application * papp, const char * pszId);
      
      virtual ::file::buffer_sp time_square_file(::axis::application * papp, const char * pszPrefix = NULL, const char * pszSuffix = NULL);
      virtual ::file::buffer_sp get(const char * name, ::axis::application * papp);
      
      
      int32_t filterex_time_square(const char * pszPrefix, stringa & stra);
      bool mk_time(const char * lpcszCandidate);
      
      string as_string(var varFile, ::axis::application * papp);
      string as_string(var varFile, var & varQuery, ::axis::application * papp);
      void as_memory(var varFile, primitive::memory_base & mem, ::axis::application * papp);
      void lines(stringa & stra, var varFile, ::axis::application * papp);
      
      bool put_contents(var varFile, const void * pvoidContents, count count, ::axis::application * papp);
      bool put_contents(var varFile, const char * lpcszContents, ::axis::application * papp);
      bool put_contents(var varFile, ::file::reader & reader, ::axis::application * papp);
      bool put_contents(var varFile, primitive::memory & mem, ::axis::application * papp);
      bool put_contents_utf8(var varFile, const char * lpcszContents, ::axis::application * papp);
      
      bool is_read_only(const char * psz);
      
      string sys_temp(const char * pszName, const char * pszExtension, ::axis::application * papp);
      string sys_temp_unique(const char * pszName);
      
      
      string replace_extension(const char * pszFile, const char * pszExtension);
      void set_extension(string & str, const char * pszExtension);
      
      
   };
   
      
} // namespace ca2



