#include "framework.h"
#include "aura/node/ansios/ansios.h"
#include "linux.h"


#ifdef IMPLEMENT_VISTA_TOOLS

#define ASSERT_HERE ASSERT(FALSE)

/*#if ( NTDDI_VERSION < NTDDI_LONGHORN )
#   error NTDDI_VERSION must be defined as NTDDI_LONGHORN or later
#endif*/

//////////////////////////////////////////////////////////////////
// if ASSERT was not defined already, let's define our own version,
// to use the CRT assert()

/*#ifndef ASSERT
#   ifdef DEBUG
#      include <assert.h>
#      define ASSERT(x) assert( x )
#      define ASSERT_HERE assert( FALSE )
#   else// DEBUG
#      define ASSERT(x)
#      define ASSERT_HERE
#   endif//DEBUG
#endif//ASSERT*/

///////////////////////////////////////////////////////////////////
// a handy macro to get the number of characters (not bytes!)
// a string buffer can hold

#ifndef _tsizeof
#   define _tsizeof( s )  (sizeof(s)/sizeof(s[0]))
#endif//_tsizeof



namespace VistaTools
{

///////////////////////////////////////////////////////////////

// macros to handle the functions implemented in a DLL properly

//////////////////////////////////////////////////////////
// MyShellExec is just a wrapper around a call to ShellExecuteEx,
// to be able to specify the verb easily.

WINBOOL
MyShellExec(   HWND hwnd,
            const char * pszVerb,
            const char * pszPath,
            const char * pszParameters,   // = NULL
            const char * pszDirectory,   // = NULL
            HANDLE * phProcess )   // = NULL
{
   SHELLEXECUTEINFO shex;

   memset( &shex, 0, sizeof( shex) );

   shex.cbSize         = sizeof( SHELLEXECUTEINFO );
   shex.fMask         = (phProcess ? SEE_MASK_NOCLOSEPROCESS : 0);
   shex.hwnd         = hwnd;
   shex.lpVerb         = pszVerb;
   shex.lpFile         = pszPath;
   shex.lpParameters   = pszParameters;
   shex.lpDirectory   = pszDirectory;
   shex.nShow         = SW_NORMAL;

   WINBOOL bRet = ::ShellExecuteEx( &shex );

   if ( phProcess )
      *phProcess = shex.hProcess;

   return bRet;
}

WINBOOL IsVista()
{
   OSVERSIONINFO osver;

   osver.dwOSVersionInfoSize = sizeof( OSVERSIONINFO );

   if (   ::GetVersionEx( &osver ) &&
         osver.dwPlatformId == VER_PLATFORM_WIN32_NT &&
         (osver.dwMajorVersion >= 6 ) )
      return TRUE;

   return FALSE;
}

#ifndef WIN64 // we need this when compiling 32-bit code only

typedef WINBOOL (WINAPI *LPFN_ISWOW64PROCESS) (HANDLE hProcess,PBOOL Wow64Process);

LPFN_ISWOW64PROCESS fnIsWow64Process =
   (LPFN_ISWOW64PROCESS)::GetProcAddress( ::GetModuleHandle("kernel32"),"IsWow64Process");

WINBOOL
IsWow64()
{
    WINBOOL bIsWow64 = FALSE;

    if (NULL != fnIsWow64Process)
    {
      if ( !fnIsWow64Process( ::GetCurrentProcess(),&bIsWow64) )
        {
            ASSERT_HERE;
        }
    }

    return bIsWow64;
}

#endif//WIN64

HRESULT
GetElevationType( __out TOKEN_ELEVATION_TYPE * ptet )
{
   if ( !IsVista() )
      return E_FAIL;

   ASSERT( ptet );

   HRESULT hResult = E_FAIL; // assume an error occurred
   HANDLE hToken   = NULL;

   if ( !::OpenProcessToken(
            ::GetCurrentProcess(),
            TOKEN_QUERY,
            &hToken ) )
   {
      ASSERT_HERE;
      return hResult;
   }

   DWORD dwReturnLength = 0;

   if ( !::GetTokenInformation(
            hToken,
            TokenElevationType,
            ptet,
            sizeof( *ptet ),
            &dwReturnLength ) )
   {
      ASSERT_HERE;
   }
   else
   {
      ASSERT( dwReturnLength == sizeof( *ptet ) );
      hResult = S_OK;
   }

   ::CloseHandle( hToken );

   return hResult;
}

HRESULT
IsElevated( __out_opt WINBOOL * pbElevated ) //= NULL )
{
   if ( !IsVista() )
      return E_FAIL;

   HRESULT hResult = E_FAIL; // assume an error occurred
   HANDLE hToken   = NULL;

   if ( !::OpenProcessToken(
            ::GetCurrentProcess(),
            TOKEN_QUERY,
            &hToken ) )
   {
      ASSERT_HERE;
      return hResult;
   }

   TOKEN_ELEVATION te = { 0 };
   DWORD dwReturnLength = 0;

   if ( !::GetTokenInformation(
            hToken,
            TokenElevation,
            &te,
            sizeof( te ),
            &dwReturnLength ) )
   {
      ASSERT_HERE;
   }
   else
   {
      ASSERT( dwReturnLength == sizeof( te ) );

      hResult = te.TokenIsElevated ? S_OK : S_FALSE;

      if ( pbElevated)
         *pbElevated = (te.TokenIsElevated != 0);
   }

   ::CloseHandle( hToken );

   return hResult;
}

////////////////////////////////
// RunElevated simply calls ShellExecuteEx with the verb "runas" to start the elevated process.
// I wish there was a just as easy way to start a non-elevated process, as well.

WINBOOL
RunElevated(
   __in      HWND   hwnd,
   __in      const char * pszPath,
   __in_opt   const char * pszParameters,   //   = NULL,
   __in_opt   const char * pszDirectory,   //   = NULL,
   __out_opt   HANDLE *phProcess )      //   = NULL );
{
   return MyShellExec(
            hwnd,
            IsVista() ? "runas" : NULL,
            pszPath,
            pszParameters,
            pszDirectory,
            phProcess );
}

#ifndef DONTWANT_RunNonElevated
///////////////////////////////////////
// RunNonElevated() implementation

///////////////////////////////////////////////////
//   The shared data, to be able to share
//   data between ours and the shell proceses

#pragma section( "ve_shared", read, write, shared )

__declspec(allocate("ve_shared"))
   HHOOK   hVEHook                     = NULL;

__declspec(allocate("ve_shared"))
   UINT   uVEMsg                     = 0;

__declspec(allocate("ve_shared"))
   WINBOOL   bVESuccess                  = FALSE;

__declspec(allocate("ve_shared"))
   char   szVE_Path[ MAX_PATH ]         = "";

__declspec(allocate("ve_shared"))
   char   szVE_Parameters[ MAX_PATH ]      = "";

__declspec(allocate("ve_shared"))
   char   szVE_Directory[ MAX_PATH ]      = "";

__declspec(allocate("ve_shared"))
   WINBOOL    bVE_NeedProcessHandle         = FALSE;

__declspec(allocate("ve_shared"))
   HANDLE   hVE_Process               = NULL;

//////////////////////////////////e
// the hook callback procedure, it is called in the context of th shell proces

LRESULT CALLBACK
VistaEelevator_HookProc_MsgRet( int code, WPARAM wParam, LPARAM lParam )
{
    if ( code >= 0 && lParam )
    {
       CWPRETSTRUCT * pwrs = (CWPRETSTRUCT *)lParam;

        if (pwrs->message == uVEMsg )
      {
         bVESuccess = VistaTools::MyShellExec(
                     pwrs->hwnd,
                     NULL,
                     szVE_Path,
                     szVE_Parameters,
                     szVE_Directory,
                     bVE_NeedProcessHandle ? &hVE_Process : NULL );
      }
    }

   return ::CallNextHookEx( hVEHook, code, wParam, lParam );
}

////////////////////////////////////////////////////////////
// The code below needs to call GetModuleHandleEx,
// but it is available on Windows XP and Vista only.
// To make the code run under Windows 2000 as well, we will
// link to GetModuleHandleEx dynamically:

typedef
WINBASEAPI
WINBOOL
(WINAPI
*PGetModuleHandleExW)(
    __in        DWORD    dwFlags,
    __in_opt    const unichar * lpModuleName,
    __out HMODULE* phModule
    );

static PGetModuleHandleExW pGetModuleHandleExW = NULL;

WINBOOL
RunNonElevated(
   __in      HWND   hwnd,
   __in      const char * pszPath,
   __in_opt   const char * pszParameters,   //   = NULL,
   __in_opt   const char * pszDirectory,   //   = NULL,
   __out_opt   HANDLE *phProcess)      //   = NULL );
{
   ASSERT( pszPath && *pszPath );   // other args are optional

   ASSERT( pszPath );

   // Determine whether we can use the regular ShellExecuteEx
   // We can use it if we are not running Vista, or if this process is already non-elevated,
   // or if the current ::fontopus::user account has no "split" token (and therefore has no distinction
   // between the elevated and non-elevated proceses

   TOKEN_ELEVATION_TYPE tet;

   if (   !IsVista() ||
         FAILED( GetElevationType( &tet ) ) ||
         tet != TokenElevationTypeFull )
   {
      // if the current process is not elevated, we can use ShellExecuteEx directly!

      return MyShellExec( hwnd,
                     NULL,
                     pszPath,
                     pszParameters,
                     pszDirectory,
                     phProcess );
   }

   #ifndef WIN64

   // If 32-bit code is executing under x64 version of Windows, it will not work, because
   // the shell is a 64-bit process, and to hook it successfully this code needs to be 64-bit as well

   if ( IsWow64() )
   {
      ASSERT_HERE;
      return FALSE;
   }

   #endif//WIN64


   //////////////////////////////////////////////
   //
   // How this code works:
   //
   // To start a non-elevated process, we need to inject our code into a non-elevated
   // process already running on the target computer. Since Windows shell is non-elevated,
   // and we can safely assume it to always run, (when was the last time you saw Windows
   // running without its shell?), we will try to inject our code into the shell process.
   //
   // To inject the code, we will install a global hook, and send a message to
   // a ::ca::user::interaction_impl created by the shell. This will cause our hook callback procedure to be executed
   // in the context of the shell proces.
   //
   // Because this trick uses a global hook, the hook procedure must be in a DLL.
   //

   /////////////////////
   // First, register a private message, to communicate with the (hooked) shell process

   if ( !uVEMsg )
      uVEMsg = ::RegisterWindowMessage( "VistaElevatorMsg" );

   //////////////////////////////////////
   // find the shell ::ca::user::interaction_impl (the desktop)

   HWND hwndShell = ::FindWindow( "Progman", NULL);

   if ( !hwndShell )
   {
      ASSERT_HERE;
      return FALSE;
   }

   if ( !hwnd )
      hwnd = ::GetForegroundWindow();

   // Link (dynamically) to the GetModuleHandleExW API:

   if ( !pGetModuleHandleExW )
   {
      pGetModuleHandleExW = (PGetModuleHandleExW)::GetProcAddress(
         ::GetModuleHandle( "Kernel32" ), "GetModuleHandleExW" );
   }

   if ( !pGetModuleHandleExW )
   {
      ASSERT_HERE;
      return FALSE;
   }

   HMODULE hModule = NULL;   // we need to know hModule of this DLL to install a global hook

   if ( !pGetModuleHandleExW(
            GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
            (const unichar *)VistaEelevator_HookProc_MsgRet,
            &hModule ) )
   {
      ASSERT_HERE;
      return FALSE;
   }

   /////////////////////////////////////////
   // Install a global hook, to inject our code into the shell proces

    hVEHook = ::SetWindowsHookEx( WH_CALLWNDPROCRET,   // hook called after SendMessage() !!!
                (HOOKPROC)VistaEelevator_HookProc_MsgRet, hModule, 0);

   if ( !hVEHook )
   {
      ASSERT_HERE;
      return FALSE;
   }

   //////////////////////////////////
   // Prepare the parameters for launching the non-elevated process
   // from the hook callback procedure (they are placed into the shared data section)

    if (!( strncpy(
               szVE_Path,
               pszPath, _tsizeof(szVE_Path) ) ) )
   {
      ASSERT_HERE;
      return FALSE;
   }

    if (!( strncpy(
               szVE_Parameters,

               pszParameters ? pszParameters : "" ,
               _tsizeof(szVE_Parameters)) ) )
   {
      ASSERT_HERE;
      return FALSE;
   }

    if ( FAILED( strncpy(
               szVE_Directory,
               pszDirectory ? pszDirectory : "",
               _tsizeof(szVE_Directory)) ) )
   {
      ASSERT_HERE;
      return FALSE;
   }

   bVE_NeedProcessHandle = (phProcess != NULL);

   /////////////////////////////////////////
   // Activate our hook callback procedure:

   bVESuccess = FALSE; // assume failure

   ::SendMessage( hwndShell, uVEMsg, 0, 0 );

   ////////////////////////////////////////////////////////
   // At this point our hook procedure has been executed!

   if ( phProcess )
      *phProcess = hVE_Process;

   /////////////////////////////////////
   // The hook is no longer needed, remov it:

   ::UnhookWindowsHookEx( hVEHook );
   hVEHook = NULL;

   //////////////////////
   // All done!

   return bVESuccess;
}
#endif //DONTWANT_RunNonElevated

} // namespace VistaTools

#endif// IMPLEMENT_VISTA_TOOLS
