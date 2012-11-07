#pragma once


CLASS_DECL_c void ensure_file_size(HANDLE h, int64_t iSize);
CLASS_DECL_c bool get_file_time(HANDLE hFile, LPFILETIME lpCreationTime, LPFILETIME lpLastAccessTime, LPFILETIME lpLastWriteTime);
