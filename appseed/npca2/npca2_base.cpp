#include "npca2.h"



HANDLE g_hinstancePluginbase = NULL; 























/*bool read_resource_as_file_dup(const char * pszFile, HINSTANCE hinstance, UINT nID, LPCTSTR lpcszType)
{
	
   HRSRC hrsrc = ::FindResource(hinstance, MAKEINTRESOURCE(nID), lpcszType);

	if(hrsrc == NULL)
	   return false;
   
   HGLOBAL hglobalResource = ::LoadResource(hinstance, hrsrc);

	if(hglobalResource == NULL)
	   return false;

   DWORD dwResourseSize = ::SizeofResource(hinstance, hrsrc);

   if(hglobalResource != NULL)
   {
      bool bOk = false;
		
      UINT FAR* pResource = (UINT FAR*) ::LockResource(hglobalResource);
      
      HANDLE hfile = ::CreateFile(pszFile, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);   

      if(hfile != INVALID_HANDLE_VALUE)
      {
         DWORD dwWritten = 0;
         ::WriteFile(hfile, pResource, dwResourseSize, &dwWritten, NULL);
         ::CloseHandle(hfile);
         bOk = dwWritten == dwResourseSize;
      }
      
      ::FreeResource(hglobalResource);

      return bOk;
	}

	return false;

}







bool file_exists_dup(const char * path1)
{
   DWORD dwFileAttributes = ::GetFileAttributes(path1);
   if(dwFileAttributes != INVALID_FILE_ATTRIBUTES && (dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0)
      return true;
   else
      return false;
}

void get_ca2_folder(char * lpszModuleFolder)
{
   strcpy_dup(lpszModuleFolder, "C:");
/*   char lpszModuleFilePath[MAX_PATH * 8];
   HMODULE hmodule = ::GetModuleHandleA("npca2.dll");
   GetModuleFileName(hmodule, lpszModuleFilePath, sizeof(lpszModuleFilePath));
   LPTSTR lpszModuleFileName;
   GetFullPathName(lpszModuleFilePath, sizeof(lpszModuleFilePath), lpszModuleFolder, &lpszModuleFileName);
   lpszModuleFolder[lpszModuleFileName - lpszModuleFolder] = '\0';
   if(strlen_dup(lpszModuleFolder) > 0)
   {
      if(lpszModuleFolder[strlen_dup(lpszModuleFolder) - 1] == '\\'
      || lpszModuleFolder[strlen_dup(lpszModuleFolder) - 1] == '/')
      {
         lpszModuleFolder[strlen_dup(lpszModuleFolder) - 1] = '\0';
      }
   }
}*/


























/*





bool is_file_ok(const char * path1, const char * pszTemplate)
{
   return file_exists_dup(path1);
}






























































void strcat_dup(char * dest, const char * cat)
{
   while(*dest != 0)
      dest++;
   while(*cat != 0)
      *dest++ = *cat++;
   *dest = '\0';
}


void strcpy_dup(char * dest, const char * cpy)
{
   while(*cpy != 0)
      *dest++ = *cpy++;
   *dest = '\0';
}

int  strlen_dup(const char * str)
{
   const char * pszEnd = str;
   while(*pszEnd != 0)
      pszEnd++;
   return pszEnd - str;
}



*/




int npca2_dll_main(HINSTANCE hinstance, DWORD dwReason, LPVOID lpReserved)
{
	UNREFERENCED_PARAMETER(lpReserved);
	if(dwReason == DLL_PROCESS_ATTACH)
	{

      g_hinstancePluginbase = hinstance;

	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
	}
	return 1;   // ok
}



extern "C" int APIENTRY _DllMainCRTStartup(HINSTANCE hinstance, DWORD dwReason, LPVOID lpReserved)
{
   return npca2_dll_main(hinstance, dwReason, lpReserved);
}
