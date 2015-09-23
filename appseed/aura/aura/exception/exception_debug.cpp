//#include "framework.h"


////////////////////////////////////////////////////////////////////////////////
// Global variables
//

   // Patch for SetUnhandledExceptionFilter
//const BYTE PatchBytes[5] = { 0x33, 0xC0, 0xC2, 0x04, 0x00 };

   // Original bytes at the beginning of SetUnhandledExceptionFilter
BYTE OriginalBytes[5] = {0};

BEGIN_EXTERN_C

CLASS_DECL_AURA int is_debugger_attached()
{
   
   return __node_is_debugger_attached() != FALSE;

}

END_EXTERN_C

CLASS_DECL_AURA int throw_assert_exception(const char * lpszFileName,int iLineNumber)
{

   throw assert_exception(::get_thread_app(),lpszFileName,iLineNumber);

}



assert_exception::assert_exception(const assert_exception & e) :
   object(e),
   ::call_stack(e),
   ::exception::base(e),
   simple_exception(e)
{
   
   debug_print(":assert(copy)");

}


assert_exception::assert_exception(::aura::application * papp, const char * pszFile, long lLine) :
   object(papp),
   ::call_stack(papp),
   ::exception::base(papp),
   simple_exception(papp)
{
   
#if defined(_LP64) || defined(VSNORD)
   
   if(pszFile == NULL)
   {
   
      debug_print(":assert(NULL, %ld)",lLine);
   
   }
   else
   {
   
      debug_print(":assert(\"%s\":%ld)",pszFile,lLine);
      
   }
   
#else
   
   if(pszFile == NULL)
   {
      
      debug_print(":assert(NULL, %d)",lLine);
      
   }
   else
   {
      
      debug_print(":assert(\"%s\":%d)",pszFile,lLine);
      
   }

#endif
   
   m_strFile = pszFile;
   
   m_lLine = lLine;
   
}


assert_exception::~assert_exception()
{
}

misc_exception::misc_exception(const misc_exception & e) :
   object(e),
   ::call_stack(e),
   ::exception::base(e),
   simple_exception(e),
   m_strMessage(e.m_strMessage)
{
   
   debug_print(":misc(copy)");

}


misc_exception::misc_exception(::aura::application * papp, const char * pszMessage) :
   object(papp),
   ::call_stack(papp),
   ::exception::base(papp),
   simple_exception(papp)
{

   if(pszMessage == NULL)
   {
   
      debug_print(":misc(NULL)");

   }
   else
   {
   
      debug_print(":misc(\"%s\")",pszMessage);
   
   }
      
   m_strMessage = pszMessage;
}

misc_exception::~misc_exception()
{
}

bool misc_exception::get_error_message(string & str, PUINT pnHelpContext)
{
   UNREFERENCED_PARAMETER(pnHelpContext);
   str = m_strMessage;
   return TRUE;
}






////////////////////////////////////////////////////////////////////////////////
// EnforceFilter function
//
/*
bool EnforceFilter( bool bEnforce )
{
   uint32_t ErrCode = 0;


   // Obtain the address of SetUnhandledExceptionFilter

   HMODULE hLib = GetModuleHandle( "kernel32.dll" );

   if( hLib == NULL )
   {
      ErrCode = GetLastError();
      _ASSERTE( !"GetModuleHandle(kernel32.dll) failed." );
      return false;
   }

   BYTE* pTarget = (BYTE*)GetProcAddress( hLib, "SetUnhandledExceptionFilter" );

   if( pTarget == 0 )
   {
      ErrCode = GetLastError();
      _ASSERTE( !"GetProcAddress(SetUnhandledExceptionFilter) failed." );
      return false;
   }

   if( IsBadReadPtr( pTarget, sizeof(OriginalBytes) ) )
   {
      _ASSERTE( !"Target is unreadable." );
      return false;
   }


   if( bEnforce )
   {
      // Save the original contents of SetUnhandledExceptionFilter

      memcpy( OriginalBytes, pTarget, sizeof(OriginalBytes) );


      // Patch SetUnhandledExceptionFilter

      if( !WriteMemory( pTarget, PatchBytes, sizeof(PatchBytes) ) )
         return false;

   }
   else
   {
      // Restore the original behavior of SetUnhandledExceptionFilter

      if( !WriteMemory( pTarget, OriginalBytes, sizeof(OriginalBytes) ) )
         return false;

   }


   // Success

   return true;

}


////////////////////////////////////////////////////////////////////////////////
// WriteMemory function
//

bool WriteMemory( BYTE* pTarget, const BYTE* pSource, uint32_t size )
{
   uint32_t ErrCode = 0;


   // Check parameters

   if( pTarget == 0 )
   {
      _ASSERTE( !"Target address is NULL." );
      return false;
   }

   if( pSource == 0 )
   {
      _ASSERTE( !"Source address is NULL." );
      return false;
   }

   if( size == 0 )
   {
      _ASSERTE( !"Source size is NULL." );
      return false;
   }

   if( IsBadReadPtr( pSource, size ) )
   {
      _ASSERTE( !"Source is unreadable." );
      return false;
   }


   // Modify protection attributes of the target memory page

   uint32_t OldProtect = 0;

   if( !VirtualProtect( pTarget, size, PAGE_EXECUTE_READWRITE, &OldProtect ) )
   {
      ErrCode = GetLastError();
      _ASSERTE( !"VirtualProtect() failed." );
      return false;
   }


   // write memory

   memcpy( pTarget, pSource, size );


   // Restore memory protection attributes of the target memory page

   uint32_t Temp = 0;

   if( !VirtualProtect( pTarget, size, OldProtect, &Temp ) )
   {
      ErrCode = GetLastError();
      _ASSERTE( !"VirtualProtect() failed." );
      return false;
   }


   // Success

   return true;

}

*/


namespace win
{


   CLASS_DECL_AURA string error_message(uint32_t dwError)
   {

      return get_system_error_message(dwError);

   }


} // namespace win


