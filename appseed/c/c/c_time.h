#pragma once


CLASS_DECL_c dword get_tick_count();


#ifdef WINDOWSEX

CLASS_DECL_c bool get_file_time(HANDLE hFile, LPFILETIME lpCreationTime, LPFILETIME lpLastAccessTime, LPFILETIME lpLastWriteTime);

#elif defined(METROWIN)

CLASS_DECL_c bool get_file_time(::Windows::Storage::StorageFile ^ file, LPFILETIME lpCreationTime, LPFILETIME lpItemTime, LPFILETIME lpLastWriteTime);

#endif