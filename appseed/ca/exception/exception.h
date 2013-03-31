#pragma once


#include "ca/ca/ca_exception.h"


#include "exception_engine.h"
#include "exception_call_stack.h"
#include "exception_base.h"

#include "exception_simple.h"

#include "exception_memory.h"
#include "exception_invalid_argument.h"

#include "exception_standard_translator.h"
#include "exception_standard.h"


namespace win
{
   CLASS_DECL_ca string error_message(uint32_t dwError);
}


namespace ca
{

   class application;

   CLASS_DECL_ca application * get_thread_app();

} // namespace ca

#include "exception_error.h"
#include "exception_overflow_error.h"
#include "exception_runtime_error.h"
#include "exception_range_error.h"


#include "exception_not_implemented.h"
#include "exception_void_implementation.h"
#include "exception_interface_only.h"
#include "exception_not_installed.h"
#include "exception_not_supported.h"
#include "exception_exit.h"
#include "exception_not_licensed.h"
#include "exception_temporary.h"
#include "exception_installing.h"

#include "exception_assert.h"
#include "exception_misc.h"



#include "exception_io.h"
#include "exception_resource.h"
#include "exception_user.h"





#include "exception_vms.h"





#include "exception_hresult.h"




#ifndef ___JUMPBUF
// Use portable 'jmp_buf' defined by ANSI by default.
#define ___JUMPBUF jmp_buf
#endif

namespace datetime
{


   class time_span;
   class time;


} // namespace datetime


// ::datetime::time_span diagnostics and serialization
CLASS_DECL_ca dump_context & operator<<(dump_context & dumpcontext, const ::datetime::time_span & dateSpanSrc);
CLASS_DECL_ca dump_context & operator<<(dump_context & dumpcontext, const ::datetime::time & dateSrc);


#if defined(DEBUG) && !defined(___NO_DEBUG_CRT)






#define afxMemDF _crtDbgFlag

enum e_memdbg // primitive::memory debug/diagnostic flags
{
   memdbg_alloc            = _CRTDBG_ALLOC_MEM_DF,         // turn on debugging allocator
   memdbg_delay_free       = _CRTDBG_DELAY_FREE_MEM_DF,         // delay freeing primitive::memory
   memdbg_check_always     = _CRTDBG_CHECK_ALWAYS_DF,          // __check_memory on every alloc/free
#if !core_level_1
   memdbg_check_every16    = _CRTDBG_CHECK_EVERY_16_DF,
   memdbg_check_every128   = _CRTDBG_CHECK_EVERY_128_DF,
   memdbg_check_every1024  = _CRTDBG_CHECK_EVERY_1024_DF,
   memdbg_check_default    = _CRTDBG_CHECK_DEFAULT_DF
#endif
};

#define __output_debug_string TRACE

// turn on/off tracking for a int16_t while
CLASS_DECL_ca bool __enable_memory_tracking(bool bTrack);

// Turn on/off the global flag gen_MemoryLeakOverride. if bEnable is TRUE
// then further calls to __enable_memory_tracking() wont change the current
// primitive::memory tracking state, until __enable_memory_leak_override(bool bEnable)
// is called again with bEnable == FALSE.
CLASS_DECL_ca bool __enable_memory_leak_override(bool bEnable);


// A failure hook returns whether to permit allocation
typedef bool (* __ALLOC_HOOK)(size_t nSize, bool bObject, LONG lRequestNumber);

// set new hook, return old (never NULL)
CLASS_DECL_ca __ALLOC_HOOK __set_alloc_hook(__ALLOC_HOOK pfnAllocHook);

#include "exception_memory_state.h"

// Enumerate allocated objects or runtime classes
/*void __do_for_all_objects(void (c_cdecl *pfn)(::ca::object* pObject, void * pContext),
   void * pContext);
void ::ca::DoForAllClasses(void (c_cdecl *pfn)(::ca::type_info pClass,
   void * pContext), void * pContext);*/

#define new DEBUG_NEW

#else

// non-DEBUG_ALLOC version that assume everything is OK
#define DEBUG_NEW new
#define __check_memory() TRUE
#define __is_memory_block(p, nBytes) TRUE
#define __enable_memory_tracking(bTrack) FALSE
#define __enable_memory_leak_override(bEnable) TRUE
#define __output_debug_string(lpsz) ::OutputDebugString(lpsz)

// diagnostic initialization
#ifndef DEBUG
#define __diagnostic_init() TRUE
#else
bool __diagnostic_init();
#endif

#endif // DEBUG



#define __stack_dump_TARGET_TRACE                     0x0001
#define __stack_dump_TARGET_CLIPBOARD 0x0002
#define __stack_dump_TARGET_BOTH                      0x0003
#define __stack_dump_TARGET_ODS                       0x0004
#ifdef DEBUG
#define __stack_dump_TARGET_DEFAULT           __stack_dump_TARGET_TRACE
#else
#define __stack_dump_TARGET_DEFAULT           __stack_dump_TARGET_CLIPBOARD
#endif

void __dump_stack(uint32_t dwFlags = __stack_dump_TARGET_DEFAULT);

#include "exception_dump_context.h"

#ifdef DEBUG
extern CLASS_DECL_ca dump_context g_dumpcontext;
extern CLASS_DECL_ca bool g_bTraceEnabled;
#endif

#ifdef DEBUG
#define _DUMP( exp ) (void)(g_dumpcontext<<exp)
#else
#define _DUMP( exp )
#endif










namespace ca
{


   class object;


} // namespace ca


#ifdef DEBUG
#define DEBUG_NEW new(__FILE__, __LINE__)
#endif








/////////////////////////////////////////////////////////////////////////////
// Diagnostic support



CLASS_DECL_ca bool __assert_failed_line(const char * lpszFileName, int32_t nLine);

CLASS_DECL_ca void c_cdecl __trace(const char * lpszFormat, ...);
// Note: file names are still ANSI strings (filenames rarely need UNICODE)
CLASS_DECL_ca void assert_valid_object(const ::ca::object* pOb,
            const char * lpszFileName, int32_t nLine);
CLASS_DECL_ca void __dump(const ::ca::object* pOb); // dump an object from CodeView


// extern ::ca::CTrace TRACE;
#ifdef DEBUG
#ifndef TRACE
#define TRACE ::ca::trace_add_file_and_line(m_papp, __FILE__, __LINE__)
#define APPTRACE(papp) ::ca::trace_add_file_and_line(papp, __FILE__, __LINE__)
//#define TRACE2 TRACE
#endif
#define THIS_FILE          __FILE__
#define VERIFY(f)          ASSERT(f)
//#define DEBUG_ONLY(f)      (f)

// The following trace macros are provided for backward compatiblity
//  (they also take a fixed number of parameters which provides
//   some amount of extra error checking)
#define TRACE0(sz)              TRACE("%s", (const char *) (sz))
#define TRACE1(sz, p1)          TRACE(sz, p1)
#define TRACE2(sz, p1, p2)      TRACE(sz, p1, p2)
#define TRACE3(sz, p1, p2, p3)  TRACE(sz, p1, p2, p3)

// These __dump macros also provided for backward compatibility
#define __dump0(spgraphics, sz)   dumpcontext << _T(sz)
#define __dump1(spgraphics, sz, p1) dumpcontext << _T(sz) << p1


#define DEBUG_ONLY(f)      (f)

#else

#define DEBUG_ONLY(f)      ((void)0)

#define VERIFY(f)          ((void)(f))
#define DEBUG_ONLY(f)      ((void)0)
#pragma warning(push)
#pragma warning(disable : 4793)
inline void c_cdecl __trace(...) { }
#pragma warning(pop)
#define TRACE              __noop
#define TRACE0(sz)
#define TRACE1(sz, p1)
#define TRACE2(sz, p1, p2)
#define TRACE3(sz, p1, p2, p3)

#endif // !DEBUG*/

#include "exception_debug.h"


#ifdef DEBUG

//#define ASSERT(f)          DEBUG_ONLY(() ((f) || !::__assert_failed_line(THIS_FILE, __LINE__) || (__debug_break(), 0)))
#define ASSERT(f)          ((void) ((f) || (is_debugger_attached() && (!::__assert_failed_line(__FILE__, __LINE__) || (__debug_break(), 0))) || (!is_debugger_attached() && (throw assert_exception(::ca::get_thread_app(), __FILE__, __LINE__), 0))))
/* see ca headers for commentary on this */
/* We use the name _ASSUME to avoid name clashes */
#define _ASSUME(cond)       do { bool _gen__condVal=!!(cond); ASSERT(_gen__condVal); __analysis_assume(_gen__condVal); } while(0)
//#define ASSERT_VALID(pOb)  DEBUG_ONLY((::assert_valid_object(pOb, THIS_FILE, __LINE__)))
#define ASSERT_VALID(pOb)  ((::assert_valid_object(pOb, __FILE__, __LINE__)))
#else
#define ASSERT(f)
#define _ASSUME(cond)
#define ASSERT_VALID(cond) __noop;
#endif

// Debug ASSERTs then throws. Retail throws if condition not met
#define ENSURE_THROW(cond, exception)   \
   do { int32_t _gen__condVal=!!(cond); ASSERT(_gen__condVal); if (!(_gen__condVal)){exception;} } while (false)
#define ENSURE(cond)      ENSURE_THROW(cond, throw invalid_argument_exception(::ca::get_thread_app()) )
#define ENSURE_ARG(cond)   ENSURE_THROW(cond, throw invalid_argument_exception(::ca::get_thread_app()) )

// Debug ASSERT_VALIDs then throws. Retail throws if pOb is NULL
#define ENSURE_VALID_THROW(pOb, exception)   \
   do { ASSERT_VALID(pOb); if (!(pOb)){exception;} } while (false)
#define ENSURE_VALID(pOb)   ENSURE_VALID_THROW(pOb, throw invalid_argument_exception(::ca::get_thread_app()) )

#define ASSERT_POINTER(p, type) \
   ASSERT(((p) != NULL) && __is_valid_address((p), sizeof(type), FALSE))

#define ASSERT_NULL_OR_POINTER(p, type) \
   ASSERT(((p) == NULL) || __is_valid_address((p), sizeof(type), FALSE))


#ifdef __GNUC__
#  define UNUSED_ALWAYS(x) __attribute__((__unused__))
#elif defined(_MSC_VER)
#  define UNUSED_ALWAYS(x)
#else
#	define UNUSED_ALWAYS(x) x
#endif


#ifdef DEBUG
#	define UNUSED(x) x
#else
#  define UNUSED(x) UNUSED_ALWAYS(x)
#endif


#ifdef DEBUG
#define REPORT_EXCEPTION(pException, szMsg) \
   do { \
      string str; \
      if (pException->get_error_message(str, 0)) \
         TRACE(::ca::trace::category_AppMsg, 0, "%s (%s:%d)\n%s\n", szMsg, __FILE__, __LINE__, str); \
      else \
         TRACE(::ca::trace::category_AppMsg, 0, "%s (%s:%d)\n", szMsg, __FILE__, __LINE__); \
      ASSERT(FALSE); \
   } while (0)
#else
#define REPORT_EXCEPTION(pException, szMsg) \
   do { \
      string strMsg; \
      char  szErrorMessage[512]; \
      if (pException->get_error_message(szErrorMessage, sizeof(szErrorMessage)/sizeof(*szErrorMessage), 0)) \
         strMsg.Format("%s (%s:%d)\n%s", szMsg, __FILE__, __LINE__, szErrorMessage); \
      else \
         strMsg.Format("%s (%s:%d)", szMsg, __FILE__, __LINE__); \
      System.simple_message_box(strMsg); \
   } while (0)
#endif



#define EXCEPTION_IN_DTOR(pException) \
   do { \
      REPORT_EXCEPTION((pException), "Exception thrown in destructor"); \
      delete pException; \
   } while (0)

#define __BEGIN_DESTRUCTOR try {
#define __END_DESTRUCTOR   } catch (base_exception *pException) { EXCEPTION_IN_DTOR(pException); }



#define C_RUNTIME_ERROR_CHECK(expr) ::c_runtime_error_check(expr)
#ifndef C_RUNTIME_ERRORCHECK_SPRINTF
#define C_RUNTIME_ERRORCHECK_SPRINTF(expr) \
do { \
   errno_t _saveErrno = errno; \
   errno = 0; \
   (expr); \
   if(0 != errno) \
   { \
      ::c_runtime_error_check(errno); \
   } \
   else \
   { \
      errno = _saveErrno; \
   } \
} while (0)
#endif // C_RUNTIME_ERRORCHECK_SPRINTF


inline errno_t c_runtime_error_check(errno_t error)
{
    switch(error)
    {
        case ENOMEM:
            throw memory_exception(::ca::get_thread_app());
            break;
        case EINVAL:
        case ERANGE:
            throw invalid_argument_exception(::ca::get_thread_app());
            break;
#if defined(WINDOWS)
        case STRUNCATE:
#endif
        case 0:
            break;
        default:
            throw invalid_argument_exception(::ca::get_thread_app());
            break;
    }
    return error;
}

inline void __cdecl __clearerr_s(FILE *stream)
{
#ifdef WINDOWS
   C_RUNTIME_ERROR_CHECK(::clearerr_s(stream));
#else
   ::clearerr(stream);
   C_RUNTIME_ERROR_CHECK(errno);
#endif
}





#include "exception_last_error.h"

// mrs/src as of 2012-08-18
// cybase/os/exception
#include "exception_os.h"
#include "exception_invalid_index.h"
#include "exception_invalid_handle.h"
#include "exception_operation_canceled.h"


#include "exception_invalid_character.h"

#include "exception_todo.h"


