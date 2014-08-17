#pragma once



#ifdef WINDOWS

extern "C" IMAGE_DOS_HEADER __ImageBase;

#endif


namespace axis
{

   //typedef void ( * PFN_trace_v)(const char *pszFileName, int32_t nLine, uint32_t dwCategory, uint32_t nLevel, const char * pszFmt, va_list args);

   CLASS_DECL_AXIS void raw_trace_v(const char *pszFileName, int32_t nLine, uint32_t dwCategory, uint32_t nLevel, const char * pszFmt, va_list args);
   //CLASS_DECL_AXIS void system_log_trace_v(const char *pszFileName, int32_t nLine, uint32_t dwCategory, uint32_t nLevel, const char * pszFmt, va_list args);

   //extern CLASS_DECL_AXIS PFN_trace_v trace_v;

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
         category_AppMsg = 500,        // main message pump trace (includes DDE)
         category_WinMsg,        // Windows message tracing
         category_CmdRouting,    // Windows command routing trace
         category_Ole,          // special OLE callback trace
         category_Database,     // special database trace
         category_Internet,     // special Internet client trace
         category_dumpContext,   // traces from dump_context
         category_Memory,      // generic non-kernel primitive::memory traces
         category_Html,         // Html traces
         category_Socket      // socket traces
            
      };
      

      class trace;

      
      // Declare a global instance of this class to automatically register a custom trace category at startup
      class CLASS_DECL_AXIS category
      {
      public:

         
         category();
         ~category();
         

         UINT GetLevel() const throw();
         void SetLevel(UINT nLevel) throw();
         e_status GetStatus() const throw();
         void SetStatus(e_status eStatus) throw();

         operator uint32_t() const throw();

         uint32_t      m_dwCategory;
         string            m_strCategory;
         UINT              m_uiLevel;
         e_status          m_estatus;
      };


      class CLASS_DECL_AXIS trace
      {
      public:

         sp(::axis::application) m_pbaseapp;

         trace(sp(::axis::application) papp)
         {
            m_pbaseapp = papp;
         }

         ~trace()
         {
         }

         category & operator[](uint_ptr dwCategory)
         {
            return m_map[dwCategory];
         }

         void TraceV(const char *pszFileName, int32_t nLine, uint_ptr dwCategory, UINT nLevel, const char * pszFmt, va_list args) const;


         /*bool LoadSettings(const char * pszFileName = NULL) const
         { return 0 != gen_TraceLoadSettings(pszFileName);}
         void SaveSettings(const char * pszFileName = NULL) const
         { gen_TraceSaveSettings(pszFileName);}*/

         map < uint_ptr, uint_ptr, category, category > m_map;
      };



#ifndef _NO_DEBUG_CRT
      class CNoUIAssertHook
      {
      public:
         CNoUIAssertHook()
         {
            ASSERT(s_pfnPrevHook == NULL);
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
         static int32_t __cdecl CrtHookProc(int32_t eReportType, char* pszMessage, int32_t* pnRetVal)
         {

            if (eReportType == _CRT_ASSERT)
            {
               ::OutputDebugStringA("ASSERTION FAILED\n");
               ::OutputDebugStringA(pszMessage);
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

      __declspec(selectany) _CRT_REPORT_HOOK CNoUIAssertHook::s_pfnPrevHook = NULL;

#endif

#define DECLARE_NOUIASSERT() ::core::CNoUIAssertHook _g_NoUIAssertHook;

#endif  // _NO_DEBUG_CRT


      CLASS_DECL_AXIS void __cdecl __trace(const char * pszFormat, ...);
      CLASS_DECL_AXIS void __cdecl __trace(const wchar_t * pszFormat, ...);
      CLASS_DECL_AXIS void __cdecl __trace(uint_ptr dwCategory, UINT nLevel, const char * pszFormat, ...);
      CLASS_DECL_AXIS void __cdecl __trace(uint_ptr dwCategory, UINT nLevel, const wchar_t * pszFormat, ...);
#define TRACENOTIMPL(funcname)  do { TRACE(::core::atlTraceNotImpl, 0, "core: %s not implemented.\n", funcname); return E_NOTIMPL; } while(0)
   } // namespace trace


};  // namespace axis

