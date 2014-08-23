#pragma once


// __is_valid_string() returns TRUE if the passed pointer
// references a string of at least the given length in characters.
// A length of -1 (the default parameter) means that the string
// buffer's minimum length isn't known, and the function will
// return TRUE no matter how long the string is. The primitive::memory
// used by the string can be read-only.

//bool __is_valid_string(const wchar_t * psz, int32_t nLength /* = -1 */)
//{
//   return __is_valid_string(psz, nLength);
//}
//
//// As above, but for ANSI strings.
//
///*bool __is_valid_string(const char * psz, int32_t nLength /* = -1 */)
//{
//   return __is_valid_string(psz, nLength);
//}*/
//
//// __is_valid_address() returns TRUE if the passed parameter points
//// to at least nBytes of accessible primitive::memory. If bReadWrite is TRUE,
//// the primitive::memory must be writeable; if bReadWrite is FALSE, the primitive::memory
//// may be const.
//
//bool __is_valid_address(const void * p, uint_ptr nBytes,
//   bool bReadWrite /* = TRUE */)
//{
//   return __is_valid_address(p, nBytes, bReadWrite);
//}


typedef int32_t HRes;

/////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
// Verify that a NULL-terminated string points to valid primitive::memory
inline bool __is_valid_string(const wchar_t * psz, size_t nMaxLength = INT_MAX)
{
#ifdef WINDOWS
   (nMaxLength);
#endif
   return (psz != NULL);
}

// Verify that a NULL-terminated string points to valid primitive::memory
inline bool __is_valid_string(const char * psz, size_t nMaxLength = UINT_MAX)
{
#ifdef WINDOWS
   (nMaxLength);
#endif
   return (psz != NULL);
}

// Verify that a pointer points to valid primitive::memory
inline bool __is_valid_address(const void * p, size_t nBytes, bool bReadWrite = TRUE)
{
#ifdef WINDOWS
   (bReadWrite);
   (nBytes);
#endif
   return (p != NULL);
}

/*template<typename T>
inline void __assert_valid_object(const T *pOb)
{
   ASSERT(pOb);
   ASSERT(__is_valid_address(pOb, sizeof(T)));
   if(pOb)
      pOb->assert_valid();
}*/
/*#ifdef DEBUG
#define ASSERT_VALID(x) __assert_valid_object(x)
#else
#define ASSERT_VALID(x) __noop;
#endif*/

// COM Sync Classes
/*class CComCriticalSection
{
public:
CComCriticalSection() throw()
{
memset(&m_sec, 0, sizeof(CRITICAL_SECTION));
}
~CComCriticalSection()
{
}
HRESULT lock() throw()
{
EnterCriticalSection(&m_sec);
return S_OK;
}
HRESULT unlock() throw()
{
LeaveCriticalSection(&m_sec);
return S_OK;
}
HRESULT Init() throw()
{
HRESULT hRes = E_FAIL;
__try
{
InitializeCriticalSection(&m_sec);
hRes = S_OK;
}
// structured exception may be raised in low primitive::memory situations
__except(STATUS_NO_MEMORY == GetExceptionCode())
{
hRes = E_OUTOFMEMORY;
}
return hRes;
}

HRESULT Term() throw()
{
DeleteCriticalSection(&m_sec);
return S_OK;
}
CRITICAL_SECTION m_sec;
};

class CComAutoCriticalSection : public CComCriticalSection
{
public:
CComAutoCriticalSection()
{
HRESULT hr = CComCriticalSection::Init();
if (FAILED(hr))
throw hresult_exception(hr);
}
~CComAutoCriticalSection() throw()
{
CComCriticalSection::Term();
}
private :
HRESULT Init(); // Not implemented. CComAutoCriticalSection::Init should never be called
HRESULT Term(); // Not implemented. CComAutoCriticalSection::Term should never be called
};

class CComSafeDeleteCriticalSection : public CComCriticalSection
{
public:
CComSafeDeleteCriticalSection(): m_bInitialized(false)
{
}

~CComSafeDeleteCriticalSection() throw()
{
if (!m_bInitialized)
{
return;
}
m_bInitialized = false;
CComCriticalSection::Term();
}

HRESULT Init() throw()
{
ASSERT( !m_bInitialized );
HRESULT hr = CComCriticalSection::Init();
if (SUCCEEDED(hr))
{
m_bInitialized = true;
}
return hr;
}

HRESULT Term() throw()
{
if (!m_bInitialized)
{
return S_OK;
}
m_bInitialized = false;
return CComCriticalSection::Term();
}

HRESULT lock()
{
// CComSafeDeleteCriticalSection::Init or CComAutoDeleteCriticalSection::Init
// not called or failed.
// m_critsec member of CComObjectRootEx is now of type
// CComAutoDeleteCriticalSection. It has to be initialized
// by calling CComObjectRootEx::_gen_InitialConstruct
ASSUME(m_bInitialized);
return CComCriticalSection::lock();
}

private:
bool m_bInitialized;
};

class CComAutoDeleteCriticalSection : public CComSafeDeleteCriticalSection
{
private:
// CComAutoDeleteCriticalSection::Term should never be called
HRESULT Term() throw();
};

class CComFakeCriticalSection
{
public:
HRESULT lock() throw() { return S_OK; }
HRESULT unlock() throw() { return S_OK; }
HRESULT Init() throw() { return S_OK; }
HRESULT Term() throw() { return S_OK; }
};
*/






/*template <typename _CharType>
inline _CharType* gen_CharNext(const _CharType* p) throw()
{
ASSUME(p != NULL);   // Too expensive to check separately here
if (*p == '\0')  // ::CharNextA won't increment if we're at a \0 already
return const_cast<_CharType*>(p+1);
else
return ::CharNextA(p);
}

template <>
inline wchar_t* gen_CharNext<wchar_t>(const wchar_t* p) throw()
{
return const_cast< wchar_t* >( p+1 );
}
template<typename CharType>
inline const CharType* gen_strchrT(const CharType* p, CharType ch) throw()
{
ASSERT(p != NULL);
if(p==NULL)
{
return NULL;
}
while( *p != 0 )
{
if (*p == ch)
{
return p;
}
p = gen_CharNext(p);
}
//strchr for '\0' should succeed - the while loop terminates
// *p == 0, but ch also == 0, so NULL terminator address is returned
return (*p == ch) ? p : NULL;
}
//Ansi and Unicode versions of printf, used with templated CharType trait classes.
#pragma warning(push)
#pragma warning(disable : 4793)
template<typename CharType>
inline int32_t gen_printfT(const CharType* pszFormat,... ) throw()
{
int32_t retval=0;
va_list argList;
va_start( argList, pszFormat );
retval=vprintf(pszFormat,argList);
va_end( argList );
return retval;
}
#pragma warning(pop)

#pragma warning(push)
#pragma warning(disable : 4793)
template<>
inline int32_t gen_printfT(const wchar_t* pszFormat,... ) throw()
{
int32_t retval=0;
va_list argList;
va_start( argList, pszFormat );
retval=vwprintf(pszFormat,   argList);
va_end( argList );
return retval;
}
#pragma warning(pop)

inline bool gen_ConvertSystemTimeToVariantTime(const SYSTEMTIME& systimeSrc,double* pVarDtTm)
{
ENSURE(pVarDtTm!=NULL);
//Convert using ::SystemTimeToVariantTime and store the result in pVarDtTm then
//convert variant time back to system time and compare to original system time.
bool ok = ::SystemTimeToVariantTime(const_cast<SYSTEMTIME*>(&systimeSrc), pVarDtTm);
SYSTEMTIME sysTime;
::ZeroMemory(&sysTime, sizeof(SYSTEMTIME));

ok = ok && ::VariantTimeToSystemTime(*pVarDtTm, &sysTime);
ok = ok && (systimeSrc.wYear == sysTime.wYear &&
systimeSrc.wMonth == sysTime.wMonth &&
systimeSrc.wDay == sysTime.wDay &&
systimeSrc.wHour == sysTime.wHour &&
systimeSrc.wMinute == sysTime.wMinute &&
systimeSrc.wSecond == sysTime.wSecond);

return ok;
}*/
