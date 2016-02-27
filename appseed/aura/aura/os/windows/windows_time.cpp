//#include "framework.h"






CLASS_DECL_AURA int_bool get_file_time(HANDLE hFile, LPFILETIME lpCreationTime, LPFILETIME lpLastAccessTime, LPFILETIME lpLastWriteTime)
{

   return GetFileTime(hFile, lpCreationTime, lpLastAccessTime, lpLastWriteTime) != FALSE;

}

LARGE_INTEGER g_freq;
LARGE_INTEGER g_firstCounter;

DWORD get_tick_count()
{

   return get_nanos() / (1000 * 1000);

}

uint64_t get_nanos()
{

   LARGE_INTEGER li = {};

   QueryPerformanceCounter(&li);

   return muldiv64(li.QuadPart, 1000 * 1000 * 1000, g_freq.QuadPart);

}


CLASS_DECL_AURA DWORD get_first_tick()
{

   return get_first_nano() / (1000 * 1000);

}

CLASS_DECL_AURA DWORD get_first_nano()
{

   return g_firstCounter.QuadPart * 1000 * 1000 * 1000 / g_freq.QuadPart;

}
