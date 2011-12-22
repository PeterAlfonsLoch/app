#pragma once


namespace ca
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

         virtual void copy(const char * pszNew, const char * psz, bool bFailIfExists, ::ca::application * app);
         virtual void move(const char * pszNew, const char * psz);
         virtual void del(const char * psz);
         virtual string copy(const char * psz, ::ca::application * papp);
         virtual string paste(const char * pszLocation, const char * path, ::ca::application * papp);

         virtual void trash_that_is_not_trash(const char * psz);
         virtual void trash_that_is_not_trash(stringa & stra);

         virtual string title_(const char * path);
         virtual string name_(const char * path);
         virtual string extension(const char * path);

         virtual var length(const char * path);

         virtual void replace(const char * pszContext, const char * pszFind, const char * pszReplace, ::ca::application * papp);

         virtual bool exists(const char * path, ::ca::application * papp);

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

         string time(::ca::application * papp, const char * pszBasePath, int iDepth, const char * pszPrefix = NULL, const char * pszSuffix = NULL);
         string time_square(::ca::application * papp, const char * pszPrefix = NULL, const char * pszSuffix = NULL);
         string time_log(::ca::application * papp, const char * pszId);

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

         string sys_temp(const char * pszName, const char * pszExtension, ::ca::application * papp);
         string sys_temp_unique(const char * pszName);


         string replace_extension(const char * pszFile, const char * pszExtension);
         void set_extension(string & str, const char * pszExtension);


      protected:
         class system::path m_path;
      };


   } // namespace file


} // namespace ca


