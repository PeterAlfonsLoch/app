#pragma once


namespace file
{

   
   namespace axis
   {


      class CLASS_DECL_AXIS system:
         virtual public ::file::system
      {
      public:


         system(::aura::application * papp);
         virtual ~system();


         virtual cres copy(const path & pszNew,const path & psz,bool bFailIfExists,e_extract eextract,::aura::application * papp);
         virtual cres move(const path & pszNew,const path & psz,::aura::application * papp);
         virtual cres del(const path & psz,::aura::application * papp);
         virtual path copy(const path & psz,::aura::application * papp);
         virtual path paste(const path & pszLocation,const path & path,::aura::application * papp);

         virtual void trash_that_is_not_trash(const path & psz,::aura::application * papp);
         virtual void trash_that_is_not_trash(const patha & stra,::aura::application * papp);

         //virtual string title_(const char * path);
         //virtual string name_(const char * path);
         //virtual string extension(const char * path);



         virtual ::cres replace(const path & pszContext,const string & pszFind,const string & pszReplace,::aura::application * papp);

         virtual bool exists(const path & path,::aura::application * papp);

         virtual bool exists(const path & path,var * pvarQuery,::aura::application * papp);

         virtual var length(const path & path,::aura::application * papp);

         virtual var length(const path & path,var * pvarQuery,::aura::application * papp);

         //void  get_ascendants_path(const path & lpcsz,patha & stra);
         //void  get_ascendants_name(const path & lpcsz,patha & stra);

         template < class T >
         bool output(::aura::application * papp,const path & pszOutput,T * p,bool (T::*lpfnOuput)(ostream &,const path &),const path & lpszSource);

         template < class T >
         bool output(::aura::application * papp,const path & pszOutput,T * p,bool (T::*lpfnOuput)(ostream &,istream &),const path & lpszInput);

         template < class T >
         bool output(::aura::application * papp,const path & pszOutput,T * p,bool (T::*lpfnOuput)(ostream &,istream &),istream & istream);








         path time(::aura::application * papp,const path & pszBasePath,int32_t iDepth,const string & strPrefix = cnull,const string & pszSuffix = cnull);
         path time_square(::aura::application * papp, const string & pszPrefix = cnull, const string & pszSuffix = cnull);
         path time_log(::aura::application * papp,const string & pszId);

         
         virtual buffer_sp time_square_file(::aura::application * papp,const string & pszPrefix = cnull,const string & pszSuffix = cnull);
         virtual buffer_sp get(const path & name,::aura::application * papp);


         template < class T >
         string time_square(::aura::application * papp,T * p,bool (T::*lpfnOutput)(ostream &,const path &),const path & lpszSource)
         {
            string strTime = time_square(papp);
            if(strTime.has_char())
               if(!output(strTime,p,lpfnOutput,lpszSource))
                  return "";
            return strTime;
         }



         int32_t filterex_time_square(const char * pszPrefix,patha & stra);
         bool mk_time(const path & lpcszCandidate);

         string as_string(var varFile,::aura::application * papp);
         string as_string(var varFile,var & varQuery,::aura::application * papp);
         void as_memory(var varFile,primitive::memory_base & mem,::aura::application * papp);
         void lines(stringa & stra,var varFile,::aura::application * papp);

         bool put_contents(var varFile,const void * pvoidContents,::count count,::aura::application * papp);
         bool put_contents(var varFile,const char * lpcszContents,::aura::application * papp);
         bool put_contents(var varFile,reader & reader,::aura::application * papp);
         bool put_contents(var varFile,memory & mem,::aura::application * papp);
         bool put_contents_utf8(var varFile,const char * lpcszContents,::aura::application * papp);

         
         bool is_read_only(const path & psz);


         path sys_temp(const path & pszName,const string & pszExtension,::aura::application * papp);
         path sys_temp_unique(const path & pszName);


         path replace_extension(const path & pszFile,const string & pszExtension);
         void set_extension(path & str,const string & pszExtension);


         virtual void normalize(path & str);
         virtual int32_t cmp(const path & psz1,const path & psz2);



         virtual string md5(const path & psz);
         virtual string nessie(const path & psz);

         virtual string nessie(buffer_sp  pfile);

         //      path & path36();



         virtual bool is_valid_fileset(const char * pszFile,::aura::application * papp);



         virtual bool resolve_link(path & strTarget,const path & pszSource,sp(::user::primitive) puiMessageParentOptional = NULL);

         //virtual bool get_last_write_time(FILETIME * pfiletime,const string & strFilename);
         using ::file::system::dtf;
         virtual void dtf(const path & pszFile,patha & stra,::aura::application * papp);
         virtual void ftd(const path & pszDir,const ::file::path & pszFile,::aura::application * papp);


         // 'n' (natural) terminated ascii number, example: 245765487n
         virtual void write_n_number(stream_buffer *  pfile,MD5_CTX * pctx,int64_t iNumber);
         virtual void read_n_number(stream_buffer *  pfile,MD5_CTX * pctx,int64_t & iNumber);

         virtual void write_gen_string(stream_buffer *  pfile,MD5_CTX * pctx,string & str);
         virtual void read_gen_string(stream_buffer *  pfile,MD5_CTX * pctx,string & str);

         
         virtual ::file::buffer_sp get_file(var varFile,UINT nOpenFlags,cres * pfesp,::aura::application * papp);


      };


      


   } // namespace axis


} // namespace file





