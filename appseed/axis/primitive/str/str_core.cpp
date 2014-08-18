#include "framework.h"



CLASS_DECL_BASE int64_t strtoi(const char * psz)
{
   return ::str::to_int64(psz);
}

CLASS_DECL_BASE int64_t strtoi(const wchar_t * psz)
{
   return wtoi64_dup(psz);
}



// string support for template collections

template<> UINT HashKey<const wchar_t *> (const wchar_t * key)
{
   ENSURE_ARG(__is_valid_string(key));
   UINT nHash = 0;
   while (*key)
      nHash = (nHash<<5) + nHash + *key++;
   return nHash;
}



string_manager * s_pstringmanager = NULL;


string_manager * __get_string_manager()
{
   
   
   return s_pstringmanager;
   
   
}


strsize const_empty_string::get_length() const
{
   return 0;
}

void const_empty_string::get_string(char * psz) const
{
   psz[0] = '\0';
}

void const_empty_string::set_string(const string & str, ::action::context actioncontext)
{
   UNREFERENCED_PARAMETER(str);
   UNREFERENCED_PARAMETER(actioncontext);
   throw "cannot set const string";
}

namespace str
{
   CLASS_DECL_BASE const_empty_string g_strEmpty;

   CLASS_DECL_BASE string_interface & empty_string()
   {
      return g_strEmpty;
   }

}



