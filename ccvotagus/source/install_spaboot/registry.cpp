#include "install_spaboot.h"

void reg_delete_tree(HKEY hkey, const char * name);


int registry_register(const char * lpszFile)
{
   reg_delete_tree(HKEY_CLASSES_ROOT, ".spaboot");
   HKEY hkey;
   if(ERROR_SUCCESS != ::RegCreateKey(
	   HKEY_CLASSES_ROOT,
	   ".spaboot",
	   &hkey))
      return 1;
   char strValue[2048];
   strcpy_dup(strValue, "ccvotagus_ca2_spaboot_file");
   if(ERROR_SUCCESS != ::RegSetValueEx(hkey, NULL, NULL, REG_SZ,
			(LPBYTE)strValue, (lstrlen(strValue))+1)*sizeof(char))
      return 1;
   strcpy_dup(strValue, "application/x-ccvotagus_ca2_spaboot_file");
   if(ERROR_SUCCESS != ::RegSetValueEx(hkey, "ContentType", NULL, REG_SZ,
			(LPBYTE)strValue, (lstrlen(strValue)+1)*sizeof(char)))
      return 1;
   if(ERROR_SUCCESS != ::RegCloseKey(hkey))
      return 1;
   reg_delete_tree(HKEY_CLASSES_ROOT, "ccvotagus_ca2_spaboot_file");
   if(ERROR_SUCCESS != ::RegCreateKey(
	   HKEY_CLASSES_ROOT,
	   "ccvotagus_ca2_spaboot_file\\shell",
	   &hkey))
      return 1;
   strcpy_dup(strValue, "open");
   if(ERROR_SUCCESS != ::RegSetValueEx(hkey, NULL, NULL, REG_SZ,
			(LPBYTE)strValue, (lstrlen(strValue)+1)*sizeof(char)))
      return 1;
   if(ERROR_SUCCESS != ::RegCloseKey(hkey))
      return 1;
   if(ERROR_SUCCESS != ::RegCreateKey(
	   HKEY_CLASSES_ROOT,
	   "ccvotagus_ca2_spaboot_file\\shell\\open",
	   &hkey))
      return 1;
   strcpy_dup(strValue, "&Open");
   if(ERROR_SUCCESS != ::RegSetValueEx(hkey, NULL, NULL, REG_SZ,
			(LPBYTE)strValue, (lstrlen(strValue)+1)*sizeof(char)))
      return 1;
   if(ERROR_SUCCESS != ::RegCloseKey(hkey))
      return 1;
   if(ERROR_SUCCESS != ::RegCreateKey(
	   HKEY_CLASSES_ROOT,
	   "ccvotagus_ca2_spaboot_file\\shell\\open\\command",
	   &hkey))
      return 1;
   strcpy_dup(strValue, "\"");
   strcat_dup(strValue, lpszFile);
   strcat_dup(strValue, "\" \"%L\"");
   if(ERROR_SUCCESS != ::RegSetValueEx(hkey, NULL, NULL, REG_SZ,
			(LPBYTE)strValue, (lstrlen(strValue)+1)*sizeof(char)))
      return 1;
   if(ERROR_SUCCESS != ::RegCloseKey(hkey))
      return 1;

   reg_delete_tree(HKEY_CLASSES_ROOT, "MIME\\DataBase\\Content Type\\application/x-ccvotagus_ca2_spaboot_file");
   if(ERROR_SUCCESS != ::RegCreateKey(
	   HKEY_CLASSES_ROOT,
	   "MIME\\DataBase\\Content Type\\application/x-ccvotagus_ca2_spaboot_file",
	   &hkey))
      return 1;
   strcpy_dup(strValue, ".spaboot");
   if(ERROR_SUCCESS != ::RegSetValueEx(hkey, "Extension", NULL, REG_SZ,
			(LPBYTE)strValue, (lstrlen(strValue)+1)*sizeof(char)))
      return 1;
   if(ERROR_SUCCESS != ::RegCloseKey(hkey))
      return 1;
   return 0;
}
































































void reg_delete_tree(HKEY hkey, const char * name)
{
   HKEY hkeySub = NULL;
   if(ERROR_SUCCESS == ::RegOpenKey(
      hkey,
      name,
      &hkeySub))
   {
      DWORD dwAlloc = 1026 * 64;
      char * szKey = (char *) malloc(dwAlloc);
      DWORD dwIndex = 0;
      while(ERROR_SUCCESS == ::RegEnumKey(hkeySub, dwIndex, szKey, dwAlloc))
      {
         reg_delete_tree(hkeySub, szKey);
         dwIndex++;
      }
      free(szKey);
      ::RegCloseKey(hkeySub);
   }
   ::RegDeleteKey(hkey, name);
}
