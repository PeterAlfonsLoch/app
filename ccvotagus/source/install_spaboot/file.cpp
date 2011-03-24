#include "install_spaboot.h"
#include "md5.h"


bool read_resource_as_file_dup(const char * pszFile, HINSTANCE hinstance, UINT nID, LPCTSTR lpcszType)
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
}

bool is_file_ok(const char * path1, const char * pszTemplate)
{
   char get[1024];
   strcpy_dup(get, "/md5?authnone&stage=");
   strcat_dup(get, pszTemplate);
   return file_exists_dup(path1) && !stricmp_dup(get_file_md5(path1), ms_get_dup("spaignition.api.veriterse.net", get));
}


bool file_put_contents(const char * path, const char * contents)
{
   HANDLE hfile = ::CreateFile(path, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);   
   if(hfile == INVALID_HANDLE_VALUE)
      return false;
   DWORD dwWrite = strlen_dup(contents);
   DWORD dwWritten = 0;
   BOOL bOk = ::WriteFile(hfile, contents, dwWrite, &dwWritten, NULL);
   ::CloseHandle(hfile);
   return dwWrite == dwWritten && bOk != FALSE;
}




const char * file_get_contents_dup(const char * path)
{
   HANDLE hfile = ::CreateFile(path, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);   
   if(hfile == INVALID_HANDLE_VALUE)
      return NULL;
   DWORD dwSizeHigh;
   DWORD dwSize = ::GetFileSize(hfile, &dwSizeHigh);
   char * psz = (char *) malloc(dwSize + 1);
   DWORD dwRead;
   ::ReadFile(hfile, psz, dwSize, &dwRead, NULL);
   psz[dwSize] = '\0';
   ::CloseHandle(hfile);
   return psz;
}


const char * get_file_md5(const char * path)
{
   md5 md5;
   md5.initialize();
   HANDLE hfile = ::CreateFile(path, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);   
   if(hfile == INVALID_HANDLE_VALUE)
      return NULL;
   DWORD dwSizeHigh;
   DWORD dwSize = ::GetFileSize(hfile, &dwSizeHigh);
   char * psz = (char *) malloc(dwSize);
   DWORD dwRead;
   ::ReadFile(hfile, psz, dwSize, &dwRead, NULL);
   md5.update(psz, dwRead);
   md5.finalize();
   free(psz);
   ::CloseHandle(hfile);
   return md5.to_string();
}