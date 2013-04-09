#include "framework.h"

































































void reg_delete_tree_dup(HKEY hkey, const char * name)
{
   HKEY hkeySub = ::null();
   if(ERROR_SUCCESS == ::RegOpenKey(
      hkey,
      name,
      &hkeySub))
   {
      uint32_t dwAlloc = 1026 * 64;
      char * szKey = (char *) _ca_alloc(dwAlloc);
      uint32_t dwIndex = 0;
      while(ERROR_SUCCESS == ::RegEnumKey(hkeySub, dwIndex, szKey, dwAlloc))
      {
         reg_delete_tree_dup(hkeySub, szKey);
         dwIndex++;
      }
      _ca_free(szKey, 0);
      ::RegCloseKey(hkeySub);
   }
   ::RegDeleteKey(hkey, name);
}
