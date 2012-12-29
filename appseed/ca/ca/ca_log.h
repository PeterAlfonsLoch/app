#pragma once

class critical_section;
class mutex;
class stringa;
class string;
class id;

namespace gen
{
   namespace log
   {
      namespace level
      {
         enum e_level
         {
            warning = 0,
            error,
            fatal,
            info
         };
      }
   }
   namespace trace
   {
      class trace;
   }
}

namespace ex1
{
   class file;
}


namespace ca
{


   CLASS_DECL_ca int32_t SimpleDebugReport(int32_t,const char *,int32_t,const char *,const char * pszFormat, va_list list);

/*   CLASS_DECL_ca int32_t __cdecl ca2_votagus_logging_Report(
                                             int32_t iReportType,
                                             const char * pszFileName,
                                             int32_t iLineNumber,
                                             const char * pszModuleName,
                                             const char * pszFormat,
                                             va_list list);


   extern CLASS_DECL_ca int32_t  ( __cdecl *  ________ca2_votagus_logging_Report)(
                                             int32_t iReportType,
                                             const char * pszFileName,
                                             int32_t iLineNumber,
                                             const char * pszModuleName,
                                             const char * pszFormat,
                                             va_list list);*/

   class CLASS_DECL_ca log :
      virtual public ::ca::ca
   {
   public:

      bool              m_bLog;
      bool              m_bExtendedLog;



      bool                    m_bTrace;
      gen::trace::trace *     m_ptrace;
      critical_section *      m_pcsTrace;
      stringa *               m_pstraSeparator;
      FILE *                  m_pfile;
      mutex *                 m_pmutex;
      bool                    m_bInitialized;
      string *                m_pstrLogPath;
      id *                    m_pid;
      int32_t                     m_iYear;
      int32_t                     m_iMonth;
      int32_t                     m_iDay;


      log(::ca::application * papp);
      virtual ~log();

      virtual void print(const char * psz, ...);

      virtual bool initialize(const char * pszId);
      virtual bool initialize(id id);
      virtual bool finalize();

      void trace_v(const char *pszFileName, int32_t nLine, DWORD dwCategory, uint32_t nLevel, const char * pszFmt, va_list args) const;

      void set_trace_category(DWORD dwCategory, const char * pszName, uint32_t uiLevel);


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
//      virtual void trace_v(const char *pszFileName, int32_t nLine, uint32_t dwCategory, uint32_t nLevel, const wchar_t * pszFmt, va_list args) const;

      void __cdecl trace(const char * pszFormat, ...);
      void __cdecl trace2(DWORD dwCategory, UINT nLevel, const char * pszFormat, ...);


      //virtual void set_trace_category(uint32_t dwCategory, const char * pszName, uint32_t uiLevel);


   
   };

   


} // namespace ca

