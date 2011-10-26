#include "StdAfx.h"


namespace _template
{

   void DECLSPEC_NO_RETURN atl_raise_exception( DWORD dwExceptionCode, DWORD dwExceptionFlags)
   {
      RaiseException( dwExceptionCode, dwExceptionFlags, 0, NULL );
   }

   atl_exception::atl_exception() throw() :
      m_hr( E_FAIL )
   {
   }

   atl_exception::atl_exception( HRESULT hr ) throw() :
      m_hr( hr )
   {
   }

   atl_exception::operator HRESULT() const throw()
   {
      return( m_hr );
   }



   DECLSPEC_NO_RETURN void WINAPI AtlThrowLastWin32()
   {
      DWORD dwError = ::GetLastError();
      AtlThrow( HRESULT_FROM_WIN32( dwError ) );
   }


}  // namespace _template
