#include "StdAfx.h"
#include "trace_module_manager.h"

extern HINSTANCE g_hInst;

trace_module_info::trace_module_info() :
   m_hInst(NULL),
   m_nCategories(0),
   m_iFirstCategory(-1)
{
   m_szPath[0] = L'\0';
   m_szName[0] = L'\0';
}

void trace_module_info::Reset(HINSTANCE hInst)
{
   WCHAR szModulePath[MAX_PATH] = {L'\0'};
   
   GetModuleFileNameW(hInst, szModulePath, MAX_PATH);
   
   szModulePath[MAX_PATH - 1] = 0;
   
#if _SECURE_ATL
   ATL_CRT_ERRORCHECK(wcsncpy_s(m_szPath, _countof(m_szPath), szModulePath, _TRUNCATE));
#else
   wcsncpy(m_szPath, szModulePath, MAX_PATH - 1);
#endif
   WCHAR *pszShortName = m_szPath + wcslen(m_szPath);
   while(pszShortName > m_szPath && *(pszShortName - 1) != L'\\')
      pszShortName--;
#if _SECURE_ATL
   ATL_CRT_ERRORCHECK(wcsncpy_s(m_szName, _countof(m_szName), pszShortName, ATL_TRACE_MAX_NAME_SIZE - 1));
#else
   wcsncpy(m_szName, pszShortName, ATL_TRACE_MAX_NAME_SIZE - 1);
#endif

   m_hInst = hInst;
   m_nCategories = 0;
   m_iFirstCategory = -1;
}

// Categories
trace_category::trace_category() : 
   m_nModuleCookie(0)
{
//   Reset(L"", 0);
}


void trace_category::Reset(const CHAR *pszName, LONG nModuleCookie)
{
   m_strName         = pszName;
   m_nModuleCookie   = nModuleCookie;
}


// Modules
trace_module::trace_module()
{
   m_functionlist.m_pfnDebugReport = NULL;
   m_functionlist.m_pnext = NULL;
}

int trace_module::DebugReport(int i1 ,const CHAR * psz1,int i2,const CHAR * psz2,const CHAR * psz3,...)
{
   va_list args;
   va_start(args, psz3);
   int i = DebugReport(i1, psz1, i2, psz2, psz3, args);
   va_end(args);
   return i;
}
int trace_module::DebugReport(int i1 ,const CHAR * psz1,int i2,const CHAR * psz2,const CHAR * psz3,va_list args)
{
   function_list * plist = &m_functionlist;
   int i = 0;
   while(plist != NULL)
   {
      if(m_functionlist.m_pfnDebugReport != NULL)
      {
         i = m_functionlist.m_pfnDebugReport(i1, psz1, i2, psz2, psz3, args);
      }
      plist = plist->m_pnext;
   }
   return i;
}


void trace_module::DebugReport(trace_module::fnDebugReport_t pfnDebugReport)
{
   function_list * plist = &m_functionlist;
   while(plist->m_pfnDebugReport != NULL)
      plist = plist->m_pnext;
   if(plist->m_pfnDebugReport == NULL)
   {
      plist->m_pfnDebugReport = pfnDebugReport;
      return;
   }
   plist->m_pnext = new function_list;
   plist = plist->m_pnext;
   plist->m_pfnDebugReport = pfnDebugReport;
   plist->m_pnext = NULL;
}

// Processes
trace_process::trace_process(DWORD_PTR dwMaxSize) :
   trace_module_info(),
   m_dwId(GetCurrentProcessId()), m_nRef(1), m_dwMaxSize(dwMaxSize),
   m_dwFrontAlloc(0), m_dwBackAlloc(0), m_dwCurrFront(0), m_dwCurrBack(0),
   m_nLevel(0), m_bLoaded(false), m_bEnabled(true), m_bFuncAndCategoryNames(false), m_bFileNameAndLineNo(false),
   m_nNextCookie( 0 )
{
   m_pvBase = this;

   Reset( NULL );
}

LONG trace_process::GetNextCookie()
{
   return( ::InterlockedIncrement( &m_nNextCookie ) );
}


int debug_reporter::DebugReport(int i1, const char * psz1, int i2, const char * psz2, const char * psz3, va_list args)
{
   return _001OnDebugReport(i1, psz1, i2, psz2, psz3, args);
}
