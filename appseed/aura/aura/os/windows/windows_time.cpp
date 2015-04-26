//#include "framework.h"






CLASS_DECL_AURA int_bool get_file_time(HANDLE hFile, LPFILETIME lpCreationTime, LPFILETIME lpLastAccessTime, LPFILETIME lpLastWriteTime)
{

   return GetFileTime(hFile, lpCreationTime, lpLastAccessTime, lpLastWriteTime) != FALSE;

}


dword get_tick_count()
{

#ifdef METROWIN

   return (dword)(GetTickCount64() % 0x100000000ULL);

#else

   return (dword)GetTickCount();

#endif

}



