#pragma once



// This is core API library.
// 
// 
//
// 
// 
// 
// 
// 


#ifndef __DEBUGAPI_H__
#define __DEBUGAPI_H__

#pragma once

#ifdef __cplusplus

namespace core
{
extern "C" {
#endif
#define TRACE_MAX_NAME_SIZE 64


uint_ptr __stdcall gen_TraceOpenProcess( uint32_t idProcess );
void __stdcall gen_TraceCloseProcess( uint_ptr dwProcess );
void __stdcall gen_TraceSnapshotProcess( uint_ptr dwProcess );


void __cdecl gen_TraceVA(uint_ptr dwModule, const char *pszFileName, int32_t nLineNo,
                  uint_ptr dwCategory, UINT nLevel, const CHAR *pszFormat, va_list ptr);
void __cdecl gen_TraceVU(uint_ptr dwModule,const char *pszFileName, int32_t nLineNo,
                  uint_ptr dwCategory, UINT nLevel, const WCHAR *pszFormat, va_list ptr);

bool __stdcall gen_TraceLoadSettingsA(const CHAR *pszFileName, uint_ptr dwProcess = 0);
bool __stdcall gen_TraceLoadSettingsU(const WCHAR *pszFileName, uint_ptr dwProcess = 0);
bool __stdcall gen_TraceSaveSettingsA(const CHAR *pszFileName, uint_ptr dwProcess = 0);
bool __stdcall gen_TraceSaveSettingsU(const WCHAR *pszFileName, uint_ptr dwProcess = 0);

/*typedef struct TRACESETTINGS
{
   UINT nLevel;
   TRACESTATUS eStatus;
} TRACESETTINGS;

typedef struct TRACEPROCESSSETTINGS
{
   UINT nLevel;
   bool bEnabled, bFuncAndCategoryNames, bFileNameAndLineNo;
} TRACEPROCESSSETTINGS;

typedef struct TRACEPROCESSINFO
{
   WCHAR szName[TRACE_MAX_NAME_SIZE], szPath[MAX_PATH];
   uint32_t dwId;
   TRACEPROCESSSETTINGS settings;
   int32_t nModules;
} TRACEPROCESSINFO;

typedef struct TRACEMODULEINFO
{
   WCHAR szName[TRACE_MAX_NAME_SIZE], szPath[MAX_PATH];
   TRACESETTINGS settings;
   uint_ptr dwModule;
   int32_t nCategories;
} TRACEMODULEINFO;

typedef struct TRACECATEGORYINFO
{
   WCHAR szName[TRACE_MAX_NAME_SIZE];
   TRACESETTINGS settings;
   uint_ptr dwCategory;
} TRACECATEGORYINFO;

bool __stdcall gen_TraceGetProcessInfo(uint_ptr dwProcess, TRACEPROCESSINFO* pProcessInfo);
void __stdcall gen_TraceGetModuleInfo(uint_ptr dwProcess, int32_t iModule, TRACEMODULEINFO* pModuleInfo);
void __stdcall gen_TraceGetCategoryInfo(uint_ptr dwProcess, uint_ptr dwModule, int32_t iCategory, TRACECATEGORYINFO* pAtlTraceCategoryInfo);
*/

#ifdef UNICODE
#define gen_TraceRegisterCategory AtlTraceRegisterCategoryU
#define gen_TraceGetUpdateEventName AtlTraceGetUpdateEventNameU
#define gen_TraceGetUpdateEventName_s AtlTraceGetUpdateEventNameU_s
#define gen_Trace AtlTraceU
#define gen_TraceV AtlTraceVU
#define gen_TraceLoadSettings AtlTraceLoadSettingsU
#define gen_TraceSaveSettings AtlTraceSaveSettingsU

#else
#define gen_TraceRegisterCategory AtlTraceRegisterCategoryA
#define gen_TraceGetUpdateEventName AtlTraceGetUpdateEventNameA
#define gen_TraceGetUpdateEventName_s AtlTraceGetUpdateEventNameA_s
#define gen_Trace AtlTraceA
#define gen_TraceV AtlTraceVA
#define gen_TraceLoadSettings AtlTraceLoadSettingsA
#define gen_TraceSaveSettings AtlTraceSaveSettingsA

#endif

#ifdef __cplusplus
};

};  // namespace core
#endif

#endif  // __DEBUGAPI_H__
