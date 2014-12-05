#pragma once


namespace html
{


   class CLASS_DECL_CORE file :
      virtual public ::object
#if defined(LINUX) || defined(APPLEOS)
      , public string_format_printer
#endif
   {
   public:


      string                     m_strOptions;
      string                     m_strStyle;
      sp(::user::str_context)    m_puistrcontext;


      file();


      virtual ::user::str_context *  str_context();

      virtual void print(const string & str);

      virtual void raw_print(const string & str);


#ifdef WINDOWS

      virtual void printf(const string & str, ...);

      virtual void printstr(const string & str, ...);

#else

      void trace(void *, const char * psz);


      inline void printf(const char *pszFmt) const
      {

         string_format format(this, &::html::file::trace, NULL);

         format.printf(pszFmt);

      }

      template<typename T, typename... Args>
      inline void printf(const char * pszFmt, const T & value, Args... args) const
      {

         string_format format(this, &::html::file::trace, NULL);

         format.printf(pszFmt, value, args...);

      }

#endif



      virtual void dprint(const char * lpcsz);

   };


} // namespace html



