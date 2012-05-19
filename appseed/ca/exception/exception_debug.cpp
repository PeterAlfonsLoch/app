#include "framework.h"


////////////////////////////////////////////////////////////////////////////////
// Global variables
//

   // Patch for SetUnhandledExceptionFilter
const BYTE PatchBytes[5] = { 0x33, 0xC0, 0xC2, 0x04, 0x00 };

   // Original bytes at the beginning of SetUnhandledExceptionFilter
BYTE OriginalBytes[5] = {0};



bool is_debugger_attached()
{
#ifdef WINDOWS
   return ::IsDebuggerPresent() != FALSE;
#else
   return ::is_gdb_present();
#endif
/*    DWORD dw;

    __asm
    {
        push eax    // Preserve the registers

        push ecx
        mov eax, fs:[0x18]  // get the TIB's linear address

        mov eax, dword ptr [eax + 0x30]
        mov ecx, dword ptr [eax]    // get the whole DWORD

        mov dw, ecx // Save it

        pop ecx // Restore the registers

        pop eax
    }


    // The 3rd byte is the byte we really need to check for the

    // presence of a debugger.

    // Check the 3rd byte

    return ((dw & 0x00010000) != 0) ? true : false;*/
}



assert_exception::assert_exception(const assert_exception & e) :
   simple_exception(e)
{
}

assert_exception::assert_exception(const char * pszFile, long lLine)
{
   m_strFile = pszFile;
   m_lLine = lLine;
}

assert_exception::~assert_exception()
{
}

misc_exception::misc_exception(const misc_exception & e) :
   simple_exception(e),
   m_strMessage(e.m_strMessage)
{
}

misc_exception::misc_exception(const char * pszMessage)
{
   m_strMessage = pszMessage;
}

misc_exception::~misc_exception()
{
}

bool misc_exception::GetErrorMessage(string & str, PUINT pnHelpContext)
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
   DWORD ErrCode = 0;


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

bool WriteMemory( BYTE* pTarget, const BYTE* pSource, DWORD size )
{
   DWORD ErrCode = 0;


   // Check parameters

   if( pTarget == 0 )
   {
      _ASSERTE( !"Target address is null." );
      return false;
   }

   if( pSource == 0 )
   {
      _ASSERTE( !"Source address is null." );
      return false;
   }

   if( size == 0 )
   {
      _ASSERTE( !"Source size is null." );
      return false;
   }

   if( IsBadReadPtr( pSource, size ) )
   {
      _ASSERTE( !"Source is unreadable." );
      return false;
   }


   // Modify protection attributes of the target primitive::memory page

   DWORD OldProtect = 0;

   if( !VirtualProtect( pTarget, size, PAGE_EXECUTE_READWRITE, &OldProtect ) )
   {
      ErrCode = GetLastError();
      _ASSERTE( !"VirtualProtect() failed." );
      return false;
   }


   // write primitive::memory

   memcpy( pTarget, pSource, size );


   // Restore primitive::memory protection attributes of the target primitive::memory page

   DWORD Temp = 0;

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


   CLASS_DECL_ca string error_message(DWORD dwError)
   {

      string str;

#ifdef WINDOWS

      wchar_t * lpBuffer;
      FormatMessageW(
         FORMAT_MESSAGE_ALLOCATE_BUFFER |
         FORMAT_MESSAGE_FROM_SYSTEM,
         NULL,
         dwError,
         0,
         (wchar_t *) &lpBuffer,
         1,
         NULL);

      str = gen::international::unicode_to_utf8(lpBuffer);
      LocalFree(lpBuffer);
#endif

      return str;

   }


} // namespace win


