#pragma once

#include "definition.h"
#include "exception/exception_0.h"


#pragma once


namespace _template
{

   CLASS_DECL_ca void DECLSPEC_NO_RETURN atl_raise_exception(DWORD dwExceptionCode, DWORD dwExceptionFlags = EXCEPTION_NONCONTINUABLE);

   class CLASS_DECL_ca atl_exception
   {
   public:
      

      HRESULT m_hr;


      atl_exception() throw();
      atl_exception( HRESULT hr ) throw();


      operator HRESULT() const throw();


   };

   CLASS_DECL_ca void WINAPI atl_throw_impl( HRESULT hr );

   // Throw a atl_exception corresponding to the result of ::GetLastError
   CLASS_DECL_ca DECLSPEC_NO_RETURN void WINAPI AtlThrowLastWin32();

}  // namespace _template
