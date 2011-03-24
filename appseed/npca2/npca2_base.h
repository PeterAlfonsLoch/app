#pragma once


#include <windows.h>
typedef short            int16;
typedef unsigned short   uint16;
typedef long             int32;


extern HANDLE g_hinstancePluginbase; 

bool defer_check();


int npca2_dll_main(HINSTANCE hinstance, DWORD dwReason, LPVOID lpReserved);


bool file_exists_dup(const char * path1);
bool read_resource_as_file_dup(const char * pszFile, HINSTANCE hinst, UINT nID, LPCTSTR lpcszType);
void get_ca2_folder(char * lpszModuleFolder);


bool is_file_ok(const char * path1, const char * pszTemplate);


void strcat_dup(char * dest, const char * cat);
void strcpy_dup(char * dest, const char * cat);
int  strlen_dup(const char * cat);
