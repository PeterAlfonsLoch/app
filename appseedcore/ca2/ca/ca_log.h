#pragma once

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
}


namespace ca
{

   CLASS_DECL_ca int SimpleDebugReport(int,const char *,int,const char *,const char * pszFormat, va_list list);

/*   CLASS_DECL_ca int __cdecl ca2_votagus_logging_Report(
                                             int iReportType,
                                             const char * pszFileName,
                                             int iLineNumber,
                                             const char * pszModuleName,
                                             const char * pszFormat,
                                             va_list list);


   extern CLASS_DECL_ca int  ( __cdecl *  ________ca2_votagus_logging_Report)(
                                             int iReportType,
                                             const char * pszFileName,
                                             int iLineNumber,
                                             const char * pszModuleName,
                                             const char * pszFormat,
                                             va_list list);*/

   class CLASS_DECL_ca log :
      virtual public object
   {
   public:

      bool              m_bLog;
      bool              m_bExtendedLog;


         /** error level enum. */
      log();
      virtual ~log();

      virtual void success(const char * psz);

      virtual void print(const char * psz, ...);

      virtual bool initialize(const char * pszId);
      virtual bool finalize();

      virtual void set_extended_log(bool bSet = true);
      virtual bool get_extended_log();


      virtual void trace_v(const char *pszFileName, int nLine, unsigned int dwCategory, unsigned int nLevel, const char * pszFmt, va_list args) const;
      virtual void trace_v(const char *pszFileName, int nLine, unsigned int dwCategory, unsigned int nLevel, const wchar_t * pszFmt, va_list args) const;

      virtual void set_trace_category(unsigned int dwCategory, const char * pszName, unsigned int uiLevel);



   };



} // namespace ca
