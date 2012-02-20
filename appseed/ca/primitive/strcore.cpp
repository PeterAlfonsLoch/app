#include "StdAfx.h"
#include "template/template.h"


CLASS_DECL_ca int64_t strtoi(const char * psz)
{
   return gen::str::atoi64(psz);
}

CLASS_DECL_ca int64_t strtoi(const wchar_t * psz)
{
   return _wtoi64(psz);
}



// string support for template collections

#if _MSC_VER >= 1100
template<> UINT HashKey<const wchar_t *> (const wchar_t * key)
#else
UINT HashKey(const wchar_t * key)
#endif
{
   ENSURE_ARG(AfxIsValidString(key));
   UINT nHash = 0;
   while (*key)
      nHash = (nHash<<5) + nHash + *key++;
   return nHash;
}




string_manager_interface * AfxGetStringManager()
{
   static string_manager s_stringmanager;
   return &s_stringmanager;
}


strsize const_empty_string::get_length() const
{
   return 0;
}

void const_empty_string::get_string(char * psz) const
{
   psz[0] = '\0';
}

void const_empty_string::set_string(const char * psz)
{
   UNREFERENCED_PARAMETER(psz);
   throw "cannot set const string";
}

namespace gen
{
   CLASS_DECL_ca const_empty_string g_strEmpty;

   CLASS_DECL_ca string_interface & empty_string()
   {
      return g_strEmpty;
   }

}



