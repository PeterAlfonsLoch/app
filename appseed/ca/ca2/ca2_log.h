#pragma once


namespace ca2
{

   class CLASS_DECL_ca log :
      virtual public ca::log,
      virtual public ::radix::object
   {
   public:


      _template::CTrace m_trace;

      critical_section m_csTrace;

      inline static string level_name(gen::log::level::e_level elevel)
      {
         switch(elevel)
         {
         case ::gen::log::level::warning:
            return "warning";
         case ::gen::log::level::error:
            return "error";
         case ::gen::log::level::fatal:
            return "fatal";
         case ::gen::log::level::info:
            return "info";
         default:
            return "undefined log error";
         }
      }

      stringa m_straSeparator;

      ex1::text_file_sp m_spfile;

      mutex m_mutex;

      bool m_bInitialized;

      string m_strLogPath;
      id m_id;

      int m_iYear;
      int m_iMonth;
      int m_iDay;

      log(::ca::application * papp);
      virtual ~log();

      virtual void print(const char * psz, ...);

      virtual bool initialize(const char * pszId);
      virtual bool initialize(id id);
      virtual bool finalize();

      void trace_v(const char *pszFileName, int nLine, DWORD_PTR dwCategory, unsigned int nLevel, const char * pszFmt, va_list args) const;

      void __cdecl trace(const char * pszFormat, ...);
      void __cdecl trace2(DWORD_PTR dwCategory, UINT nLevel, const char * pszFormat, ...);

      void set_trace_category(DWORD_PTR dwCategory, const char * pszName, unsigned int uiLevel);

   };

} // namespace ca2