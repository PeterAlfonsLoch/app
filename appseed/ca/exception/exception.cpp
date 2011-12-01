#include "StdAfx.h"

namespace ca
{
   
//   exception::~exception()
  // {
   //}

} // namespace ca

namespace _template
{

#if defined( _ATL_CUSTOM_THROW )  // You can define your own AtlThrow to throw a custom exception.

CLASS_DECL_ca void WINAPI atl_throw_impl( HRESULT hr )
{
   ATLTRACE(atlTraceException, 0, "AtlThrow: hr = 0x%x\n", hr );
#ifdef _AFX
   if( hr == E_OUTOFMEMORY )
   {
      AfxThrowMemoryException();
   }
   else
   {
//      AfxThrowOleException( hr );
   }
#else
   throw atl_exception( hr );
#endif
};

#endif


// Throw a atl_exception with th given HRESULT
#if !defined( _ATL_CUSTOM_THROW )  // You can define your own AtlThrow

CLASS_DECL_ca void WINAPI atl_throw_impl(HRESULT hr)
{
//   TRACE("AtlThrow: hr = 0x%x\n", hr);
   throw hresult_exception(hr);
/*   ::OutputDebugString("AtlThrow");
   char sz[200];
   sprintf(sz, "0x%s", hr);
   ::OutputDebugString(sz);
   ::OutputDebugString("\n");
   //ATLTRACE(trace::category_Exception, 0, "AtlThrow: hr = 0x%x\n", hr );
   ATLASSERT( false );
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
}
#endif


} // namespace _template


// exception support
 resource_exception::resource_exception()
   : simple_exception() { }
 resource_exception::resource_exception(BOOL bAutoDelete, UINT nResourceID)
   : simple_exception(bAutoDelete) { m_nResourceID = nResourceID; }
 resource_exception::~resource_exception()
   { }


  user_exception::user_exception()
   : simple_exception() { }
 user_exception::user_exception(BOOL bAutoDelete, UINT nResourceID)
   : simple_exception(bAutoDelete) { m_nResourceID = nResourceID; }
 user_exception::~user_exception()
   { }



