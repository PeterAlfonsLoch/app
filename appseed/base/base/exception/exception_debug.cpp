#include "framework.h"


////////////////////////////////////////////////////////////////////////////////
// Global variables
//

   // Patch for SetUnhandledExceptionFilter
//const BYTE PatchBytes[5] = { 0x33, 0xC0, 0xC2, 0x04, 0x00 };

   // Original bytes at the beginning of SetUnhandledExceptionFilter
BYTE OriginalBytes[5] = {0};



bool is_debugger_attached()
{

#ifdef WINDOWS

   
   return ::IsDebuggerPresent() != FALSE;

   
#elif defined(LINUX)
   
    
   return ::is_gdb_present();
   

#elif defined(APPLEOS)
   
   
   return ::AmIBeingDebugged();
   
   
#elif defined(ANDROID)
   
   
   return false;
   
   
#else
   
   
   throw not_implemented(get_app());
   
   
#endif
/*    uint32_t dw;

    __asm
    {
        push eax    // Preserve the registers

        push ecx
        mov eax, fs:[0x18]  // get the TIB's linear address

        mov eax, dword ptr [eax + 0x30]
        mov ecx, dword ptr [eax]    // get the whole uint32_t

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
   element(e),
   ::call_stack(e),
   ::exception::base(e),
   simple_exception(e)
{
}

assert_exception::assert_exception(sp(base_application) papp, const char * pszFile, long lLine) :
   element(papp),
   ::call_stack(papp),
   ::exception::base(papp),
   simple_exception(papp)
{
   m_strFile = pszFile;
   m_lLine = lLine;
}

assert_exception::~assert_exception()
{
}

misc_exception::misc_exception(const misc_exception & e) :
   element(e),
   ::call_stack(e),
   ::exception::base(e),
   simple_exception(e),
   m_strMessage(e.m_strMessage)
{
}

misc_exception::misc_exception(sp(base_application) papp, const char * pszMessage) :
   element(papp),
   ::call_stack(papp),
   ::exception::base(papp),
   simple_exception(papp)
{
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


   // Modify protection attributes of the target primitive::memory page

   uint32_t OldProtect = 0;

   if( !VirtualProtect( pTarget, size, PAGE_EXECUTE_READWRITE, &OldProtect ) )
   {
      ErrCode = GetLastError();
      _ASSERTE( !"VirtualProtect() failed." );
      return false;
   }


   // write primitive::memory

   memcpy( pTarget, pSource, size );


   // Restore primitive::memory protection attributes of the target primitive::memory page

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


   CLASS_DECL_BASE string error_message(uint32_t dwError)
   {

      return get_system_error_message(dwError);

   }


} // namespace win


