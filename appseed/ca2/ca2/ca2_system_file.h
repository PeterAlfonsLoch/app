#pragma once

namespace ca2
{

   class CLASS_DECL_ca system_file :
      public ::radix::object
   {
   public:
      system_file();
      class CLASS_DECL_ca path
      {
      public:
         bool is_equal(const char * lpszFilPathA, const char * lpszFilPathB);
         bool eat_end_level(string & str, int iLevelCount, const char * lpSeparator);
         void split(stringa & stra, const char * lpcszPath);
         bool is_relative(const char * psz);
      };

      path & path();

      void copy(const char * pszNew, const char * psz, bool bFailIfExists = false);
      void move(const char * pszNew, const char * psz);
      void del(const char * psz);
      string copy(const char * psz);
      string paste(const char * pszLocation, const char * path);

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
      bool output(const char * pszOutput, T * p, bool (T::*lpfnOuput)(::ex1::output_stream &, const char *), const char * lpszSource)
      {
         System.dir().mk(System.dir().name(pszOutput));
         ex1::filesp fileOut(get_app());
         if(!fileOut->open(pszOutput, ex1::file::mode_create | ex1::file::type_binary | ex1::file::mode_write))
            return false;
         return (p->*lpfnOuput)(fileOut, lpszSource);
      }

      template < class T >
      bool output(const char * pszOutput, T * p, bool (T::*lpfnOuput)(::ex1::output_stream &, ::ex1::input_stream &), const char * lpszSource)
      {
         System.dir().mk(System.dir().name(pszOutput));
         ex1::filesp fileOut(get_app());
         if(!fileOut->open(pszOutput, ex1::file::mode_create | ex1::file::type_binary | ex1::file::mode_write))
            return false;
         ex1::filesp fileIn(get_app());
         if(!fileIn->open(pszOutput, ex1::file::type_binary | ex1::file::mode_read))
            return false;
         return (p->*lpfnOuput)(fileOut, fileIn);
      }

      template < class T >
      bool output(const char * pszOutput, T * p, bool (T::*lpfnOuput)(::ex1::output_stream &, ::ex1::input_stream &), ::ex1::input_stream & istream)
      {
         return (p->*lpfnOuput)(get(pszOutput), istream);
      }

      string time(const char * pszBasePath, int iDepth, const char * pszPrefix = NULL, const char * pszSuffix = NULL);
      string time_square(const char * pszPrefix = NULL, const char * pszSuffix = NULL);
      string time_log(const char * pszId);

      ex1::filesp time_square_file(const char * pszPrefix = NULL, const char * pszSuffix = NULL);
      ex1::filesp get(const char * name);
      
      template < class T >
      string time_square(T * p, bool (T::*lpfnOuput)(::ex1::output_stream &, const char *), const char * lpszSource)
      {
         string strTime = time_square();
         if(strTime.has_char())
            if(!output(strTime, p, lpfnOutput, lpszSource))
               return "";
         return strTime;
      }

      int filterex_time_square(stringa & stra);
      bool mk_time(const char * lpcszCandidate);

      string as_string(var varFile, ::ca::application * papp);
      void as_memory(var varFile, primitive::memory & mem, ::ca::application * papp);
      void lines(stringa & stra, var varFile, ::ca::application * papp);

      bool put_contents(const char * lpcszFileName, const char * lpcszContents);
      bool put_contents_utf8(const char * lpcszFileName, const char * lpcszContents);
      bool put_contents(const char * lpcszFileName, ex1::file & file);
      bool put_contents(const char * lpcszFileName, primitive::memory & mem);

      bool is_read_only(const char * psz);

      string sys_temp(const char * pszName, const char * pszExtension);
      string sys_temp_unique(const char * pszName);
      

   protected:
      class system_file::path m_path;
   };

} // namespace ca2

