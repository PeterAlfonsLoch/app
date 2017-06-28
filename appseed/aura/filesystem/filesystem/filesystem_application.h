#pragma once


namespace file
{


   class CLASS_DECL_AURA application:
      virtual public object
   {
   public:


      application(::aura::application * papp);
      virtual ~application();


      virtual cres copy(const ::file::path & pszNew, const ::file::path & psz, bool bFailIfExists = false, e_extract eextract = extract_first);
      virtual cres move(const ::file::path & pszNew,const ::file::path & psz);
      virtual cres del(const ::file::path & psz);
      virtual cres rename(const ::file::path & pszNew,const ::file::path & psz);


      virtual void trash_that_is_not_trash(const ::file::path & psz);
      virtual void trash_that_is_not_trash(::file::patha & stra);


      virtual cres replace(const ::file::path & pszContext, const string & pszFind, const string & pszReplace);

      virtual bool exists(const ::file::path & pszPath);

      virtual var length(const ::file::path & pszPath);

      ::file::path time(const ::file::path & pszBasePath,int32_t iDepth = 1,const string & pszPrefix = cnull,const string & pszSuffix = cnull);
      ::file::path time_square(const string & pszPrefix = cnull,const string & pszSuffix = cnull);
      ::file::path time_log(const string & pszId);


      virtual ::file::file_sp time_square_file(const char * pszPrefix = NULL, const char * pszSuffix = NULL);
      virtual ::file::file_sp get(const ::file::path & name);


      virtual var as_json(var varFile);
      virtual string as_string(var varFile);
      virtual string as_string(var varFile, var & varQuery);
      virtual void as_memory(var varFile, memory & mem);
      virtual void lines(stringa & stra, var varFile);

      virtual bool put_contents(var varFile, const void * pvoidContents, ::count count);
      virtual bool put_contents(var varFile, const char * lpcszContents);
      virtual bool put_contents(var varFile, ::file::reader & reader);
      virtual bool put_contents(var varFile, memory & mem);
      virtual bool put_contents_utf8(var varFile, const char * lpcszContents);

      virtual bool add_contents(var varFile,const char * lpcszContents);

      string sys_temp(const char * pszName, const char * pszExtension);


      virtual ::file::file_sp get_file(var varFile, UINT nOpenFlags, cres * pfesp = NULL);
      //virtual ::file::byte_stream get_byte_stream(var varFile, UINT nOpenFlags);

      // get a file and if there are exceptions, should show end user friendly messages
      virtual ::file::file_sp friendly_get_file(var varFile, UINT nOpenFlags, cres * pfesp = NULL);


      void dtf(const ::file::path & pszFile,const ::file::path & pszDir);
      void dtf(const ::file::path & pszFile,::file::patha & stra,::file::patha & straRelative);
      void ftd(const ::file::path & pszDir,const ::file::path & pszFile);


      virtual bool crypto_set(var varFile,const char * pszData,const char * pszSalt);
      virtual bool crypto_get(var varFile,string & str,const char * pszSalt);

      virtual bool save(var varFile,::file::serializable & o);
      virtual bool load(::file::serializable & o,var varFile);

      virtual bool save_lines(var varFile,stringa & stra);
      virtual bool load_lines(stringa & stra,var varFile);


      template < class T >
      bool output(const path & pathOut, T * p, bool (T::*lpfnOuput)(ostream &, istream &), const path & pathIn);

      template < class T >
      bool output(const path & pathOut, T * p, bool (T::*lpfnOuput)(ostream &, istream &), file * pfileIn);

      template < class T >
      bool output(const path & pathOut, T * p, bool (T::*lpfnOuput)(ostream &, istream &), istream & is);

      template < class T >
      bool output(file * pfileOut, T * p, bool (T::*lpfnOuput)(ostream &, istream &), const path & pathIn);

      template < class T >
      bool output(file * pfileOut, T * p, bool (T::*lpfnOuput)(ostream &, istream &), file * pfileIn);

      template < class T >
      bool output(file * pfileOut, T * p, bool (T::*lpfnOuput)(ostream &, istream &), istream & is);

      template < class T >
      bool output(ostream & os, T * p, bool (T::*lpfnOuput)(ostream &, istream &), const path & pathIn);

      template < class T >
      bool output(ostream & os, T * p, bool (T::*lpfnOuput)(ostream &, istream &), file * pfileIn);

      template < class T >
      bool output(ostream & os, T * p, bool (T::*lpfnOuput)(ostream &, istream &), istream & is);


      virtual bool transfer(const path & pathOut, const path & pathIn);

      virtual bool transfer(const path & pathOut, file * pfileIn);

      virtual bool transfer(const path & pathOut, istream & is);

      virtual bool transfer(file * pfileOut, const path & pathIn);

      virtual bool transfer(file * pfileOut, file * pfileIn);

      virtual bool transfer(file * pfileOut, istream & is);

      virtual bool transfer(ostream & os, const path & pathIn);

      virtual bool transfer(ostream & os, file * pfileIn);

      virtual bool transfer(ostream & os, istream & is);

      virtual bool touch(const ::file::path & path);


      virtual string md5(var varFile);
      virtual string nessie(var varFile);


   };


   typedef smart_pointer < application > application_sp;


} // namespace axis











