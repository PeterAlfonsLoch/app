// This is ca2 API library.
// 
// 
//
// 
// 
// 
// 
// 

/////////////////////////////////////////////////////////////////////////////
// AFXDLLX.H: Extra header for building an ca2 API Extension DLL
//
// This file is really a source file that you should include in the
// main source file of your DLL.  It must only be included once, and
// not multiple times (you will get linker errors if it is included
// multiple times).  If you do not use _AFXEXT, it is not required
// but you may want the feature it provides.
//
// Previous versions of 32-bit ca2 API did not require this spfile->  This version
// requires this file to support dynamic loading of extension DLLs.  In
// other words, if your application does LoadLibrary on any extension
// DLL (instead of binding to the DLL at link time), this file is
// required.

// Startup code must be unmanaged to avoid loader lock issues.
#pragma managed(push, off)

#ifdef _AFX_MINREBUILD
#pragma component(minrebuild, off)
#endif
#ifndef _AFX_FULLTYPEINFO
#pragma component(mintypeinfo, on)
#endif

// The following symbol used to force inclusion of this module for _AFXEXT
#if defined(_X86_)
extern "C" { int _afxForceEXTDLL; }
#else
extern "C" { int __afxForceEXTDLL; }
#endif

/////////////////////////////////////////////////////////////////////////////
// RawDllMain that saves current app class list and factory list

extern "C" BOOL WINAPI ExtRawDllMain(HINSTANCE, DWORD dwReason, LPVOID);
extern "C" BOOL (WINAPI* const _pRawDllMain)(HINSTANCE, DWORD, LPVOID) = &ExtRawDllMain;

extern "C"
BOOL WINAPI ExtRawDllMain(HINSTANCE, DWORD dwReason, LPVOID)
{
   UNREFERENCED_PARAMETER(dwReason);
   return TRUE;    // ok
}

#ifdef _AFX_MINREBUILD
#pragma component(minrebuild, on)
#endif
#ifndef _AFX_FULLTYPEINFO
#pragma component(mintypeinfo, off)
#endif

/////////////////////////////////////////////////////////////////////////////

#pragma managed(pop)
