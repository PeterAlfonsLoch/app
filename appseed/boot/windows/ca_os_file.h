#pragma once


CLASS_DECL_c int_bool ensure_file_size(HANDLE h, uint64_t iSize);
CLASS_DECL_ca bool get_file_time(HANDLE hFile, LPFILETIME lpCreationTime, LPFILETIME lpLastAccessTime, LPFILETIME lpLastWriteTime);
