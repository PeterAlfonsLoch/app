#pragma once


namespace radix
{


   class object;


} // namespace radix


#ifdef _DEBUG
#define DEBUG_NEW new(__FILE__, __LINE__)
#endif


/////////////////////////////////////////////////////////////////////////////
// Standard exception throws

CLASS_DECL_ca void DECLSPEC_NO_RETURN AfxThrowMemoryException();
CLASS_DECL_ca void DECLSPEC_NO_RETURN AfxThrowNotSupportedException();
CLASS_DECL_ca void DECLSPEC_NO_RETURN AfxThrowInvalidArgException();
//CLASS_DECL_ca void DECLSPEC_NO_RETURN AfxThrowArchiveException(int cause, const char * lpszArchiveName = NULL);
CLASS_DECL_ca void DECLSPEC_NO_RETURN AfxThrowFileException(int cause, LONG lOsError = -1, const char * lpszFileName = NULL);


/////////////////////////////////////////////////////////////////////////////
// CRT functions

inline errno_t c_runtime_error_check(errno_t error)
{
   switch(error)
   {
   case ENOMEM:
      AfxThrowMemoryException();
      break;
   case EINVAL:
   case ERANGE:
      AfxThrowInvalidArgException();
      break;
#if defined(_WINDOWS)
   case STRUNCATE:
#endif
   case 0:
      break;
   default:
      AfxThrowInvalidArgException();
      break;
   }
   return error;
}

//#define C_RUNTIME_ERROR_CHECK(expr) ::c_runtime_error_check(expr)


inline void __cdecl Afx_clearerr_s(FILE *stream)
{
#ifdef _WINDOWS
   C_RUNTIME_ERROR_CHECK(::clearerr_s(stream));
#else
   ::clearerr(stream);
#endif
}


/////////////////////////////////////////////////////////////////////////////
// Diagnostic support



CLASS_DECL_ca BOOL AfxAssertFailedLine(const char * lpszFileName, int nLine);

CLASS_DECL_ca void AFX_CDECL AfxTrace(const char * lpszFormat, ...);
// Note: file names are still ANSI strings (filenames rarely need UNICODE)
CLASS_DECL_ca void Afxassert_validObject(const ::radix::object* pOb,
            const char * lpszFileName, int nLine);
CLASS_DECL_ca void Afxdump(const ::radix::object* pOb); // dump an object from CodeView


// extern _template::CTrace TRACE;
#ifdef _DEBUG
#define TRACE ATLTRACE
#define THIS_FILE          __FILE__
#define VERIFY(f)          ASSERT(f)
//#define DEBUG_ONLY(f)      (f)

// The following trace macros are provided for backward compatiblity
//  (they also take a fixed number of parameters which provides
//   some amount of extra error checking)
#define TRACE0(sz)              TRACE("%s", _T(sz))
#define TRACE1(sz, p1)          TRACE(_T(sz), p1)
#define TRACE2(sz, p1, p2)      TRACE(_T(sz), p1, p2)
#define TRACE3(sz, p1, p2, p3)  TRACE(_T(sz), p1, p2, p3)

// These AFX_dump macros also provided for backward compatibility
#define AFX_dump0(spgraphics, sz)   dumpcontext << _T(sz)
#define AFX_dump1(spgraphics, sz, p1) dumpcontext << _T(sz) << p1


#define DEBUG_ONLY(f)      (f)

#else

#define DEBUG_ONLY(f)      ((void)0)

#define VERIFY(f)          ((void)(f))
#define DEBUG_ONLY(f)      ((void)0)
#pragma warning(push)
#pragma warning(disable : 4793)
inline void AFX_CDECL AfxTrace(...) { }
#pragma warning(pop)
#define TRACE              __noop
#define TRACE0(sz)
#define TRACE1(sz, p1)
#define TRACE2(sz, p1, p2)
#define TRACE3(sz, p1, p2, p3)

#endif // !_DEBUG*/

#include "debug.h"


#ifdef _DEBUG

//#define ASSERT(f)          DEBUG_ONLY((void) ((f) || !::AfxAssertFailedLine(THIS_FILE, __LINE__) || (AfxDebugBreak(), 0)))
#define ASSERT(f)          ((void) ((f) || (is_debugger_attached() && (!::AfxAssertFailedLine(__FILE__, __LINE__) || (AfxDebugBreak(), 0))) || (!is_debugger_attached() && (throw assert_exception(__FILE__, __LINE__), 0))))
/* see _template headers for commentary on this */
/* We use the name AFXASSUME to avoid name clashes */
#define AFXASSUME(cond)       do { bool __afx_condVal=!!(cond); ASSERT(__afx_condVal); __analysis_assume(__afx_condVal); } while(0)
//#define ASSERT_VALID(pOb)  DEBUG_ONLY((::Afxassert_validObject(pOb, THIS_FILE, __LINE__)))
#define ASSERT_VALID(pOb)  ((::Afxassert_validObject(pOb, __FILE__, __LINE__)))
#else
#define ASSERT(f)
#define AFXASSUME(cond)
#define ASSERT_VALID(cond)
#endif

// Debug ASSERTs then throws. Retail throws if condition not met
#define ENSURE_THROW(cond, exception)   \
   do { int __afx_condVal=!!(cond); ASSERT(__afx_condVal); if (!(__afx_condVal)){exception;} } while (false)
#define ENSURE(cond)      ENSURE_THROW(cond, ::AfxThrowInvalidArgException() )
#define ENSURE_ARG(cond)   ENSURE_THROW(cond, ::AfxThrowInvalidArgException() )

// Debug ASSERT_VALIDs then throws. Retail throws if pOb is NULL
#define ENSURE_VALID_THROW(pOb, exception)   \
   do { ASSERT_VALID(pOb); if (!(pOb)){exception;} } while (false)
#define ENSURE_VALID(pOb)   ENSURE_VALID_THROW(pOb, ::AfxThrowInvalidArgException() )

#define ASSERT_POINTER(p, type) \
   ASSERT(((p) != NULL) && fx_is_valid_address((p), sizeof(type), FALSE))

#define ASSERT_NULL_OR_POINTER(p, type) \
   ASSERT(((p) == NULL) || fx_is_valid_address((p), sizeof(type), FALSE))

#ifdef _DEBUG
#define UNUSED(x)
#else
#define UNUSED(x) x
#endif
#define UNUSED_ALWAYS(x) x

#ifdef _DEBUG
#define REPORT_EXCEPTION(pException, szMsg) \
   do { \
      string str; \
      if (pException->GetErrorMessage(str, 0)) \
         TRACE(::radix::trace::category_AppMsg, 0, "%s (%s:%d)\n%s\n", szMsg, __FILE__, __LINE__, str); \
      else \
         TRACE(::radix::trace::category_AppMsg, 0, "%s (%s:%d)\n", szMsg, __FILE__, __LINE__); \
      ASSERT(FALSE); \
   } while (0)
#else
#define REPORT_EXCEPTION(pException, szMsg) \
   do { \
      string strMsg; \
      char  szErrorMessage[512]; \
      if (pException->GetErrorMessage(szErrorMessage, sizeof(szErrorMessage)/sizeof(*szErrorMessage), 0)) \
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

#define AFX_BEGIN_DESTRUCTOR try {
#define AFX_END_DESTRUCTOR   } catch (base_exception *pException) { EXCEPTION_IN_DTOR(pException); }
