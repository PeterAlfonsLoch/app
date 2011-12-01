#include "StdAfx.h"



// AfxIsValidString() returns TRUE if the passed pointer
// references a string of at least the given length in characters.
// A length of -1 (the default parameter) means that the string
// buffer's minimum length isn't known, and the function will
// return TRUE no matter how long the string is. The primitive::memory
// used by the string can be read-only.

BOOL AfxIsValidString(const wchar_t * psz, int nLength /* = -1 */)
{
   return _template::_template_is_valid_string(psz, nLength);
}

// As above, but for ANSI strings.

BOOL AfxIsValidString(const char * psz, int nLength /* = -1 */)
{
   return _template::_template_is_valid_string(psz, nLength);
}

// fx_is_valid_address() returns TRUE if the passed parameter points
// to at least nBytes of accessible primitive::memory. If bReadWrite is TRUE,
// the primitive::memory must be writeable; if bReadWrite is FALSE, the primitive::memory
// may be const.

BOOL fx_is_valid_address(const void * p, UINT_PTR nBytes,
   BOOL bReadWrite /* = TRUE */)
{
   return _template::_template_is_valid_address(p, nBytes, bReadWrite);
}

// AfxIsValidAtom() returns TRUE if the passed parameter is 
// a valid local or global atom.

BOOL AfxIsValidAtom(ATOM nAtom)
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

// fx_is_valid_address() returns TRUE if the passed parameter is 
// a valid representation of a local or a global atom within a const char *.

BOOL AfxIsValidAtom(const char * psz)
{
   return HIWORD(psz) == 0L && AfxIsValidAtom(ATOM(LOWORD(psz)));
}

/////////////////////////////////////////////////////////////////////////////
