#pragma once

#include "definition.h"
#include "exception/exception_0.h"


namespace _template
{

   /////////////////////////////////////////////////////////////////////////////
   // Exception raise (for functions that cannot return an error code)

   inline void __declspec(noreturn) _AtlRaiseException( DWORD dwExceptionCode, DWORD dwExceptionFlags = EXCEPTION_NONCONTINUABLE )
   {
      RaiseException( dwExceptionCode, dwExceptionFlags, 0, NULL );
   }

   class CAtlException
   {
   public:
      CAtlException() throw() :
         m_hr( E_FAIL )
      {
      }

      CAtlException( HRESULT hr ) throw() :
         m_hr( hr )
      {
      }

      operator HRESULT() const throw()
      {
         return( m_hr );
      }

   public:
      HRESULT m_hr;
   };

   #ifndef _ATL_NO_EXCEPTIONS

   // Throw a CAtlException with the given HRESULT
   #if defined( _ATL_CUSTOM_THROW )  // You can define your own AtlThrow to throw a custom exception.
   #ifdef _AFX
   #error ca2 API projects must use default implementation of AtlThrow()
   #endif
   #else
   CLASS_DECL_ca void WINAPI AtlThrowImpl( HRESULT hr );
   #endif

   // Throw a CAtlException corresponding to the result of ::GetLastError
   ATL_NOINLINE __declspec(noreturn) inline void WINAPI AtlThrowLastWin32()
   {
      DWORD dwError = ::GetLastError();
      AtlThrow( HRESULT_FROM_WIN32( dwError ) );
   }

   #else  // no exception handling

   // Throw a CAtlException with th given HRESULT
   #if !defined( _ATL_CUSTOM_THROW )  // You can define your own AtlThrow

   CLASS_DECL_ca2 inline void WINAPI AtlThrowImpl( HRESULT hr );
   #endif

   // Throw a CAtlException corresponding to the result of ::GetLastError
   ATL_NOINLINE inline void WINAPI AtlThrowLastWin32()
   {
      DWORD dwError = ::GetLastError();
      AtlThrow( HRESULT_FROM_WIN32( dwError ) );
   }

   #endif  // no exception handling

}  // namespace _template
