#pragma once


#if defined(WINDOWS)

CLASS_DECL_ca bool IsWow64();

#endif



typedef struct MD5state_st MD5_CTX;




namespace ca
{


   class CLASS_DECL_ca file_system :
      public ::ca::object
   {
   public:

      class CLASS_DECL_ca path :
         virtual public ::ca::object
      {
      public:
         
         file_system * m_pfile;


         bool is_equal(const char * lpszFilPathA, const char * lpszFilPathB);
         bool eat_end_level(string & str, int32_t iLevelCount, const char * lpSeparator);
         void split(stringa & stra, const char * lpcszPath);
         bool is_relative(const char * psz);

         bool rename(const char * pszNew, const char * psz, ::ca::applicationsp papp);

      };

      file_system();

      path & path();

      virtual void copy(const char * pszNew, const char * psz, bool bFailIfExists, e_extract eextract, ::ca::applicationsp app);
      virtual void move(const char * pszNew, const char * psz);
      virtual void del(const char * psz);
      virtual string copy(const char * psz, ::ca::applicationsp papp);
      virtual string paste(const char * pszLocation, const char * path, ::ca::applicationsp papp);

      virtual void trash_that_is_not_trash(const char * psz, ::ca::applicationsp papp);
      virtual void trash_that_is_not_trash(stringa & stra, ::ca::applicationsp papp);

      virtual string title_(const char * path);
      virtual string name_(const char * path);
      virtual string extension(const char * path);

      virtual var length(const char * path);

      virtual void replace(const char * pszContext, const char * pszFind, const char * pszReplace, ::ca::applicationsp papp);

      virtual bool exists(const char * path, ::ca::applicationsp papp);
      virtual bool exists(const string & path, ::ca::applicationsp papp);

      virtual bool exists(const char * path, var * pvarQuery, ::ca::applicationsp papp);
      virtual bool exists(const string & path, var * pvarQuery, ::ca::applicationsp papp);

      void  get_ascendants_path(const char * lpcsz, stringa & stra);
      void  get_ascendants_name(const char * lpcsz, stringa & stra);

      template < class T >
      bool output(::ca::applicationsp papp, const char * pszOutput, T * p, bool (T::*lpfnOuput)(::ca::writer &, const char *), const char * lpszSource)
#if defined(LINUX) || defined(MACOS)
         ;
#else
      {
         System.dir().mk(System.dir().name(pszOutput), papp);
         ::ca::filesp fileOut = App(papp).file().get_file(pszOutput, ::ca::file::mode_create | ::ca::file::type_binary | ::ca::file::mode_write);
         if(fileOut.is_null())
            return false;
         return (p->*lpfnOuput)(fileOut, lpszSource);
      }
#endif

      template < class T >
      bool output(::ca::applicationsp papp, const char * pszOutput, T * p, bool (T::*lpfnOuput)(::ca::writer &, ::ca::reader &), const char * lpszInput)
#if defined(LINUX) || defined(MACOS)
         ;
#else
      {

         App(papp).dir().mk(System.dir().name(pszOutput));

         ::ca::filesp fileOut = App(papp).file().get_file(pszOutput, ::ca::file::mode_create | ::ca::file::type_binary | ::ca::file::mode_write);

         if(fileOut.is_null())
            return false;

         ::ca::filesp fileIn = App(papp).file().get_file(lpszInput, ::ca::file::type_binary | ::ca::file::mode_read);

         if(fileIn.is_null())
            return false;

         return (p->*lpfnOuput)(fileOut, fileIn);

      }
#endif

      template < class T >
      bool output(::ca::applicationsp papp, const char * pszOutput, T * p, bool (T::*lpfnOuput)(::ca::writer &, ::ca::reader &), ::ca::reader & istream)
      {
         return (p->*lpfnOuput)(get(pszOutput, papp), istream);
      }

      string time(::ca::applicationsp papp, const char * pszBasePath, int32_t iDepth, const char * pszPrefix = ::null(), const char * pszSuffix = ::null());
      string time_square(::ca::applicationsp papp, const char * pszPrefix = ::null(), const char * pszSuffix = ::null());
      string time_log(::ca::applicationsp papp, const char * pszId);

      virtual ::ca::filesp time_square_file(::ca::applicationsp papp, const char * pszPrefix = ::null(), const char * pszSuffix = ::null());
      virtual ::ca::filesp get(const char * name, ::ca::applicationsp papp);

      template < class T >
      string time_square(::ca::applicationsp papp, T * p, bool (T::*lpfnOutput)(::ca::writer &, const char *), const char * lpszSource)
      {
         string strTime = time_square(papp);
         if(strTime.has_char())
            if(!output(strTime, p, lpfnOutput, lpszSource))
               return "";
         return strTime;
      }

      int32_t filterex_time_square(const char * pszPrefix, stringa & stra);
      bool mk_time(const char * lpcszCandidate);

      string as_string(var varFile, ::ca::applicationsp papp);
      string as_string(var varFile, var & varQuery, ::ca::applicationsp papp);
      void as_memory(var varFile, primitive::memory_base & mem, ::ca::applicationsp papp);
      void lines(stringa & stra, var varFile, ::ca::applicationsp papp);

      bool put_contents(var varFile, const void * pvoidContents, ::count count, ::ca::applicationsp papp);
      bool put_contents(var varFile, const char * lpcszContents, ::ca::applicationsp papp);
      bool put_contents(var varFile, ::ca::file & file, ::ca::applicationsp papp);
      bool put_contents(var varFile, primitive::memory & mem, ::ca::applicationsp papp);
      bool put_contents_utf8(var varFile, const char * lpcszContents, ::ca::applicationsp papp);

      bool is_read_only(const char * psz);

      string sys_temp(const char * pszName, const char * pszExtension, ::ca::applicationsp papp);
      string sys_temp_unique(const char * pszName);


      string replace_extension(const char * pszFile, const char * pszExtension);
      void set_extension(string & str, const char * pszExtension);


      void normalize(string & str);
      int32_t cmp(const char * psz1, const char* psz2);



      string md5(const char * psz);
      string nessie(const char * psz);

      string nessie(::ca::file * pfile);

//      path & path36();

      void dtf(const char * pszFile, const char * pszDir, ::ca::applicationsp papp);
      void dtf(const char * pszFile, stringa & stra, stringa & straRelative, ::ca::applicationsp papp);
      void ftd(const char * pszDir, const char * pszFile, ::ca::applicationsp papp);

      void is_valid_fileset(const char * pszFile, ::ca::applicationsp papp);

      // 'n' (natural) terminated ascii number, example: 245765487n
      static void write_n_number(::ca::file * pfile, ::crypto::md5::context * pctx, int64_t iNumber);
      static void read_n_number(::ca::file * pfile, ::crypto::md5::context * pctx, int64_t & iNumber);

      static void write_gen_string(::ca::file * pfile, ::crypto::md5::context * pctx, string & str);
      static void read_gen_string(::ca::file * pfile, ::crypto::md5::context * pctx, string & str);




   protected:

      class file_system::path m_path;

   };


   typedef smart_pointer < file_system > file_system_sp;




} // namespace ca





