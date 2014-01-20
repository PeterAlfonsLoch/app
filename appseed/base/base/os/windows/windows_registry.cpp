#include "framework.h"

































































void reg_delete_tree_dup(HKEY hkey, const char * name)
{
   HKEY hkeySub = NULL;
   if(ERROR_SUCCESS == ::RegOpenKey(
      hkey,
      name,
      &hkeySub))
   {
      uint32_t dwAlloc = 1026 * 64;
      char * szKey = (char *) memory_alloc(dwAlloc);
      uint32_t dwIndex = 0;
      while(ERROR_SUCCESS == ::RegEnumKey(hkeySub, dwIndex, szKey, dwAlloc))
      {
         reg_delete_tree_dup(hkeySub, szKey);
         dwIndex++;
      }
      memory_free_dbg(szKey, 0);
      ::RegCloseKey(hkeySub);
   }
   ::RegDeleteKey(hkey, name);
}
