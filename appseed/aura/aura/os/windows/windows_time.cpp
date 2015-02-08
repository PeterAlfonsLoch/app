//#include "framework.h"






CLASS_DECL_AURA int_bool get_file_time(HANDLE hFile, LPFILETIME lpCreationTime, LPFILETIME lpLastAccessTime, LPFILETIME lpLastWriteTime)
{

   return GetFileTime(hFile, lpCreationTime, lpLastAccessTime, lpLastWriteTime) != FALSE;

}
