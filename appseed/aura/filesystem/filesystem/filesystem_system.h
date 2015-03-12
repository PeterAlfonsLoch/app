#pragma once


namespace file
{


   class CLASS_DECL_AURA system :
      virtual public object
   {
   public:


      system(::aura::application * papp);
      virtual ~system();


      virtual cres copy(const path & pszNew,const path & psz,bool bFailIfExists,e_extract eextract,::aura::application * papp);
      virtual cres move(const path & pszNew,const path & psz,::aura::application * papp);
      virtual cres del(const path & psz,::aura::application * papp);
      virtual path copy(const path & psz,::aura::application * papp);
      virtual path paste(const path & pszLocation,const path & path,::aura::application * papp);
      virtual cres rename(const path & pszNew,const path & psz,::aura::application * papp);

      virtual void trash_that_is_not_trash(const path & psz,::aura::application * papp);
      virtual void trash_that_is_not_trash(patha & stra, ::aura::application * papp);

      virtual bool get_status(const path & path,file_status & status,::aura::application * papp);
      virtual cres set_status(const path & path,const file_status & status,::aura::application * papp);

      virtual cres replace(const path & pszContext,const string & pszFind,const string & pszReplace,::aura::application * papp);

      virtual bool exists(const path & path,::aura::application * papp);

      virtual bool exists(const path & path,var * pvarQuery,::aura::application * papp);

      virtual var length(const path & path,::aura::application * papp);

      virtual var length(const path & path,var * pvarQuery,::aura::application * papp);


      template < class T >
      bool output(::aura::application * papp,const path & pszOutput,T * p,bool (T::*lpfnOuput)(ostream &,const path &),const path & lpszSource);

      template < class T >
      bool output(::aura::application * papp,const path & pszOutput,T * p,bool (T::*lpfnOuput)(ostream &,istream &),const path & lpszInput);

      template < class T >
      bool output(::aura::application * papp,const path & pszOutput,T * p,bool (T::*lpfnOuput)(ostream &,istream &),istream & istream);








      path time(::aura::application * papp,const path & pszBasePath,int32_t iDepth,const char * pszPrefix = NULL,const char * pszSuffix = NULL);
      path time_square(::aura::application * papp,const char* pszPrefix = NULL,const char * pszSuffix = NULL);
      path time_log(::aura::application * papp,const char * pszId);

      virtual buffer_sp time_square_file(::aura::application * papp, const char * pszPrefix = NULL, const char * pszSuffix = NULL);
      virtual buffer_sp get(const path & name,::aura::application * papp);

      template < class T >
      string time_square(::aura::application * papp,T * p,bool (T::*lpfnOutput)(ostream &,const path &),const path & lpszSource)
      {
         string strTime = time_square(papp);
         if(strTime.has_char())
            if(!output(strTime, p, lpfnOutput, lpszSource))
               return "";
         return strTime;
      }



      virtual int32_t filterex_time_square(const char * pszPrefix,patha & stra);
      virtual bool mk_time(const char * lpcszCandidate);

      virtual string as_string(var varFile,::aura::application * papp);
      virtual string as_string(var varFile,var & varQuery,::aura::application * papp);
      virtual void as_memory(var varFile,primitive::memory_base & mem,::aura::application * papp);
      virtual void lines(stringa & stra,var varFile,::aura::application * papp);

      virtual bool put_contents(var varFile,const void * pvoidContents,::count count,::aura::application * papp);
      virtual bool put_contents(var varFile,const char * lpcszContents,::aura::application * papp);
      virtual bool put_contents(var varFile,reader & reader,::aura::application * papp);
      virtual bool put_contents(var varFile,primitive::memory & mem,::aura::application * papp);
      virtual bool put_contents_utf8(var varFile,const char * lpcszContents,::aura::application * papp);

      virtual bool add_contents(var varFile,const void * pvoidContents,::count count,::aura::application * papp);
      virtual bool add_contents(var varFile,const char * lpcszContents,::aura::application * papp);

      virtual bool is_read_only(const path & psz);

      virtual path sys_temp(const path & pszName,const char * pszExtension,::aura::application * papp);
      virtual path sys_temp_unique(const path & pszName);


      virtual path replace_extension(const path & pszFile,const char * pszExtension);
      virtual void set_extension(path & str,const char * pszExtension);


      virtual void normalize(string & str);
      virtual int32_t cmp(const path & psz1,const path & psz2);



      virtual string md5(const path & psz);
      virtual string nessie(const path & psz);

      virtual string nessie(buffer_sp  pfile);

      virtual bool is_valid_fileset(const path & pszFile,::aura::application * papp);

      virtual bool resolve_link(string & strTarget,const path & pszSource,sp(::aura::interaction) puiMessageParentOptional = NULL);

      virtual bool get_last_write_time(FILETIME * pfiletime,const string & strFilename);

      virtual void dtf(const path & pszFile,const path & pszDir,::aura::application * papp);

      virtual void dtf(const path & pszFile,patha & stra,::aura::application * papp);

      virtual void ftd(const path & pszDir,const path & pszFile,::aura::application * papp);


   };


   typedef smart_pointer < system > system_sp;




} // namespace file





