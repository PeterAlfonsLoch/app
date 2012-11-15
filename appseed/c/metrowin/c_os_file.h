#pragma once


CLASS_DECL_c void ensure_file_size(HANDLE h, int64_t iSize);
CLASS_DECL_c DWORD GetFileAttributes(const char * psz);
CLASS_DECL_c DWORD GetFileSize(HANDLE h, LPDWORD lpdwHi);
CLASS_DECL_c DWORD SetFilePointer(HANDLE h, LONG lMove, PLONG plHi, DWORD dwMeth);
//CLASS_DECL_c HANDLE FindFirstFile(const char * psz, WIN32_FIND_DATA * pdata);


CLASS_DECL_c BOOL FileTimeToLocalFileTime(const FILETIME * lpFileTime, LPFILETIME lpLocalFileTime);
CLASS_DECL_c BOOL LocalFileTimeToFileTime(const FILETIME * lpFileTime, LPFILETIME lpLocalFileTime);


CLASS_DECL_c ::Windows::Storage::StorageFolder ^ get_os_folder(const char * lpcszDirName);
CLASS_DECL_c ::Windows::Storage::StorageFile ^ get_os_file(const char * lpcszFileName, dword dwDesiredAcces, dword dwShareMode, LPSECURITY_ATTRIBUTES lpSA, dword dwCreationDisposition, dword dwFlagsAndAttributes, HANDLE hTemplateFile);
CLASS_DECL_c bool get_file_time(::Windows::Storage::StorageFile ^ file, LPFILETIME lpCreationTime, LPFILETIME lpItemTime, LPFILETIME lpLastWriteTime);



