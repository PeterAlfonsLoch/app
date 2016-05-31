#pragma once


namespace ace
{


   class CLASS_DECL_ACE log :
      virtual public object
   {
   public:

      enum e_level
      {

         level_warning = 0,
         level_error,
         level_fatal,
         level_info

      };

      bool                    m_bLog;
      bool                    m_bExtendedLog;



      bool                    m_bTrace;
      ::ace::trace::trace *  m_ptrace;
      mutex                   m_mutexTrace;
      stringa                 m_straSeparator;
      FILE *                  m_pfile;
      bool                    m_bInitialized;
      string                  m_strLogPath;
      id                      m_id;
      int32_t                 m_iYear;
      int32_t                 m_iMonth;
      int32_t                 m_iDay;


      log(::ace::application * papp);
      virtual ~log();

      virtual void print(const char * psz, ...);

      virtual bool initialize(const char * pszId);
      virtual bool initialize(id id);
      virtual bool finalize();

      void trace_str(const char *pszFileName, int32_t nLine, uint32_t dwCategory, uint32_t nLevel, const char * psz) const;
      void trace_v(const char *pszFileName, int32_t nLine, uint32_t dwCategory, uint32_t nLevel, const char * pszFmt, va_list args) const;

      void set_trace_category(uint32_t dwCategory, const char * pszName, uint32_t uiLevel);


      /** error level enum. */
      //      log();
      //    virtual ~log();

      virtual void success(const char * psz);

      //      virtual void print(const char * psz, ...);

      //      virtual bool initialize(const char * pszId);
      //      virtual bool finalize();

      virtual void set_extended_log(bool bSet = true);
      virtual bool get_extended_log();


      //virtual void trace_v(const char *pszFileName, int32_t nLine, uint32_t dwCategory, uint32_t nLevel, const char * pszFmt, va_list args) const;
      //      virtual void trace_v(const char *pszFileName, int32_t nLine, uint32_t dwCategory, uint32_t nLevel, const unichar * pszFmt, va_list args) const;

      void __cdecl trace(const char * pszFormat, ...);
      void __cdecl trace2(uint32_t dwCategory, UINT nLevel, const char * pszFormat, ...);


      //virtual void set_trace_category(uint32_t dwCategory, const char * pszName, uint32_t uiLevel);



   };


   CLASS_DECL_ACE int32_t SimpleDebugReport(int32_t, const char *, int32_t, const char *, const char * pszFormat, va_list list);


} // namespace ace


inline ::ace::log::e_level ca_get_level_warning() { return ::ace::log::level_warning; }



