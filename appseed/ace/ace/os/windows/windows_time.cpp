//#include "framework.h"






CLASS_DECL_ACE int_bool get_file_time(HANDLE hFile, LPFILETIME lpCreationTime, LPFILETIME lpLastAccessTime, LPFILETIME lpLastWriteTime)
{

   return GetFileTime(hFile, lpCreationTime, lpLastAccessTime, lpLastWriteTime) != FALSE;

}

LARGE_INTEGER g_freq;

uint64_t get_nanos()
{

   LARGE_INTEGER li = {};

   QueryPerformanceCounter(&li);

   return muldiv64(li.QuadPart, 1000 * 1000 * 1000, g_freq.QuadPart);

}


