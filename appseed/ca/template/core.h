#pragma once


#include "definition.h"


#include "checked.h"
#include "simple_collection.h"

namespace _template
{
   /////////////////////////////////////////////////////////////////////////////
   // Verify that a null-terminated string points to valid primitive::memory
   inline BOOL _template_is_valid_string(const wchar_t * psz, size_t nMaxLength = INT_MAX)
   {
#ifdef WINDOWS
      (nMaxLength);
#endif
      return (psz != NULL);
   }

   // Verify that a null-terminated string points to valid primitive::memory
   inline BOOL _template_is_valid_string(const char * psz, size_t nMaxLength = UINT_MAX)
   {
#ifdef WINDOWS
      (nMaxLength);
#endif
      return (psz != NULL);
   }

   // Verify that a pointer points to valid primitive::memory
   inline BOOL _template_is_valid_address(const void * p, size_t nBytes,
      BOOL bReadWrite = TRUE)
   {
#ifdef WINDOWS
      (bReadWrite);
      (nBytes);
#endif
      return (p != NULL);
   }

   template<typename T>
   inline void _template_assert_valid_object(const T *pOb)
   {
      ATLASSERT(pOb);
      ATLASSERT(_template_is_valid_address(pOb, sizeof(T)));
      if(pOb)
         pOb->assert_valid();
   }
   #ifdef _DEBUG
   #define ATLASSERT_VALID(x) _template::_template_assert_valid_object(x)
   #else
   #define ATLASSERT_VALID(x) __noop;
   #endif

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
            AtlThrow(hr);
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
         ATLASSERT( !m_bInitialized );
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
         // by calling CComObjectRootEx::_AtlInitialConstruct
         ATLASSUME(m_bInitialized);
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
   inline _CharType* AtlCharNext(const _CharType* p) throw()
   {
      ATLASSUME(p != NULL);   // Too expensive to check separately here
      if (*p == '\0')  // ::CharNextA won't increment if we're at a \0 already
         return const_cast<_CharType*>(p+1);
      else
         return ::CharNextA(p);
   }

   template <>
   inline wchar_t* AtlCharNext<wchar_t>(const wchar_t* p) throw()
   {
      return const_cast< wchar_t* >( p+1 );
   }
   template<typename CharType>
   inline const CharType* AtlstrchrT(const CharType* p, CharType ch) throw()
   {
      ATLASSERT(p != NULL);
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
         p = AtlCharNext(p);
      }
      //strchr for '\0' should succeed - the while loop terminates
      // *p == 0, but ch also == 0, so NULL terminator address is returned
      return (*p == ch) ? p : NULL;
   }
   //Ansi and Unicode versions of printf, used with templated CharType trait classes.
   #pragma warning(push)
   #pragma warning(disable : 4793)
   template<typename CharType>
   inline int AtlprintfT(const CharType* pszFormat,... ) throw()
   {
      int retval=0;
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
   inline int AtlprintfT(const wchar_t* pszFormat,... ) throw()
   {
      int retval=0;
      va_list argList;
      va_start( argList, pszFormat );
      retval=vwprintf(pszFormat,   argList);
      va_end( argList );
      return retval;
   }
   #pragma warning(pop)

   inline BOOL AtlConvertSystemTimeToVariantTime(const SYSTEMTIME& systimeSrc,double* pVarDtTm)
   {
      ATLENSURE(pVarDtTm!=NULL);
      //Convert using ::SystemTimeToVariantTime and store the result in pVarDtTm then
      //convert variant time back to system time and compare to original system time.
      BOOL ok = ::SystemTimeToVariantTime(const_cast<SYSTEMTIME*>(&systimeSrc), pVarDtTm);
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

}   // namespace _template
