#include "framework.h"




 // __is_valid_atom() returns TRUE if the passed parameter is 
// a valid local or global atom.

bool __is_valid_atom(ATOM nAtom)
{
   char sBuffer[256];
   if (GetAtomName(nAtom, sBuffer, _countof(sBuffer)))
   {
      return TRUE;
   }
   DWORD dwError = GetLastError();
   if (dwError == ERROR_INSUFFICIENT_BUFFER || dwError == ERROR_MORE_DATA)
   {
      return TRUE;
   }
   if (GlobalGetAtomName(nAtom, sBuffer, _countof(sBuffer)))
   {
      return TRUE;
   }
   dwError = GetLastError();
   if (dwError == ERROR_INSUFFICIENT_BUFFER || dwError == ERROR_MORE_DATA)
   {
      return TRUE;
   }
   return FALSE;
}

// __is_valid_address() returns TRUE if the passed parameter is 
// a valid representation of a local or a global atom within a const char *.

bool __is_valid_atom(const char * psz)
{
   return HIWORD(psz) == 0L && __is_valid_atom(ATOM(LOWORD(psz)));
}
