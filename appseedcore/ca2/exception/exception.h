#pragma once


#include "ca/ca_exception.h"


#include "class.h"
#include "base_exception.h"
#include "se_exception.h"


namespace win
{
   CLASS_DECL_ca string error_message(DWORD dwError);
}

#include "error_exception.h"
#include "not_implemented.h"
#include "interface_only.h"
#include "not_supported.h"

#include "simple.h"
#include "assert.h"
#include "misc.h"

#include "memory.h"

#include "invalid_argument.h"


#include "resource.h"
#include "user.h"

#include "VMSException.h"



#ifndef _AFX_JUMPBUF
// Use portable 'jmp_buf' defined by ANSI by default.
#define _AFX_JUMPBUF jmp_buf
#endif


// time_span diagnostics and serialization
CLASS_DECL_ca dump_context& operator<<(dump_context & dumpcontext,time_span dateSpanSrc);
CLASS_DECL_ca dump_context& operator<<(dump_context & dumpcontext, class time dateSrc);

// Low level sanity checks for primitive::memory blocks
CLASS_DECL_ca BOOL fx_is_valid_address(const void * lp, UINT_PTR nBytes, BOOL bReadWrite = TRUE);
CLASS_DECL_ca BOOL AfxIsValidString(const wchar_t * lpsz, int nLength = -1);
CLASS_DECL_ca BOOL AfxIsValidString(const char * lpsz, int nLength = -1);

// Sanity checks for ATOMs
CLASS_DECL_ca BOOL AfxIsValidAtom(ATOM nAtom);
CLASS_DECL_ca BOOL AfxIsValidAtom(const char * psz);

#if defined(_DEBUG) && !defined(_AFX_NO_DEBUG_CRT)






#define afxMemDF _crtDbgFlag

enum AfxMemDF // primitive::memory debug/diagnostic flags
{
   allocMemDF          = _CRTDBG_ALLOC_MEM_DF,         // turn on debugging allocator
   delayFreeMemDF      = _CRTDBG_DELAY_FREE_MEM_DF,         // delay freeing primitive::memory
   checkAlwaysMemDF    = _CRTDBG_CHECK_ALWAYS_DF,          // AfxCheckMemory on every alloc/free
#if !core_level_1
   checkEvery16MemDF   = _CRTDBG_CHECK_EVERY_16_DF,
   checkEvery128MemDF   = _CRTDBG_CHECK_EVERY_128_DF,
   checkEvery1024MemDF   = _CRTDBG_CHECK_EVERY_1024_DF,
   checkDefaultMemDF   = _CRTDBG_CHECK_DEFAULT_DF
#endif
};

#define AfxOutputDebugString TRACE

// turn on/off tracking for a short while
CLASS_DECL_ca BOOL AfxEnableMemoryTracking(BOOL bTrack);

// Turn on/off the global flag _afxMemoryLeakOverride. if bEnable is TRUE
// then further calls to AfxEnableMemoryTracking() wont change the current
// primitive::memory tracking state, until AfxEnableMemoryLeakOverride(BOOL bEnable)
// is called again with bEnable == FALSE.
CLASS_DECL_ca BOOL AfxEnableMemoryLeakOverride(BOOL bEnable);


// A failure hook returns whether to permit allocation
typedef BOOL (* AFX_ALLOC_HOOK)(size_t nSize, BOOL bObject, LONG lRequestNumber);

// Set new hook, return old (never NULL)
CLASS_DECL_ca AFX_ALLOC_HOOK AfxSetAllocHook(AFX_ALLOC_HOOK pfnAllocHook);

#include "memory_state.h"

// Enumerate allocated objects or runtime classes
/*void AfxDoForAllObjects(void (AFX_CDECL *pfn)(::radix::object* pObject, void * pContext),
   void * pContext);
void AfxDoForAllClasses(void (AFX_CDECL *pfn)(::ca::type_info pClass,
   void * pContext), void * pContext);*/

#define new DEBUG_NEW

#else

// non-_DEBUG_ALLOC version that assume everything is OK
#define DEBUG_NEW new
#define AfxCheckMemory() TRUE
#define AfxIsMemoryBlock(p, nBytes) TRUE
#define AfxEnableMemoryTracking(bTrack) FALSE
#define AfxEnableMemoryLeakOverride(bEnable) TRUE
#define AfxOutputDebugString(lpsz) ::OutputDebugString(lpsz)

// diagnostic initialization
#ifndef _DEBUG
#define AfxDiagnosticInit() TRUE
#else
BOOL AfxDiagnosticInit(void);
#endif

#endif // _DEBUG



#define AFX_STACK_dump_TARGET_TRACE                     0x0001
#define AFX_STACK_dump_TARGET_CLIPBOARD 0x0002
#define AFX_STACK_dump_TARGET_BOTH                      0x0003
#define AFX_STACK_dump_TARGET_ODS                       0x0004
#ifdef _DEBUG
#define AFX_STACK_dump_TARGET_DEFAULT           AFX_STACK_dump_TARGET_TRACE
#else
#define AFX_STACK_dump_TARGET_DEFAULT           AFX_STACK_dump_TARGET_CLIPBOARD
#endif

void AfxdumpStack(DWORD dwFlags = AFX_STACK_dump_TARGET_DEFAULT);

#include "dump_context.h"

#ifdef _DEBUG
extern AFX_DATA dump_context afxdump;
extern AFX_DATA BOOL afxTraceEnabled;
#endif

#ifdef _DEBUG
#define AFXDUMP( exp ) (void)(afxdump<<exp)
#else
#define AFXDUMP( exp )
#endif



