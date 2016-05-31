#pragma once


namespace android
{



   class CLASS_DECL_AURA file_system :
      virtual public ::file::system
   {
   public:




      file_system(::ace::application * papp);


      //virtual void copy(const char * pszNew, const char * psz, bool bFailIfExists, e_extract eextract, ::ace::application * app);
      //virtual void move(const char * pszNew, const char * psz);
      //virtual void del(const char * psz);
      //virtual string copy(const char * psz, ::ace::application * papp);
      //virtual string paste(const char * pszLocation, const char * path, ::ace::application * papp);

      //virtual void trash_that_is_not_trash(const char * psz, ::ace::application * papp);
      //virtual void trash_that_is_not_trash(stringa & stra, ::ace::application * papp);

      //virtual string title_(const char * path);
      //virtual string name_(const char * path);
      //virtual string extension(const char * path);

      //virtual var length(const char * path);

      //virtual void replace(const char * pszContext, const char * pszFind, const char * pszReplace, ::ace::application * papp);

      //virtual bool exists(const char * path, ::ace::application * papp);
      //virtual bool exists(const string & path, ::ace::application * papp);

      //void  get_ascendants_path(const char * lpcsz, stringa & stra);
      //void  get_ascendants_name(const char * lpcsz, stringa & stra);


      //string time(::ace::application * papp, const char * pszBasePath, int32_t iDepth, const char * pszPrefix = NULL, const char * pszSuffix = NULL);
      //string time_square(::ace::application * papp, const char * pszPrefix = NULL, const char * pszSuffix = NULL);
      //string time_log(::ace::application * papp, const char * pszId);

      //virtual ::file::buffer_sp time_square_file(::ace::application * papp, const char * pszPrefix = NULL, const char * pszSuffix = NULL);
      //virtual ::file::buffer_sp get(const char * name, ::ace::application * papp);


      //int32_t filterex_time_square(const char * pszPrefix, stringa & stra);
      //bool mk_time(const char * lpcszcandidate);

      //string as_string(var varFile, ::ace::application * papp);
      //string as_string(var varFile, var & varQuery, ::ace::application * papp);
      //void as_memory(var varFile, primitive::memory_base & mem, ::ace::application * papp);
      //void lines(stringa & stra, var varFile, ::ace::application * papp);

      //bool put_contents(var varFile, const void * pvoidContents, count count, ::ace::application * papp);
      //bool put_contents(var varFile, const char * lpcszContents, ::ace::application * papp);
      //bool put_contents(var varFile, ::file::reader & file, ::ace::application * papp);
      //bool put_contents(var varFile, memory & mem, ::ace::application * papp);
      //bool put_contents_utf8(var varFile, const char * lpcszContents, ::ace::application * papp);

      //bool is_read_only(const char * psz);

      //string sys_temp(const char * pszName, const char * pszExtension, ::ace::application * papp);
      //string sys_temp_unique(const char * pszName);


      //string replace_extension(const char * pszFile, const char * pszExtension);
      //void set_extension(string & str, const char * pszExtension);
	  bool update_module_path();

   };


} // namespace ca2


