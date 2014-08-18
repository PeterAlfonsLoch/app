#pragma once


typedef uint32_t (WINAPI* GetFinalPathNameByHandleDef)(
	HANDLE hFile,
	LPWSTR lpszFilePath,
	uint32_t cchFilePath,
	uint32_t dwFlags	);



#ifdef __cplusplus

class string;

bool GetDrive(const char * lpDeviceFileName, string & fsFileName, bool bDriveLetterOnly );

CLASS_DECL_AXIS int_bool ensure_file_size(HANDLE h, uint64_t iSize);
CLASS_DECL_AXIS int_bool ensure_file_size(int32_t fd, size_t iSize);
CLASS_DECL_AXIS int_bool ensure_file_size(FILE * file, size_t iSize);

#endif


int_bool StopAndUninstallDrv( HANDLE hDrvHandle );

HANDLE ExtractAndInstallDrv();

int ftruncate(int file, int64_t len);




CLASS_DECL_AXIS int_bool ensure_file_size(HANDLE h, uint64_t iSize);
CLASS_DECL_AXIS int_bool get_file_time(HANDLE hFile, LPFILETIME lpCreationTime, LPFILETIME lpLastAccessTime, LPFILETIME lpLastWriteTime);
