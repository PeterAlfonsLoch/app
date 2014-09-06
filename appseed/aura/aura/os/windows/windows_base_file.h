#pragma once


typedef uint32_t (WINAPI* GetFinalPathNameByHandleDef)(
	HANDLE hFile,
	LPWSTR lpszFilePath,
	uint32_t cchFilePath,
	uint32_t dwFlags	);



#ifdef __cplusplus

class string;

bool GetDrive(const char * lpDeviceFileName, string & fsFileName, bool bDriveLetterOnly );


#endif


int_bool StopAndUninstallDrv( HANDLE hDrvHandle );

HANDLE ExtractAndInstallDrv();

int ftruncate(int file, file_size len);




CLASS_DECL_AURA int_bool ensure_file_size_handle(HANDLE h, uint64_t iSize);
CLASS_DECL_AURA int_bool get_file_time(HANDLE hFile, LPFILETIME lpCreationTime, LPFILETIME lpLastAccessTime, LPFILETIME lpLastWriteTime);
