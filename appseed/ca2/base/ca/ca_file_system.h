#pragma once


#if defined(WINDOWS)

CLASS_DECL_ca2 bool IsWow64();

#endif



typedef struct MD5state_st MD5_CTX;




namespace ca2
{


   class CLASS_DECL_ca2 file_system :
      public ::ca2::object
   {
   public:

      class CLASS_DECL_ca2 path :
         virtual public ::ca2::object
      {
      public:
         
         file_system * m_pfile;


         bool is_equal(const char * lpszFilPathA, const char * lpszFilPathB);
         bool eat_end_level(string & str, int32_t iLevelCount, const char * lpSeparator);
         void split(stringa & stra, const char * lpcszPath);
         bool is_relative(const char * psz);

         bool rename(const char * pszNew, const char * psz, sp(::ca2::application) papp);

      };

      file_system();

      path & path();

      virtual void copy(const char * pszNew, const char * psz, bool bFailIfExists, e_extract eextract, sp(::ca2::application) app);
      virtual void move(const char * pszNew, const char * psz);
      virtual void del(const char * psz);
      virtual string copy(const char * psz, sp(::ca2::application) papp);
      virtual string paste(const char * pszLocation, const char * path, sp(::ca2::application) papp);

      virtual void trash_that_is_not_trash(const char * psz, sp(::ca2::application) papp);
      virtual void trash_that_is_not_trash(stringa & stra, sp(::ca2::application) papp);

      virtual string title_(const char * path);
      virtual string name_(const char * path);
      virtual string extension(const char * path);

      virtual var length(const char * path);

      virtual void replace(const char * pszContext, const char * pszFind, const char * pszReplace, sp(::ca2::application) papp);

      virtual bool exists(const char * path, sp(::ca2::application) papp);
      virtual bool exists(const string & path, sp(::ca2::application) papp);

      virtual bool exists(const char * path, var * pvarQuery, sp(::ca2::application) papp);
      virtual bool exists(const string & path, var * pvarQuery, sp(::ca2::application) papp);

      void  get_ascendants_path(const char * lpcsz, stringa & stra);
      void  get_ascendants_name(const char * lpcsz, stringa & stra);

      template < class T >
      bool output(sp(::ca2::application) papp, const char * pszOutput, T * p, bool (T::*lpfnOuput)(::ca2::writer &, const char *), const char * lpszSource)
#if defined(LINUX) || defined(MACOS)
         ;
#else
      {
         System.dir().mk(System.dir().name(pszOutput), papp);
         ::ca2::filesp fileOut = App(papp).file().get_file(pszOutput, ::ca2::file::mode_create | ::ca2::file::type_binary | ::ca2::file::mode_write);
         if(fileOut.is_null())
            return false;
         return (p->*lpfnOuput)(fileOut, lpszSource);
      }
#endif

      template < class T >
      bool output(sp(::ca2::application) papp, const char * pszOutput, T * p, bool (T::*lpfnOuput)(::ca2::writer &, ::ca2::reader &), const char * lpszInput)
#if defined(LINUX) || defined(MACOS)
         ;
#else
      {

         App(papp).dir().mk(System.dir().name(pszOutput));

         ::ca2::filesp fileOut = App(papp).file().get_file(pszOutput, ::ca2::file::mode_create | ::ca2::file::type_binary | ::ca2::file::mode_write);

         if(fileOut.is_null())
            return false;

         ::ca2::filesp fileIn = App(papp).file().get_file(lpszInput, ::ca2::file::type_binary | ::ca2::file::mode_read);

         if(fileIn.is_null())
            return false;

         return (p->*lpfnOuput)(fileOut, fileIn);

      }
#endif

      template < class T >
      bool output(sp(::ca2::application) papp, const char * pszOutput, T * p, bool (T::*lpfnOuput)(::ca2::writer &, ::ca2::reader &), ::ca2::reader & istream)
      {
         return (p->*lpfnOuput)(get(pszOutput, papp), istream);
      }

      string time(sp(::ca2::application) papp, const char * pszBasePath, int32_t iDepth, const char * pszPrefix = NULL, const char * pszSuffix = NULL);
      string time_square(sp(::ca2::application) papp, const char * pszPrefix = NULL, const char * pszSuffix = NULL);
      string time_log(sp(::ca2::application) papp, const char * pszId);

      virtual ::ca2::filesp time_square_file(sp(::ca2::application) papp, const char * pszPrefix = NULL, const char * pszSuffix = NULL);
      virtual ::ca2::filesp get(const char * name, sp(::ca2::application) papp);

      template < class T >
      string time_square(sp(::ca2::application) papp, T * p, bool (T::*lpfnOutput)(::ca2::writer &, const char *), const char * lpszSource)
      {
         string strTime = time_square(papp);
         if(strTime.has_char())
            if(!output(strTime, p, lpfnOutput, lpszSource))
               return "";
         return strTime;
      }

      int32_t filterex_time_square(const char * pszPrefix, stringa & stra);
      bool mk_time(const char * lpcszCandidate);

      string as_string(var varFile, sp(::ca2::application) papp);
      string as_string(var varFile, var & varQuery, sp(::ca2::application) papp);
      void as_memory(var varFile, primitive::memory_base & mem, sp(::ca2::application) papp);
      void lines(stringa & stra, var varFile, sp(::ca2::application) papp);

      bool put_contents(var varFile, const void * pvoidContents, ::count count, sp(::ca2::application) papp);
      bool put_contents(var varFile, const char * lpcszContents, sp(::ca2::application) papp);
      bool put_contents(var varFile, ::ca2::file & file, sp(::ca2::application) papp);
      bool put_contents(var varFile, primitive::memory & mem, sp(::ca2::application) papp);
      bool put_contents_utf8(var varFile, const char * lpcszContents, sp(::ca2::application) papp);

      bool is_read_only(const char * psz);

      string sys_temp(const char * pszName, const char * pszExtension, sp(::ca2::application) papp);
      string sys_temp_unique(const char * pszName);


      string replace_extension(const char * pszFile, const char * pszExtension);
      void set_extension(string & str, const char * pszExtension);


      void normalize(string & str);
      int32_t cmp(const char * psz1, const char* psz2);



      string md5(const char * psz);
      string nessie(const char * psz);

      string nessie(sp(::ca2::file) pfile);

//      path & path36();

      void dtf(const char * pszFile, const char * pszDir, sp(::ca2::application) papp);
      void dtf(const char * pszFile, stringa & stra, stringa & straRelative, sp(::ca2::application) papp);
      void ftd(const char * pszDir, const char * pszFile, sp(::ca2::application) papp);

      void is_valid_fileset(const char * pszFile, sp(::ca2::application) papp);

      // 'n' (natural) terminated ascii number, example: 245765487n
      static void write_n_number(sp(::ca2::file) pfile, ::crypto::md5::context * pctx, int64_t iNumber);
      static void read_n_number(sp(::ca2::file) pfile, ::crypto::md5::context * pctx, int64_t & iNumber);

      static void write_gen_string(sp(::ca2::file) pfile, ::crypto::md5::context * pctx, string & str);
      static void read_gen_string(sp(::ca2::file) pfile, ::crypto::md5::context * pctx, string & str);




   protected:

      class file_system::path m_path;

   };


   typedef ::ca::smart_pointer < file_system > file_system_sp;




} // namespace ca2





