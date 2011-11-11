#pragma once


namespace ca2
{


   namespace file
   {


      class CLASS_DECL_ca system :
         public ::radix::object
      {
      public:

         class CLASS_DECL_ca path
         {
         public:
            bool is_equal(const char * lpszFilPathA, const char * lpszFilPathB);
            bool eat_end_level(string & str, int iLevelCount, const char * lpSeparator);
            void split(stringa & stra, const char * lpcszPath);
            bool is_relative(const char * psz);
         };

         system();

         path & path();

         void copy(const char * pszNew, const char * psz, bool bFailIfExists, ::ca::application * app);
         void move(const char * pszNew, const char * psz);
         void del(const char * psz);
         string copy(const char * psz, ::ca::application * papp);
         string paste(const char * pszLocation, const char * path, ::ca::application * papp);

         void trash_that_is_not_trash(const char * psz);
         void trash_that_is_not_trash(stringa & stra);

         string title_(const char * path);
         string name_(const char * path);
         string extension(const char * path);

         var length(const char * path);


         void replace(const char * pszContext, const char * pszFind, const char * pszReplace);

         bool exists(const char * path);

         void  get_ascendants_path(const char * lpcsz, stringa & stra);
         void  get_ascendants_name(const char * lpcsz, stringa & stra);

         template < class T >
         bool output(const char * pszOutput, T * p, bool (T::*lpfnOuput)(::ex1::writer &, const char *), const char * lpszSource)
         #ifdef LINUX
         ;
         #else
         {
            System.dir().mk(System.dir().name(pszOutput));
            ex1::filesp fileOut(get_app());
            if(!fileOut->open(pszOutput, ex1::file::mode_create | ex1::file::type_binary | ex1::file::mode_write))
               return false;
            return (p->*lpfnOuput)(fileOut, lpszSource);
         }
         #endif

         template < class T >
         bool output(const char * pszOutput, T * p, bool (T::*lpfnOuput)(::ex1::writer &, ::ex1::reader &), const char * lpszInput)
         #ifdef LINUX
         ;
         #else
         {
            System.dir().mk(System.dir().name(pszOutput));
            ex1::filesp fileOut(get_app());
            if(!fileOut->open(pszOutput, ex1::file::mode_create | ex1::file::type_binary | ex1::file::mode_write))
               return false;
            ex1::filesp fileIn(get_app());
            if(!fileIn->open(lpszInput, ex1::file::type_binary | ex1::file::mode_read))
               return false;
            return (p->*lpfnOuput)(fileOut, fileIn);
         }
         #endif

         template < class T >
         bool output(const char * pszOutput, T * p, bool (T::*lpfnOuput)(::ex1::writer &, ::ex1::reader &), ::ex1::reader & istream)
         {
            return (p->*lpfnOuput)(get(pszOutput), istream);
         }

         string time(const char * pszBasePath, int iDepth, const char * pszPrefix = NULL, const char * pszSuffix = NULL);
         string time_square(const char * pszPrefix = NULL, const char * pszSuffix = NULL);
         string time_log(const char * pszId);

         ex1::filesp time_square_file(const char * pszPrefix = NULL, const char * pszSuffix = NULL);
         ex1::filesp get(const char * name);

         template < class T >
         string time_square(T * p, bool (T::*lpfnOutput)(::ex1::writer &, const char *), const char * lpszSource)
         {
            string strTime = time_square();
            if(strTime.has_char())
               if(!output(strTime, p, lpfnOutput, lpszSource))
                  return "";
            return strTime;
         }

         int filterex_time_square(const char * pszPrefix, stringa & stra);
         bool mk_time(const char * lpcszCandidate);

         string as_string(var varFile, ::ca::application * papp);
         string as_string(var varFile, var varQuery, ::ca::application * papp);
         void as_memory(var varFile, primitive::memory_base & mem, ::ca::application * papp);
         void lines(stringa & stra, var varFile, ::ca::application * papp);

         bool put_contents(var varFile, const void * pvoidContents, count count, ::ca::application * papp);
         bool put_contents(var varFile, const char * lpcszContents, ::ca::application * papp);
         bool put_contents(var varFile, ex1::file & file, ::ca::application * papp);
         bool put_contents(var varFile, primitive::memory & mem, ::ca::application * papp);
         bool put_contents_utf8(var varFile, const char * lpcszContents, ::ca::application * papp);

         bool is_read_only(const char * psz);

         string sys_temp(const char * pszName, const char * pszExtension);
         string sys_temp_unique(const char * pszName);


         string replace_extension(const char * pszFile, const char * pszExtension);
         void set_extension(string & str, const char * pszExtension);


      protected:
         class system::path m_path;
      };


   } // namespace file


} // namespace ca2


