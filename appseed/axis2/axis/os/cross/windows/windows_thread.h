// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//
//
// Emulates a subset of the Win32 threading API as a layer on top of WinRT threadpools.
//
// Supported features:
//
//    - CreateThread (returns a standard Win32 handle which can be waited on, then closed)
//    - CREATE_SUSPENDED and ResumeThread
//    - Partial support for SetThreadPriority (see below)
//    - Sleep
//    - Thread local storage (TlsAlloc, TlsFree, TlsGetValue, TlsSetValue)
//
// Differences from Win32:
//
//    - If using TLS other than from this CreateThread emulation, call TlsShutdown before thread/task exit
//    - No ExitThread or TerminateThread (just return from the thread function to exit)
//    - No SuspendThread, so ResumeThread is only useful in combination with CREATE_SUSPENDED
//    - SetThreadPriority is only available while a thread is in CREATE_SUSPENDED state
//    - SetThreadPriority only supports three priority levels (negative, zero, or positive)
//    - No thread identifier APIs (GetThreadId, GetCurrentThreadId, OpenThread)
//    - No affinity APIs
//    - No GetExitCodeThread
//    - Failure cases return error codes but do not always call SetLastError
#ifndef CA2_APP_AXIS_OS_CROSS_WINDOWS_THREAD_H
#define CA2_APP_AXIS_OS_CROSS_WINDOWS_THREAD_H


#ifndef CREATE_SUSPENDED
#define CREATE_SUSPENDED 0x00000004
#endif



//#if !defined(LINUX) && !defined(SOLARIS)
//typedef struct hthread * HTHREAD;
//#endif

CLASS_DECL_AXIS HTHREAD WINAPI CreateThread(LPSECURITY_ATTRIBUTES unusedThreadAttributes, uint_ptr unusedStackSize, uint32_t (* lpStartAddress)(void *) , void * lpParameter, uint32_t uiCreationFlags, uint32_t * puiId);
CLASS_DECL_AXIS DWORD WINAPI ResumeThread(HTHREAD hThread);
CLASS_DECL_AXIS int_bool WINAPI SetThreadPriority(HTHREAD hThread, int32_t nPriority);
CLASS_DECL_AXIS int32_t WINAPI GetThreadPriority(HTHREAD hThread);


CLASS_DECL_AXIS VOID WINAPI Sleep(DWORD dwMilliseconds);

CLASS_DECL_AXIS DWORD WINAPI TlsAlloc();
CLASS_DECL_AXIS int_bool WINAPI TlsFree(DWORD dwTlsIndex);
CLASS_DECL_AXIS LPVOID WINAPI TlsGetValue(DWORD dwTlsIndex);
CLASS_DECL_AXIS int_bool WINAPI TlsSetValue(DWORD dwTlsIndex, LPVOID lpTlsValue);

void WINAPI TlsShutdown();


#if defined(METROWIN) && defined(__cplusplus_winrt)


interface IDWriteFactory;
interface ID2D1Factory1;
interface ID3D11Device;
interface ID3D11DeviceContext;
interface ID3D11Device1;
interface IDXGIDevice;

CLASS_DECL_AXIS IDWriteFactory * TlsGetWriteFactory();
CLASS_DECL_AXIS ID2D1Factory1 * GetD2D1Factory1();
CLASS_DECL_AXIS ID3D11Device * TlsGetD3D11Device();
CLASS_DECL_AXIS ID3D11DeviceContext * TlsGetD3D11DeviceContext();
CLASS_DECL_AXIS ID3D11Device1 * TlsGetD3D11Device1();
CLASS_DECL_AXIS IDXGIDevice * TlsGetDXGIDevice();

#define TLS_WRITE_FACTORY     12
#define TLS_D2D1_FACTORY1     13
#define TLS_d3_1              14
#define TLS_d3_2              15
#define TLS_d3_3              16
#define TLS_d3_4              17

#elif !defined(WINDOWS)

#define PM_NOREMOVE 0
#define PM_REMOVE 1

#endif


#define TLS_MESSAGE_QUEUE     127




#endif // CA2_APP_AXIS_OS_CROSS_WINDOWS_THREAD_H
