#pragma once


#ifdef WINDOWSEX


enum OF_TYPE
{
	FILES_ONLY = 1,
	MODULES_ONLY = 2,
	ALL_TYPES = 3
};

struct OF_INFO_t
{
	uint32_t dwPID;
	LPCWSTR lpFile;
	HANDLE hFile;
};

typedef void (CALLBACK* OF_CALLBACK)(OF_INFO_t OpenedFileInf0, uint_ptr uUserContext );



extern "C" CLASS_DECL_BASE void ShowOpenedFiles( LPCWSTR lpPath );
extern "C" CLASS_DECL_BASE void GetOpenedFiles( LPCWSTR lpPath, 
													  OF_TYPE Filter,
													  OF_CALLBACK CallBackProc,
													  uint_ptr pUserContext );
#endif



