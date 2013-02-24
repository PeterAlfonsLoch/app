#pragma once


#if defined(WINDOWS)

CLASS_DECL_ca bool IsWow64();

#endif


namespace ca
{


   namespace file
   {


      class CLASS_DECL_ca system :
         public ::ca::object
      {
      public:

         class CLASS_DECL_ca path
         {
         public:
            bool is_equal(const char * lpszFilPathA, const char * lpszFilPathB);
            bool eat_end_level(string & str, int32_t iLevelCount, const char * lpSeparator);
            void split(stringa & stra, const char * lpcszPath);
            bool is_relative(const char * psz);
         };

         system();

         path & path();

         virtual void copy(const char * pszNew, const char * psz, bool bFailIfExists, e_extract eextract, ::ca::application * app);
         virtual void move(const char * pszNew, const char * psz);
         virtual void del(const char * psz);
         virtual string copy(const char * psz, ::ca::application * papp);
         virtual string paste(const char * pszLocation, const char * path, ::ca::application * papp);

         virtual void trash_that_is_not_trash(const char * psz, ::ca::application * papp);
         virtual void trash_that_is_not_trash(stringa & stra, ::ca::application * papp);

         virtual string title_(const char * path);
         virtual string name_(const char * path);
         virtual string extension(const char * path);

         virtual var length(const char * path);

         virtual void replace(const char * pszContext, const char * pszFind, const char * pszReplace, ::ca::application * papp);

         virtual bool exists(const char * path, ::ca::application * papp);
         virtual bool exists(const string & path, ::ca::application * papp);

         virtual bool exists(const char * path, var * pvarQuery, ::ca::application * papp);
         virtual bool exists(const string & path, var * pvarQuery, ::ca::application * papp);

         void  get_ascendants_path(const char * lpcsz, stringa & stra);
         void  get_ascendants_name(const char * lpcsz, stringa & stra);

         template < class T >
         bool output(::ca::application * papp, const char * pszOutput, T * p, bool (T::*lpfnOuput)(::ca::writer &, const char *), const char * lpszSource)
         #if defined(LINUX) || defined(MACOS)
         ;
         #else
         {
            System.dir().mk(System.dir().name(pszOutput), papp);
            ca::filesp fileOut = App(papp).file().get_file(pszOutput, ca::file::mode_create | ca::file::type_binary | ca::file::mode_write);
            if(fileOut.is_null())
               return false;
            return (p->*lpfnOuput)(fileOut, lpszSource);
         }
         #endif

         template < class T >
         bool output(::ca::application * papp, const char * pszOutput, T * p, bool (T::*lpfnOuput)(::ca::writer &, ::ca::reader &), const char * lpszInput)
         #if defined(LINUX) || defined(MACOS)
         ;
         #else
         {

            App(papp).dir().mk(System.dir().name(pszOutput));

            ca::filesp fileOut = App(papp).file().get_file(pszOutput, ca::file::mode_create | ca::file::type_binary | ca::file::mode_write);

            if(fileOut.is_null())
                return false;

            ca::filesp fileIn = App(papp).file().get_file(lpszInput, ca::file::type_binary | ca::file::mode_read);

            if(fileIn.is_null())
               return false;

            return (p->*lpfnOuput)(fileOut, fileIn);

         }
         #endif

         template < class T >
         bool output(::ca::application * papp, const char * pszOutput, T * p, bool (T::*lpfnOuput)(::ca::writer &, ::ca::reader &), ::ca::reader & istream)
         {
            return (p->*lpfnOuput)(get(pszOutput, papp), istream);
         }

         string time(::ca::application * papp, const char * pszBasePath, int32_t iDepth, const char * pszPrefix = NULL, const char * pszSuffix = NULL);
         string time_square(::ca::application * papp, const char * pszPrefix = NULL, const char * pszSuffix = NULL);
         string time_log(::ca::application * papp, const char * pszId);

         virtual ca::filesp time_square_file(::ca::application * papp, const char * pszPrefix = NULL, const char * pszSuffix = NULL);
         virtual ca::filesp get(const char * name, ::ca::application * papp);

         template < class T >
         string time_square(::ca::application * papp, T * p, bool (T::*lpfnOutput)(::ca::writer &, const char *), const char * lpszSource)
         {
            string strTime = time_square(papp);
            if(strTime.has_char())
               if(!output(strTime, p, lpfnOutput, lpszSource))
                  return "";
            return strTime;
         }

         int32_t filterex_time_square(const char * pszPrefix, stringa & stra);
         bool mk_time(const char * lpcszCandidate);

         string as_string(var varFile, ::ca::application * papp);
         string as_string(var varFile, var & varQuery, ::ca::application * papp);
         void as_memory(var varFile, primitive::memory_base & mem, ::ca::application * papp);
         void lines(stringa & stra, var varFile, ::ca::application * papp);

         bool put_contents(var varFile, const void * pvoidContents, count count, ::ca::application * papp);
         bool put_contents(var varFile, const char * lpcszContents, ::ca::application * papp);
         bool put_contents(var varFile, ca::file & file, ::ca::application * papp);
         bool put_contents(var varFile, primitive::memory & mem, ::ca::application * papp);
         bool put_contents_utf8(var varFile, const char * lpcszContents, ::ca::application * papp);

         bool is_read_only(const char * psz);

         string sys_temp(const char * pszName, const char * pszExtension, ::ca::application * papp);
         string sys_temp_unique(const char * pszName);


         string replace_extension(const char * pszFile, const char * pszExtension);
         void set_extension(string & str, const char * pszExtension);


      void normalize(string & str);
      int32_t cmp(const char * psz1, const char* psz2);

      protected:
         class system::path m_path;
      };


      typedef smart_pointer < system > system_sp;


   } // namespace file


} // namespace ca






typedef struct MD5state_st MD5_CTX;


namespace ca
{


   class CLASS_DECL_ca file :
      public ::ca::object
   {
   public:

      class CLASS_DECL_ca path :
         public ::ca::object
      {
      public:
         bool rename(const char * pszNew, const char * psz, ::ca::application * papp);
         file * m_pfile;
      };


      path m_path;

      file();


      string md5(const char * psz);
      string nessie(const char * psz);

      string nessie(ca::file * pfile);

      path & path36();
   
      void dtf(const char * pszFile, const char * pszDir, ::ca::application * papp);
      void dtf(const char * pszFile, stringa & stra, stringa & straRelative, ::ca::application * papp);
      void ftd(const char * pszDir, const char * pszFile, ::ca::application * papp);

      void is_valid_fileset(const char * pszFile, ::ca::application * papp);

      // 'n' (natural) terminated ascii number, example: 245765487n
      static void write_n_number(ca::file * pfile, ::crypto::md5::context * pctx, int64_t iNumber);
      static void read_n_number(ca::file * pfile, ::crypto::md5::context * pctx, int64_t & iNumber);

      static void write_gen_string(ca::file * pfile, ::crypto::md5::context * pctx, string & str);
      static void read_gen_string(ca::file * pfile, ::crypto::md5::context * pctx, string & str);


   };


} // namespace ca




#pragma once






