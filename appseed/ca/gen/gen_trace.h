#pragma once



#ifdef WINDOWS

extern "C" IMAGE_DOS_HEADER __ImageBase;

#endif


namespace gen
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

      class trace;

      // Declare a global instance of this class to automatically register a custom trace category at startup
      class CLASS_DECL_ca category
      {
      public:

         category();
         ~category();

         UINT GetLevel() const throw();
         void SetLevel( UINT nLevel ) throw();
         e_status GetStatus() const throw();
         void SetStatus(e_status eStatus) throw();

         operator DWORD() const throw();

         unsigned int      m_dwCategory;
         string            m_strCategory;
         UINT              m_uiLevel;
         e_status          m_estatus;
      };


      class CLASS_DECL_ca trace
      {
      public:

         ::ca::application * m_papp;

         trace(::ca::application * papp)
         {
            m_papp = papp;
         }

         ~trace()
         {
         }

         category & operator[](DWORD_PTR dwCategory)
         {
            return m_map[dwCategory];
         }

         void TraceV(const char *pszFileName, int nLine, DWORD_PTR dwCategory, UINT nLevel, const char * pszFmt, va_list args) const;


         /*bool LoadSettings(const char * pszFileName = NULL) const
         { return 0 != gen_TraceLoadSettings(pszFileName);}
         void SaveSettings(const char * pszFileName = NULL) const
         { gen_TraceSaveSettings(pszFileName);}*/

         collection::map < DWORD_PTR, DWORD_PTR, category, category > m_map;
      };



#ifndef _NO_DEBUG_CRT
      class CNoUIAssertHook
      {
      public:
         CNoUIAssertHook()
         {
            ASSERT( s_pfnPrevHook == NULL );
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

#define DECLARE_NOUIASSERT() gen::CNoUIAssertHook _g_NoUIAssertHook;

#endif  // _NO_DEBUG_CRT


      CLASS_DECL_ca void __cdecl __trace(const char * pszFormat, ...);
      CLASS_DECL_ca void __cdecl __trace(const wchar_t * pszFormat, ...);
      CLASS_DECL_ca void __cdecl __trace(DWORD_PTR dwCategory, UINT nLevel, const char * pszFormat, ...);
      CLASS_DECL_ca void __cdecl __trace(DWORD_PTR dwCategory, UINT nLevel, const wchar_t * pszFormat, ...);
#define TRACENOTIMPL(funcname)  do { TRACE(gen::atlTraceNotImpl, 0, "gen: %s not implemented.\n", funcname); return E_NOTIMPL; } while(0)
   } // namespace trace
    

};  // namespace gen

