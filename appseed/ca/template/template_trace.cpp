#include "StdAfx.h"


/*_template::CTraceCategory traceMultiApp("MultiApp");
_template::CTraceCategory ::radix::trace::category_AppMsg("AppMsg");
_template::CTraceCategory traceWinMsg("WinMsg");
_template::CTraceCategory traceCmdRouting("CmdRouting");
_template::CTraceCategory traceOle("Ole");
_template::CTraceCategory traceDatabase("Database");
_template::CTraceCategory traceInternet("Internet");
_template::CTraceCategory tracedumpContext("dump_context");
_template::CTraceCategory traceMemory("Memory");
_template::CTraceCategory traceGdi("GDI");
_template::CTraceCategory traceUser("User");
_template::CTraceCategory traceKernel("Kernel");
_template::CTraceCategory traceHtml("HTML");
_template::CTraceCategory traceSocket("socket");
*/


//extern CLASS_DECL_ca2 fixed_alloc_array * g_pfixedallocaWstring;


namespace _template
{
   typedef void ( * PFN_trace_v)(const char *pszFileName, int nLine, unsigned int dwCategory, unsigned int nLevel, const char * pszFmt, va_list args);
   CLASS_DECL_ca2 void raw_trace_v(const char *pszFileName, int nLine, unsigned int dwCategory, unsigned int nLevel, const char * pszFmt, va_list args);
   CLASS_DECL_ca2 PFN_trace_v trace_v = &raw_trace_v;

/*   CTraceCategory::CTraceCategory( const char * pszCategoryName, UINT nStartingLevel ) throw() :
      m_dwCategory( 0 )
   {
      m_dwCategory = _template::CTrace::s_trace.RegisterCategory( pszCategoryName );
      _template::CTrace::s_trace.ChangeCategory( m_dwCategory, nStartingLevel, ATLTRACESTATUS_INHERIT);
   }*/

   void CTrace::TraceV(const char *pszFileName, int nLine, DWORD_PTR dwCategory, UINT nLevel, const char * pszFormat, va_list args) const
   {
      UNREFERENCED_PARAMETER(pszFileName);
      UNREFERENCED_PARAMETER(nLine);
/*      const trace_category *pCategory;
      trace_module * pmodule = NULL;
      static const int nCount = 1024;
      CHAR szBuf[nCount] = {'\0'};
      int nLen = 0;*/

      CTraceCategory & category = ((CTrace *) this)->m_map[(unsigned int ) dwCategory];

      //if(ShouldTraceOutput(dwModule, dwCategory, nLevel, &pCategory, &pmodule))
      if(category.m_estatus == trace::status_disabled || nLevel > category.m_uiLevel)
         return;
/*      if (nLen >= 0 && nLen < nCount)
                  {
                        if(g_Allocator.GetProcess()->m_bFileNameAndLineNo)
               {
                  int nTemp;
                  ATL_CRT_ERRORCHECK_SPRINTF(nTemp = _snprintf_s(szBuf + nLen, nCount - nLen, nCount - nLen - 1, "%s(%d) : ", pszFileName, nLine));
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
                  int nTemp;
                  ATL_CRT_ERRORCHECK_SPRINTF(nTemp = _snprintf_s(szBuf + nLen, nCount - nLen, nCount - nLen - 1, "%S: ", pCategory->Name()));
                  if( nTemp < 0 )
                     nLen = nCount;
                  else
                     nLen += nTemp;
               }
                  }*/
      /*if (nLen >= 0 && nLen < nCount)
      {
         ATL_CRT_ERRORCHECK_SPRINTF(_vsnprintf_s(szBuf + nLen, nCount - nLen, nCount - nLen - 1, pszFormat, ptr));
      }*/

      string str;

      str.FormatV(pszFormat, args);

      ::OutputDebugStringW(gen::international::utf8_to_unicode(str));

      /*if(pmodule != NULL)
         pmodule->DebugReport(_CRT_WARN, NULL, 0, NULL, pszFormat, ptr);
      else
         OutputDebugStringA(szBuf);*/
   }


   CTraceCategory::CTraceCategory()
   {
      m_uiLevel      = 3000;
      m_estatus      = trace::status_enabled;
      m_dwCategory   = 0;
   }
   
   CTraceCategory::~CTraceCategory()
   {
   }


   void CTraceCategory::SetLevel( UINT nLevel ) throw()
   {
      m_uiLevel = nLevel;
   }

   trace::e_status CTraceCategory::GetStatus() const throw()
   {
      return m_estatus;
   }

   void CTraceCategory::SetStatus( trace::e_status eStatus ) throw()
   {
      m_estatus = eStatus;
   }


   CTraceCategory::operator DWORD_PTR() const throw()
   {
      return( m_dwCategory );
   }

   UINT CTraceCategory::GetLevel() const throw()
   {
      return m_uiLevel;
   }

   CLASS_DECL_ca2 void raw_trace_v(const char *pszFileName, int nLine, unsigned int dwCategory, unsigned int nLevel, const char * pszFmt, va_list args)
   {
      UNREFERENCED_PARAMETER(pszFileName);
      UNREFERENCED_PARAMETER(nLine);
      UNREFERENCED_PARAMETER(dwCategory);
      UNREFERENCED_PARAMETER(nLevel);
      
      string str;
      str.Format(pszFmt, args);
      ::OutputDebugStringW(gen::international::utf8_to_unicode(str));
   }

   /*CLASS_DECL_ca2 void system_log_trace_v(const char *pszFileName, int nLine, unsigned int dwCategory, unsigned int nLevel, const char * pszFmt, va_list args)
   {
      System.log().trace_v(pszFileName, nLine, dwCategory, nLevel, pszFmt, args);
   }*/

}  // namespace _template
