#pragma once


#ifndef WINDOWS


class CLASS_DECL_c hglobal
{
public:

   char     m_szFile[256];
   int32_t      m_fd;
   void *   m_map;

};


typedef hglobal * HGLOBAL;


HGLOBAL WINAPI GlobalAlloc(UINT uFlags, SIZE_T dwBytes);
HGLOBAL WINAPI GlobalReAlloc(HGLOBAL hMem, SIZE_T dwBytes, UINT uFlags);
HGLOBAL WINAPI GlobalFree(HGLOBAL hMem);

LPVOID WINAPI GlobalLock(HGLOBAL hMem);
bool WINAPI GlobalUnlock(HGLOBAL hMem);

SIZE_T WINAPI GlobalSize(HGLOBAL hMem);


#endif




