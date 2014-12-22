#include "framework.h"
#include "linux.h"


/////////////////////////////////////////////////////////////////////////////
// __EXCEPTION_CONTEXT (thread global state)

__EXCEPTION_CONTEXT* __get_exception_context()
{

   return NULL;

}

/////////////////////////////////////////////////////////////////////////////
// __exception_link linked 'jmpbuf' and out-of-line helpers

__exception_link::__exception_link()
{
}


// out-of-line cleanup called from inline __exception_link destructor
CLASS_DECL_AXIS void __try_cleanup()
{
}

// special out-of-line implementation of THROW_LAST (for auto-delete behavior)
void CLASS_DECL_AXIS __throw_last_cleanup()
{
}






namespace gen
{

#if defined( _CUSTOM_THROW )  // You can define your own throw hresult_exception to throw a custom exception.

CLASS_DECL_AXIS void WINAPI atl_throw_impl( HRESULT hr )
{
   TRACE(atlTraceException, 0, "throw hresult_exception: hr = 0x%x\n", hr );
#ifdef _AFX
   if( hr == E_OUTOFMEMORY )
   {
      throw memory_exception();
   }
   else
   {
//      ::ca2::ThrowOleException( hr );
   }
#else
   throw atl_exception( hr );
#endif
};

#endif


// Throw a atl_exception with th given HRESULT
#if !defined( _CUSTOM_THROW )  // You can define your own throw hresult_exception

//CLASS_DECL_AXIS void WINAPI atl_throw_impl(HRESULT hr)
//{
//   TRACE("throw hresult_exception: hr = 0x%x\n", hr);
 //  throw hresult_exception(hr);
/*   ::OutputDebugString("throw hresult_exception");
   char sz[200];
   sprintf(sz, "0x%s", hr);
   ::OutputDebugString(sz);
   ::OutputDebugString("\n");
   //TRACE(trace::category_Exception, 0, "throw hresult_exception: hr = 0x%x\n", hr );
   ASSERT( false );
   DWORD dwExceptionCode;
   switch(hr)
   {
   case E_OUTOFMEMORY:
      dwExceptionCode = STATUS_NO_MEMORY;
      break;
   default:
      dwExceptionCode = EXCEPTION_ILLEGAL_INSTRUCTION;
   }
   atl_raise_exception((DWORD)dwExceptionCode);*/
//}
#endif


} // namespace gen
