#include "StdAfx.h"








/*int app-install.exe(const char * param)
{
   char szModulePath[MAX_PATH * 3];
   ::GetModuleFileNameA((HINSTANCE) ::GetModuleHandleA("npca2.dll"), szModulePath, sizeof(szModulePath));

   char path[MAX_PATH * 3];
   char * file = NULL;
   ::GetFullPathNameA(szModulePath, sizeof(path), path, &file);
   file[0] = '\0';

   strcat_dup(path, "app-install.exe");

   installer_call_sync(path, param);
   return 0;

}*/




