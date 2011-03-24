#include "StdAfx.h"

#include <stdio.h>
#ifdef WIN32
#include <windows.h>
#endif

namespace ca
{

//   extern ::ca::application * g_papp;

   CLASS_DECL_ca int SimpleDebugReport(int,const char *,int,const char *,const char * pszFormat, va_list list)
   {
      #ifdef WIN32
      char buf[2048];
      vsnprintf_s(buf, sizeof(buf), sizeof(buf), pszFormat, list);
      OutputDebugString(buf);
      #else
      vprintf(pszFormat, list);
      #endif
      return 0;
   }

   /*int ca2_votagus_logging_Report(
                                 int iReportType,
                                 const char * pszFileName,
                                 int iLineNumber,
                                 const char * pszModuleName,
                                 const char * pszFormat,
                                 va_list list)
   {
      return System.________ca2_votagus_logging_Report(iReportType, pszFileName, iLineNumber, pszModuleName, pszFormat, list);
   }*/

   void log::set_extended_log(bool bSet)
   {
      m_bExtendedLog = bSet;
   }

   bool log::get_extended_log()
   {
      return m_bExtendedLog;
   }

   log::log()
   {
      m_bLog = true;
   }

   log::~log()
   {
   }

   void log::success(const char * psz)
   {
      print(psz);
   }

   void log::print(const char * psz, ...)
   {
      UNREFERENCED_PARAMETER(psz);
   }

   bool log::initialize(const char * pszId)
   {
      UNREFERENCED_PARAMETER(pszId);
      return true;
   }

   bool log::finalize()
   {
      return true;
   }


   void log::trace_v(const char *pszFileName, int nLine, unsigned int dwCategory, unsigned int nLevel, const char * pszFmt, va_list args) const
   {
   }

   void log::trace_v(const char *pszFileName, int nLine, unsigned int dwCategory, unsigned int nLevel, const wchar_t * pszFmt, va_list args) const
   {
   }

   void log::set_trace_category(unsigned int dwCategory, const char * pszName, unsigned int uiLevel)
   {
   }


} // namespace ca
