#pragma once


namespace file
{


   class CLASS_DECL_BASE application :
      public object
   {
   public:


      application();


      virtual void copy(const char * pszNew, const char * psz, bool bFailIfExists = false, e_extract eextract = extract_first);


      virtual void trash_that_is_not_trash(const char * psz);
      virtual void trash_that_is_not_trash(stringa & stra);


      virtual void replace(const char * pszContext, const char * pszFind, const char * pszReplace);

      virtual bool exists(const char * pszPath);
      virtual bool exists(const string & strPath);
      virtual bool exists(const var & var);

      virtual var length(const char * pszPath);
      virtual var length(const string & strPath);
      virtual var length(const var & var);

      string time(const char * pszBasePath, int32_t iDepth = 1, const char * pszPrefix = NULL, const char * pszSuffix = NULL);
      string time_square(const char * pszPrefix = NULL, const char * pszSuffix = NULL);
      string time_log(const char * pszId);


      virtual ::file::buffer_sp time_square_file(const char * pszPrefix = NULL, const char * pszSuffix = NULL);
      virtual ::file::buffer_sp get(const char * name);


      virtual string as_string(var varFile);
      virtual string as_string(var varFile, var & varQuery);
      virtual void as_memory(var varFile, primitive::memory & mem);
      virtual void lines(stringa & stra, var varFile);

      virtual bool put_contents(var varFile, const void * pvoidContents, ::count count);
      virtual bool put_contents(var varFile, const char * lpcszContents);
      virtual bool put_contents(var varFile, ::file::reader & reader);
      virtual bool put_contents(var varFile, primitive::memory & mem);
      virtual bool put_contents_utf8(var varFile, const char * lpcszContents);


      string sys_temp(const char * pszName, const char * pszExtension);


      virtual ::file::buffer_sp get_file(var varFile, UINT nOpenFlags);
      //virtual ::file::byte_stream get_byte_stream(var varFile, UINT nOpenFlags);

      // get a file and if there are exceptions, should show end user friendly messages
      virtual ::file::buffer_sp friendly_get_file(var varFile, UINT nOpenFlags);

   };


} // namespace base











