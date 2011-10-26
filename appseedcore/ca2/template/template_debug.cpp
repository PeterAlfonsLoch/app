#include "StdAfx.h"
#include "radix/common.h"
#include "trace_module_manager.h"

namespace _template
{

static bool WINAPI ShouldTraceOutput(DWORD_PTR dwModule,
                       DWORD_PTR dwCategory,
                       UINT nLevel,
                       const trace_category **ppCategory,
                       trace_module ** ppmodule);

void WINAPI NotifyTool()
{
   HANDLE hEvent;
   hEvent = OpenEventA(EVENT_MODIFY_STATE, FALSE, g_pszUpdateEventName);

   if(hEvent)
   {
      SetEvent(hEvent);
      CloseHandle(hEvent);
   }
}

// API
DWORD_PTR __stdcall AtlTraceRegister(HINSTANCE hInst,
                        int (__cdecl *fnDebugReport)(int,const char *,int,const char *,const char *,va_list))
{
   UNREFERENCED_PARAMETER(hInst);
   UNREFERENCED_PARAMETER(fnDebugReport);

   /*int iModule = g_Allocator.AddModule(hInst);
   trace_module* pModule = g_Allocator.GetModule(iModule);
   ATLASSERT(pModule != NULL);
   if(pModule != NULL)
   {
      pModule->DebugReport(fnDebugReport);
      NotifyTool();
   }

   return( DWORD_PTR( iModule )+1 );*/
   return 0;
}

BOOL __stdcall AtlTraceUnregister(DWORD_PTR dwModule)
{
   UNREFERENCED_PARAMETER(dwModule);
   /*int iModule = int( dwModule-1 );
   g_Allocator.RemoveModule( iModule );

   NotifyTool();

   return TRUE;*/
   return FALSE;
}

/*
DWORD_PTR __stdcall AtlTraceRegisterCategoryA(DWORD_PTR dwModule, const CHAR szCategoryName[ATL_TRACE_MAX_NAME_SIZE])
{
   if( szCategoryName == NULL )
   {
      return 0;
   }
   return AtlTraceRegisterCategoryU(dwModule, gen::international::utf8_to_unicode(szCategoryName));
}

DWORD_PTR __stdcall AtlTraceRegisterCategoryU(DWORD_PTR dwModule, const WCHAR szCategoryName[ATL_TRACE_MAX_NAME_SIZE])
{
   if( szCategoryName == NULL )
      return 0;

   int iModule = int( dwModule-1 );

   int iCategory = g_Allocator.AddCategory(iModule, szCategoryName);
   NotifyTool();

   return( DWORD_PTR( iCategory )+1 );
}
*/

/*
BOOL __stdcall AtlTraceModifyProcess(DWORD_PTR dwProcess, UINT nLevel, BOOL bEnabled,
                            BOOL bFuncAndCategoryNames, BOOL bFileNameAndLineNo)
{
   allocator* pAllocator = reinterpret_cast< allocator* >( dwProcess );
//#ifdef _DEBUG
   if( pAllocator == NULL )
   {
      pAllocator = &g_Allocator;
   }
//#endif  // _DEBUG

   trace_process* pProcess = pAllocator->GetProcess();
   ATLASSERT(pProcess != NULL);
   if(pProcess != NULL)
   {
      pProcess->m_nLevel = nLevel;
      pProcess->m_bEnabled = 0 != bEnabled;
      pProcess->m_bFuncAndCategoryNames = 0 != bFuncAndCategoryNames;
      pProcess->m_bFileNameAndLineNo = 0 != bFileNameAndLineNo;
   }

   return( TRUE );
}

BOOL __stdcall AtlTraceModifyModule(DWORD_PTR dwProcess, DWORD_PTR dwModule, UINT nLevel, ATLTRACESTATUS eStatus)
{
   allocator* pAllocator = reinterpret_cast< allocator* >( dwProcess );
//#ifdef _DEBUG
   if( pAllocator == NULL )
   {
      pAllocator = &g_Allocator;
   }
//#endif  // _DEBUG

   int iModule = int( dwModule-1 );

   trace_module* pModule = pAllocator->GetModule(iModule);
   ATLASSERT(pModule != NULL);
   if(pModule != NULL)
   {
      switch(eStatus)
      {
      case ATLTRACESTATUS_INHERIT:
         pModule->m_eStatus = trace_settings::Inherit;
         break;
      case ATLTRACESTATUS_ENABLED:
         pModule->m_eStatus = trace_settings::Enabled;
         break;
      case ATLTRACESTATUS_DISABLED:
         pModule->m_eStatus = trace_settings::Disabled;
         break;
      default:
         ATLASSERT( false );
         break;
      }
      pModule->m_nLevel = nLevel;
   }

   return( TRUE );
}

BOOL __stdcall AtlTraceModifyCategory(DWORD_PTR dwProcess, DWORD_PTR dwCategory,
                             UINT nLevel, ATLTRACESTATUS eStatus)
{
   allocator* pAllocator = reinterpret_cast< allocator* >( dwProcess );
//#ifdef _DEBUG
   if( pAllocator == NULL )
   {
      pAllocator = &g_Allocator;
   }
//#endif  // _DEBUG

   int iCategory = int( dwCategory-1 );
   trace_category *pCategory = pAllocator->GetCategory(iCategory);
   if(pCategory != NULL)
   {
      switch(eStatus)
      {
      case ATLTRACESTATUS_INHERIT:
         pCategory->m_eStatus = trace_settings::Inherit;
         break;
      case ATLTRACESTATUS_ENABLED:
         pCategory->m_eStatus = trace_settings::Enabled;
         break;
      case ATLTRACESTATUS_DISABLED:
         pCategory->m_eStatus = trace_settings::Disabled;
         break;
      default:
         ATLASSERT(false);
         break;
      }
      pCategory->m_nLevel = nLevel;
   }
   return TRUE;
}

BOOL __stdcall AtlTraceGetProcess(DWORD_PTR dwProcess, UINT *pnLevel, BOOL *pbEnabled,
                          BOOL *pbFuncAndCategoryNames, BOOL *pbFileNameAndLineNo)
{
   allocator* pAllocator = reinterpret_cast< allocator* >( dwProcess );
//#ifdef _DEBUG
   if( pAllocator == NULL )
   {
      pAllocator = &g_Allocator;
   }
//#endif  // _DEBUG

   trace_process* pProcess = pAllocator->GetProcess();
   ATLENSURE(pProcess != NULL);

   if(pnLevel)
      *pnLevel = pProcess->m_nLevel;
   if(pbEnabled)
      *pbEnabled = pProcess->m_bEnabled;
   if(pbFuncAndCategoryNames)
      *pbFuncAndCategoryNames = pProcess->m_bFuncAndCategoryNames;
   if(pbFileNameAndLineNo)
      *pbFileNameAndLineNo = pProcess->m_bFileNameAndLineNo;

   return( TRUE );
}


BOOL __stdcall AtlTraceGetCategory(DWORD_PTR dwProcess, DWORD_PTR dwCategory, UINT *pnLevel,
                           ATLTRACESTATUS *peStatus)
{
   allocator* pAllocator = reinterpret_cast< allocator* >( dwProcess );
//#ifdef _DEBUG
   if( pAllocator == NULL )
   {
      pAllocator = &g_Allocator;
   }
//#endif  // _DEBUG

   int iCategory = int( dwCategory-1 );
   trace_category* pCategory = pAllocator->GetCategory( iCategory );
   ATLENSURE(pCategory != NULL);

   if(pnLevel != NULL)
   {
      *pnLevel = pCategory->m_nLevel;
   }

   if(peStatus != NULL)
   {
      switch(pCategory->m_eStatus)
      {
      case trace_settings::Inherit:
         *peStatus = ATLTRACESTATUS_INHERIT;
         break;
      case trace_settings::Enabled:
         *peStatus = ATLTRACESTATUS_ENABLED;
         break;
      case trace_settings::Disabled:
         *peStatus = ATLTRACESTATUS_DISABLED;
         break;
      }
   }

   return( TRUE );
}

void __stdcall AtlTraceGetUpdateEventNameA(__out_opt CHAR *pszEventName)
{
   if( g_pszUpdateEventName == NULL || pszEventName == NULL )
   {
      return;
   }
#pragma warning(push)
#pragma warning(disable:4996)
   // This API is deprecated because the size of the buffer cannot be
   // known. Therefore, we have to use unsafe version of strcpy. The
   // warning is disabled to prevent build problems.
   strcpy(pszEventName, g_pszUpdateEventName);
#pragma warning(pop)
}

void __stdcall AtlTraceGetUpdateEventNameA_s(__out_ecount_opt(cchEventName) CHAR *pszEventName, size_t cchEventName)
{
   if( g_pszUpdateEventName == NULL || pszEventName == NULL )
   {
      return;
   }
   checked::strcpy_s(pszEventName, cchEventName, g_pszUpdateEventName);
}

void __stdcall AtlTraceGetUpdateEventNameU(__out_opt WCHAR *pszEventName)
{
   if( g_pszUpdateEventName == NULL || pszEventName == NULL )
   {
      return;
   }
#pragma warning(push)
#pragma warning(disable:4996)
   // This API is deprecated because the size of the buffer cannot be
   // known. Therefore, we have to use unsafe version of wcscpy. The
   // warning is disabled to prevent build problems.
   wcscpy(pszEventName, gen::international::utf8_to_unicode(g_pszUpdateEventName));
#pragma warning(pop)
}

void __stdcall AtlTraceGetUpdateEventNameU_s(__out_ecount_opt(cchEventName) WCHAR *pszEventName, size_t cchEventName)
{
   if( g_pszUpdateEventName == NULL || pszEventName == NULL )
   {
      return;
   }
   checked::wcscpy_s(pszEventName, cchEventName, gen::international::utf8_to_unicode(g_pszUpdateEventName));
}*/




void __cdecl AtlTraceVA(DWORD_PTR dwModule, const char *pszFileName, int nLine,
                  DWORD_PTR dwCategory, UINT nLevel, const CHAR *pszFormat, va_list ptr)
{
   UNREFERENCED_PARAMETER(dwModule);
   UNREFERENCED_PARAMETER(pszFileName);
   UNREFERENCED_PARAMETER(nLine);
   UNREFERENCED_PARAMETER(dwCategory);
   UNREFERENCED_PARAMETER(nLevel);
   UNREFERENCED_PARAMETER(pszFormat);
   UNREFERENCED_PARAMETER(ptr);

}

void __cdecl AtlTraceVU(DWORD_PTR dwModule, const char *pszFileName, int nLine,
                  DWORD_PTR dwCategory, UINT nLevel, const WCHAR *pszFormat, va_list ptr)
{
   UNREFERENCED_PARAMETER(dwModule);
   UNREFERENCED_PARAMETER(pszFileName);
   UNREFERENCED_PARAMETER(nLine);
   UNREFERENCED_PARAMETER(dwCategory);
   UNREFERENCED_PARAMETER(nLevel);
   UNREFERENCED_PARAMETER(pszFormat);
   UNREFERENCED_PARAMETER(ptr);

}

DWORD_PTR __stdcall AtlTraceOpenProcess(DWORD idProcess)
{
   allocator* pAllocator = new allocator;

   char szBuf[64];
   ATL_CRT_ERRORCHECK_SPRINTF(_snprintf_s(szBuf, _countof(szBuf), _countof(szBuf) - 1, g_pszKernelObjFmt, g_pszAllocFileMapName, idProcess));
   if( !pAllocator->open(szBuf) )
   {
      delete pAllocator;
      return( 0 );
   }

   return( reinterpret_cast< DWORD_PTR >( pAllocator ) );
}

void __stdcall AtlTraceCloseProcess( DWORD_PTR dwProcess )
{
   ATLENSURE(dwProcess!=NULL);

   allocator* pAllocator = reinterpret_cast< allocator* >( dwProcess );
   pAllocator->close( true );
   delete pAllocator;
}

void __stdcall AtlTraceSnapshotProcess( DWORD_PTR dwProcess )
{
   ATLENSURE(dwProcess!=NULL);

   allocator* pAllocator = reinterpret_cast< allocator* >( dwProcess );
   pAllocator->TakeSnapshot();
}

/*
BOOL __stdcall AtlTraceGetProcessInfo(DWORD_PTR dwProcess, ATLTRACEPROCESSINFO* pProcessInfo)
{
   ATLENSURE(dwProcess!=NULL);
   ATLASSERT(pProcessInfo != NULL);

   allocator* pAllocator = reinterpret_cast< allocator* >( dwProcess );
   ATLASSERT(pAllocator->m_bSnapshot);
   trace_process *pProcess = pAllocator->GetProcess();
   ATLASSERT(pProcess != NULL);

   if(pProcess)
   {
      wcsncpy_s(pProcessInfo->szName, _countof(pProcessInfo->szName), pProcess->Name(), _TRUNCATE);
      wcscpy_s(pProcessInfo->szPath, _countof(pProcessInfo->szPath), pProcess->Path());
      pProcessInfo->dwId = pProcess->Id();
      pProcessInfo->settings.nLevel = pProcess->m_nLevel;
      pProcessInfo->settings.bEnabled = pProcess->m_bEnabled;
      pProcessInfo->settings.bFuncAndCategoryNames = pProcess->m_bFuncAndCategoryNames;
      pProcessInfo->settings.bFileNameAndLineNo = pProcess->m_bFileNameAndLineNo;
      pProcessInfo->nModules = pAllocator->m_snapshot.m_aModules.get_size();
   }
   return( TRUE );
}

void __stdcall AtlTraceGetModuleInfo(DWORD_PTR dwProcess, int iModule, ATLTRACEMODULEINFO* pModuleInfo)
{
   ATLENSURE(dwProcess!=NULL);
   ATLASSERT(pModuleInfo != NULL);
   if( pModuleInfo == NULL )
      return;

   allocator* pAllocator = reinterpret_cast< allocator* >( dwProcess );
   ATLASSERT(pAllocator->m_bSnapshot);

   DWORD_PTR dwModule = pAllocator->m_snapshot.m_aModules[iModule].m_dwModule;
   trace_module* pModule = pAllocator->GetModule(int(dwModule-1));
   if( pModule == NULL )
      return;

   wcsncpy_s(pModuleInfo->szName, _countof(pModuleInfo->szName), pModule->Name(), _TRUNCATE);
   wcsncpy_s(pModuleInfo->szPath, _countof(pModuleInfo->szPath), pModule->Path(), _TRUNCATE);
   pModuleInfo->nCategories = pModule->m_nCategories;
   pModuleInfo->settings.nLevel = pModule->m_nLevel;
   pModuleInfo->dwModule = dwModule;
   switch(pModule->m_eStatus)
   {
   default:
   case trace_settings::Inherit:
      pModuleInfo->settings.eStatus = ATLTRACESTATUS_INHERIT;
      break;
   case trace_settings::Enabled:
      pModuleInfo->settings.eStatus = ATLTRACESTATUS_ENABLED;
      break;
   case trace_settings::Disabled:
      pModuleInfo->settings.eStatus = ATLTRACESTATUS_DISABLED;
      break;
   }
}

void __stdcall AtlTraceGetCategoryInfo(DWORD_PTR dwProcess, DWORD_PTR dwModule, int iCategory, ATLTRACECATEGORYINFO* pCategoryInfo)
{
   ATLENSURE(dwProcess!=NULL);
   ATLASSERT(pCategoryInfo != NULL);

   allocator* pAllocator = reinterpret_cast< allocator* >( dwProcess );
   ATLASSERT(pAllocator->m_bSnapshot);

   int iModule = int( dwModule-1 );
   trace_module* pModule = pAllocator->GetModule( iModule );
   if( pModule == NULL )
      return;

   trace_category* pCategory = pAllocator->GetCategory( pModule->m_iFirstCategory );

   int nCategory = pModule->m_iFirstCategory;
   for( int iCategoryIndex = 0; iCategoryIndex < iCategory; iCategoryIndex++ )
   {
      if( pCategory == NULL )
         return;
      nCategory = pCategory->m_iNextCategory;
      pCategory = pAllocator->GetCategory( pCategory->m_iNextCategory );
   }

   if( pCategory == NULL )
      return;

   wcsncpy_s(pCategoryInfo->szName, _countof(pCategoryInfo->szName), pCategory->Name(), _TRUNCATE);
   pCategoryInfo->settings.nLevel = pCategory->m_nLevel;
   pCategoryInfo->dwCategory = DWORD_PTR( nCategory )+1;
   switch(pCategory->m_eStatus)
   {
   case trace_settings::Inherit:
      pCategoryInfo->settings.eStatus = ATLTRACESTATUS_INHERIT;
      break;
   case trace_settings::Enabled:
      pCategoryInfo->settings.eStatus = ATLTRACESTATUS_ENABLED;
      break;
   case trace_settings::Disabled:
      pCategoryInfo->settings.eStatus = ATLTRACESTATUS_DISABLED;
      break;
   default:
      ATLASSERT( false );
      break;
   }
}
*/

static bool WINAPI ShouldTraceOutput(DWORD_PTR dwModule,
                       DWORD_PTR dwCategory,
                       UINT nLevel,
                       const trace_category **ppCategory,
                       trace_module ** ppmodule)
{
   UNREFERENCED_PARAMETER(dwModule);
   UNREFERENCED_PARAMETER(dwCategory);
   UNREFERENCED_PARAMETER(nLevel);
   UNREFERENCED_PARAMETER(ppCategory);
   UNREFERENCED_PARAMETER(ppmodule);


//   bool bFound = false;

   /*ATLASSERT(ppCategory && ppmodule);
   *ppCategory = NULL;
   *ppmodule = NULL;

   trace_process *pProcess = g_Allocator.GetProcess();
   ATLASSERT(pProcess);
   trace_module *pModule = g_Allocator.GetModule( int( dwModule-1 ) );

   ATLASSERT(pModule != NULL);
   if(pModule != NULL)
   {
      *ppmodule = pModule;

      trace_category *pCategory = g_Allocator.GetCategory( int( dwCategory-1 ) );
      if( pCategory != NULL )
      {
         bFound = true;
         bool bOut = false;

         if(pProcess->m_bEnabled &&
            pModule->m_eStatus == trace_settings::Inherit &&
            pCategory->m_eStatus == trace_settings::Inherit &&
            nLevel <= pProcess->m_nLevel)
         {
            bOut = true;
         }
         else if(pModule->m_eStatus == trace_settings::Enabled &&
            pCategory->m_eStatus == trace_settings::Inherit &&
            nLevel <= pModule->m_nLevel)
         {
            bOut = true;
         }
         else if(pCategory->m_eStatus == trace_settings::Enabled &&
            nLevel <= pCategory->m_nLevel)
         {
            bOut = true;
         }

         if(bOut)
         {
            *ppCategory = pProcess->m_bFuncAndCategoryNames ? pCategory : NULL;
            return true;
         }
      }
   }*/

   return false;
}

};  // namespace _template
