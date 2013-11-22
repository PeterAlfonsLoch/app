#pragma once


CLASS_DECL_BASE int_bool ensure_file_size(HANDLE h, uint64_t iSize);
CLASS_DECL_BOOT bool get_file_time(HANDLE hFile, LPFILETIME lpCreationTime, LPFILETIME lpLastAccessTime, LPFILETIME lpLastWriteTime);
