#pragma once


class CLASS_DECL_c os_thread
{
public:


   DWORD (WINAPI * m_pfn)(LPVOID);
   LPVOID           m_pv;


   os_thread(DWORD (WINAPI * lpStartAddr)(LPVOID), LPVOID);



};


CLASS_DECL_c HANDLE start_thread(DWORD (WINAPI * pfn)(LPVOID), LPVOID pv, int iPriority = 0);


CLASS_DECL_c HANDLE create_thread(LPSECURITY_ATTRIBUTES lpsa, DWORD cbStack, DWORD (WINAPI * pfn)(LPVOID), LPVOID pv, DWORD f, LPDWORD lpdwId);


