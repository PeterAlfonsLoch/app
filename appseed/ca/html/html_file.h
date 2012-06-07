#pragma once


namespace html
{


   class CLASS_DECL_ca file :
      virtual public ::radix::object
#if defined(LINUX) || defined(MACOS)
      , public string_format_printer
#endif
   {
   public:

      string                     m_strOptions;
      string                     m_strStyle;
      ::user::str_context *      m_puistrcontext;


      file();


      virtual ::user::str_context *  str_context();

      virtual void print(const char * lpcsz);


#ifdef WINDOWS

      virtual void printf(const char * lpcsz, ...);

      virtual void printstr(const char * lpcsz, ...);

#else

      void trace(void *, const char * psz);


      inline void printf(const char *pszFmt) const
      {

         string_format format(this, &html_file::trace, NULL);

         format.printf(pszFmt);

      }

      template<typename T, typename... Args>
      inline void printf(const char * pszFmt, const T & value, Args... args) const
      {

         string_format format(this, &html_file::trace, NULL);

         format.printf(pszFmt, value, args...);

      }

#endif



      virtual void dprint(const char * lpcsz);

   };


} // namespace html



