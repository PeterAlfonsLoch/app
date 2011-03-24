#include "StdAfx.h"


#include "common.h"
#include "allocate.h"


#pragma warning(disable : 4074)
#pragma init_seg(compiler)

const char *g_pszUpdateEventName   = "AtlTraceModuleManager_ProcessAddedStatic3";
const char *g_pszAllocFileMapName   = "AtlDebugAllocator_FileMappingNameStatic3";

const char *g_pszKernelObjFmt = "%s_%0x";

//allocator g_Allocator;

static bool WINAPI Init()
{
   char szFileMappingName[MAX_PATH];

   int ret;
   ATL_CRT_ERRORCHECK_SPRINTF(ret = _snprintf_s(szFileMappingName, _countof(szFileMappingName), _countof(szFileMappingName) - 1, g_pszKernelObjFmt,
      g_pszAllocFileMapName, GetCurrentProcessId()));
   
   if(ret == -1 || ret >= MAX_PATH)
   {
      throw _template::CAtlException( E_FAIL );
   }
   // surely four megs is enough?
  // if( !g_Allocator.Init(szFileMappingName, 4*1024*1024 ) )
   //{
    //  throw _template::CAtlException( E_OUTOFMEMORY );
   //}

   return true;
}

//static const bool g_bInitialized = Init();

