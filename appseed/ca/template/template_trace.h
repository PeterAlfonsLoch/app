#pragma once


#include "ca/template/template_definition.h"
#include "ca/template/template_debug.h"
#include "ca/ca_log.h"

#ifdef WINDOWS

extern "C" IMAGE_DOS_HEADER __ImageBase;

#endif


namespace _template
{

   //typedef void ( * PFN_trace_v)(const char *pszFileName, int nLine, unsigned int dwCategory, unsigned int nLevel, const char * pszFmt, va_list args);

   CLASS_DECL_ca void raw_trace_v(const char *pszFileName, int nLine, unsigned int dwCategory, unsigned int nLevel, const char * pszFmt, va_list args);
   //CLASS_DECL_ca void system_log_trace_v(const char *pszFileName, int nLine, unsigned int dwCategory, unsigned int nLevel, const char * pszFmt, va_list args);

   //extern CLASS_DECL_ca PFN_trace_v trace_v;

   namespace trace
   {
      enum e_status
      {
         status_enabled,
         status_disabled
      };

      enum e_category
      {
         category_General,
         category_COM,
         category_QI,
         category_Registrar,
         category_Refcount,
         category_Windowing,
         category_Controls,
         category_Hosting,
         category_DBClient,
         category_DBProvider,
         category_Snapin,
         category_NotImpl,
         category_Allocation,
         category_Exception,
         category_Time,
         category_Cache,
         category_Stencil,
         category_String,
         category_Map,
         category_Util,
         category_Security,
         category_Sync,
         category_ISAPI,

         category_User,
         category_User2,
         category_User3,
         category_User4,
      };
   }

   class CTrace;

   // Declare a global instance of this class to automatically register a custom trace category at startup
   class CLASS_DECL_ca CTraceCategory
   {
   public:

      CTraceCategory();
      ~CTraceCategory();

      UINT GetLevel() const throw();
      void SetLevel( UINT nLevel ) throw();
      trace::e_status GetStatus() const throw();
      void SetStatus(trace::e_status eStatus) throw();

      operator DWORD() const throw();

      unsigned int      m_dwCategory;
      string            m_strCategory;
      UINT              m_uiLevel;
      trace::e_status   m_estatus;
   };


   class CLASS_DECL_ca CTrace
   {
   public:

      ::ca::application * m_papp;

      CTrace(::ca::application * papp)
      {
         m_papp = papp;
      }

      ~CTrace()
      {
      }

      CTraceCategory & operator[](DWORD_PTR dwCategory)
      {
         return m_map[dwCategory];
      }

      void TraceV(const char *pszFileName, int nLine, DWORD_PTR dwCategory, UINT nLevel, const char * pszFmt, va_list args) const;


      /*bool LoadSettings(const char * pszFileName = NULL) const
         { return 0 != AtlTraceLoadSettings(pszFileName);}
      void SaveSettings(const char * pszFileName = NULL) const
         { AtlTraceSaveSettings(pszFileName);}*/

      collection::map < DWORD_PTR, DWORD_PTR, CTraceCategory, CTraceCategory > m_map;
   };



   #ifndef _ATL_NO_DEBUG_CRT
   class CNoUIAssertHook
   {
   public:
      CNoUIAssertHook()
      {
         ATLASSERT( s_pfnPrevHook == NULL );
   #ifdef VC6
         //s_pfnPrevHook = _CrtGetReportHook();
         _CrtSetReportHook(CrtHookProc);
   #else
         s_pfnPrevHook = _CrtSetReportHook(CrtHookProc);
   #endif
      }
      ~CNoUIAssertHook()
      {
         _CrtSetReportHook(s_pfnPrevHook);
         s_pfnPrevHook = NULL;
      }

   private:
      static int __cdecl CrtHookProc(int eReportType, char* pszMessage, int* pnRetVal)
      {

         if (eReportType == _CRT_ASSERT)
         {
            ::OutputDebugStringA( "ASSERTION FAILED\n" );
            ::OutputDebugStringA( pszMessage );
            //If caller doesn't want retVal, so be it.
            if (pnRetVal != NULL)
            {
               *pnRetVal = 1;
            }
            return TRUE;
         }

         if (s_pfnPrevHook != NULL)
         {
            return s_pfnPrevHook(eReportType, pszMessage, pnRetVal);
         }
         else
         {
            return FALSE;
         }
      }

   private:
      static _CRT_REPORT_HOOK s_pfnPrevHook;
   };

   #ifdef WINDOWS

   __declspec( selectany ) _CRT_REPORT_HOOK CNoUIAssertHook::s_pfnPrevHook = NULL;

   #endif

   #define DECLARE_NOUIASSERT() _template::CNoUIAssertHook _g_NoUIAssertHook;

   #endif  // _ATL_NO_DEBUG_CRT

   #ifndef ATLTRACE
   #define ATLTRACE ::_template::CTraceFileAndLineInfo(m_papp, __FILE__, __LINE__)
   #define APPTRACE(papp) ::_template::CTraceFileAndLineInfo(papp, __FILE__, __LINE__)
   #define ATLTRACE2 ATLTRACE
   #endif

   CLASS_DECL_ca void __cdecl AtlTrace(const char * pszFormat, ...);
   CLASS_DECL_ca void __cdecl AtlTrace(const wchar_t * pszFormat, ...);
   CLASS_DECL_ca void __cdecl AtlTrace2(DWORD_PTR dwCategory, UINT nLevel, const char * pszFormat, ...);
   CLASS_DECL_ca void __cdecl AtlTrace2(DWORD_PTR dwCategory, UINT nLevel, const wchar_t * pszFormat, ...);
   #define ATLTRACENOTIMPL(funcname)  do { ATLTRACE(_template::atlTraceNotImpl, 0, "_template: %s not implemented.\n", funcname); return E_NOTIMPL; } while(0)


};  // namespace _template

