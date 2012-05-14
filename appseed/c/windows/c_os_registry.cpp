#include "framework.h"

































































void reg_delete_tree_dup(HKEY hkey, const char * name)
{
   HKEY hkeySub = NULL;
   if(ERROR_SUCCESS == ::RegOpenKey(
      hkey,
      name,
      &hkeySub))
   {
      DWORD dwAlloc = 1026 * 64;
      char * szKey = (char *) ca2_alloc(dwAlloc);
      DWORD dwIndex = 0;
      while(ERROR_SUCCESS == ::RegEnumKey(hkeySub, dwIndex, szKey, dwAlloc))
      {
         reg_delete_tree_dup(hkeySub, szKey);
         dwIndex++;
      }
      ca2_free(szKey);
      ::RegCloseKey(hkeySub);
   }
   ::RegDeleteKey(hkey, name);
}
