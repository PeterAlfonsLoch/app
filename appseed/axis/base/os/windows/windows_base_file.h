#pragma once


typedef uint32_t (WINAPI* GetFinalPathNameByHandleDef)(
	HANDLE hFile,
	LPWSTR lpszFilePath,
	uint32_t cchFilePath,
	uint32_t dwFlags	);



#ifdef __cplusplus

class string;

bool GetDrive(const char * lpDeviceFileName, string & fsFileName, bool bDriveLetterOnly );

CLASS_DECL_BASE int_bool ensure_file_size(HANDLE h, uint64_t iSize);
CLASS_DECL_BASE int_bool ensure_file_size(int32_t fd, size_t iSize);
CLASS_DECL_BASE int_bool ensure_file_size(FILE * file, size_t iSize);

#endif


int_bool StopAndUninstallDrv( HANDLE hDrvHandle );

HANDLE ExtractAndInstallDrv();

int ftruncate(int file, file_size len);




CLASS_DECL_BASE int_bool ensure_file_size(HANDLE h, uint64_t iSize);
CLASS_DECL_BASE int_bool get_file_time(HANDLE hFile, LPFILETIME lpCreationTime, LPFILETIME lpLastAccessTime, LPFILETIME lpLastWriteTime);
