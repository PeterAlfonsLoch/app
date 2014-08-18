#include "framework.h"

/*
category traceMultiApp("MultiApp");
category traceAppMsg("AppMsg");
category traceWinMsg("WinMsg");
category traceCmdRouting("CmdRouting");
category traceOle("Ole");
category traceDatabase("Database");
category traceInternet("Internet");
category tracedumpContext("dump_context");
category traceMemory("Memory");
category traceGdi("GDI");
category traceUser("User");
category traceKernel("Kernel");
category traceHtml("HTML");
category traceSocket("socket");
*/


namespace base
{

   namespace trace
   {
      typedef void ( * PFN_trace_v)(const char *pszFileName, int32_t nLine, uint32_t dwCategory, uint32_t nLevel, const char * pszFmt, va_list args);
      CLASS_DECL_AXIS void raw_trace_v(const char *pszFileName, int32_t nLine, uint32_t dwCategory, uint32_t nLevel, const char * pszFmt, va_list args);
      CLASS_DECL_AXIS PFN_trace_v trace_v = &raw_trace_v;

      /*   category::category( const char * pszCategoryName, UINT nStartingLevel ) throw() :
      m_dwCategory( 0 )
      {
      m_dwCategory = ::core::CTrace::s_trace.RegisterCategory( pszCategoryName );
      ::core::CTrace::s_trace.ChangeCategory( m_dwCategory, nStartingLevel, TRACESTATUS_INHERIT);
      }*/

      void trace::TraceV(const char *pszFileName, int32_t nLine, uint_ptr dwCategory, UINT nLevel, const char * pszFormat, va_list args) const
      {
         UNREFERENCED_PARAMETER(pszFileName);
         UNREFERENCED_PARAMETER(nLine);
         /*      const category *pCategory;
         trace_module * pmodule = NULL;
         static const int32_t nCount = 1024;
         CHAR szBuf[nCount] = {'\0'};
         int32_t nLen = 0;*/

         category & category = ((trace *) this)->m_map[(uint32_t ) dwCategory];

         //if(ShouldTraceOutput(dwModule, dwCategory, nLevel, &pCategory, &pmodule))
         if(category.m_estatus == ::base::trace::status_disabled || nLevel > category.m_uiLevel)
            return;
         /*      if (nLen >= 0 && nLen < nCount)
         {
         if(g_Allocator.GetProcess()->m_bFileNameAndLineNo)
         {
         int32_t nTemp;
         C_RUNTIME_ERRORCHECK_SPRINTF(nTemp = _snprintf_s(szBuf + nLen, nCount - nLen, nCount - nLen - 1, "%s(%d) : ", pszFileName, nLine));
         if( nTemp < 0 )
         nLen = nCount;
         else
         nLen += nTemp;
         }
         }
         if (nLen >= 0 && nLen < nCount)
         {
         if(pCategory && g_Allocator.GetProcess()->m_bFuncAndCategoryNames)
         {
         int32_t nTemp;
         C_RUNTIME_ERRORCHECK_SPRINTF(nTemp = _snprintf_s(szBuf + nLen, nCount - nLen, nCount - nLen - 1, "%S: ", pCategory->Name()));
         if( nTemp < 0 )
         nLen = nCount;
         else
         nLen += nTemp;
         }
         }*/
         /*if (nLen >= 0 && nLen < nCount)
         {
         C_RUNTIME_ERRORCHECK_SPRINTF(_vsnprintf_s(szBuf + nLen, nCount - nLen, nCount - nLen - 1, pszFormat, ptr));
         }*/

         string str;

         str.FormatV(pszFormat, args);

         ::OutputDebugStringW(::str::international::utf8_to_unicode(str));

         /*if(pmodule != NULL)
         pmodule->DebugReport(_CRT_WARN, NULL, 0, NULL, pszFormat, ptr);
         else
         OutputDebugStringA(szBuf);*/
      }


      category::category()
      {
         m_uiLevel      = 3000;
         m_estatus      = status_enabled;
         m_dwCategory   = 0;
      }

      category::~category()
      {
      }


      void category::SetLevel( UINT nLevel ) throw()
      {
         m_uiLevel = nLevel;
      }

      e_status category::GetStatus() const throw()
      {
         return m_estatus;
      }

      void category::SetStatus( e_status eStatus ) throw()
      {
         m_estatus = eStatus;
      }


      category::operator uint32_t() const throw()
      {
         return( m_dwCategory );
      }

      UINT category::GetLevel() const throw()
      {
         return m_uiLevel;
      }

      CLASS_DECL_AXIS void raw_trace_v(const char *pszFileName, int32_t nLine, uint32_t dwCategory, uint32_t nLevel, const char * pszFmt, va_list args)
      {
         UNREFERENCED_PARAMETER(pszFileName);
         UNREFERENCED_PARAMETER(nLine);
         UNREFERENCED_PARAMETER(dwCategory);
         UNREFERENCED_PARAMETER(nLevel);

         string str;
         str.FormatV(pszFmt, args);
         ::OutputDebugStringW(::str::international::utf8_to_unicode(str));
      }

      /*CLASS_DECL_AXIS void system_log_trace_v(const char *pszFileName, int32_t nLine, uint32_t dwCategory, uint32_t nLevel, const char * pszFmt, va_list args)
      {
      System.log().trace_v(pszFileName, nLine, dwCategory, nLevel, pszFmt, args);
      }*/


   } // namespace trace

}  // namespace core
