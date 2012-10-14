#pragma once


/*
CLASS_DECL_c _Use_decl_annotations_ HANDLE WINAPI CreateThread(LPSECURITY_ATTRIBUTES unusedThreadAttributes, SIZE_T unusedStackSize, LPTHREAD_START_ROUTINE lpStartAddress, LPVOID lpParameter, DWORD dwCreationFlags, LPDWORD unusedThreadId);
CLASS_DECL_c _Use_decl_annotations_ DWORD WINAPI ResumeThread(HANDLE hThread);
CLASS_DECL_c _Use_decl_annotations_ BOOL WINAPI SetThreadPriority(HANDLE hThread, int nPriority);
CLASS_DECL_c _Use_decl_annotations_ VOID WINAPI Sleep(DWORD dwMilliseconds);
CLASS_DECL_c DWORD WINAPI TlsAlloc();
CLASS_DECL_c _Use_decl_annotations_ BOOL WINAPI TlsFree(DWORD dwTlsIndex);
CLASS_DECL_c _Use_decl_annotations_ LPVOID WINAPI TlsGetValue(DWORD dwTlsIndex);
CLASS_DECL_c _Use_decl_annotations_ BOOL WINAPI TlsSetValue(DWORD dwTlsIndex, LPVOID lpTlsValue);
CLASS_DECL_c void WINAPI TlsShutdown();
CLASS_DECL_c int WINAPI GetThreadPriority(_In_ HANDLE hThread);
*/