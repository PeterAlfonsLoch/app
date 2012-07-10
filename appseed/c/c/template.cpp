#include "framework.h"


template<> UINT simple_HashKey<const char *> (const char * key)
{
   UINT nHash = 0;
   while (*key)
      nHash = (nHash<<5) + nHash + *key++;
   return nHash;
}

template<> UINT simple_HashKey<const wchar_t *> (const wchar_t * key)
{
   UINT nHash = 0;
   while (*key)
      nHash = (nHash<<5) + nHash + *key++;
   return nHash;
}

template<> UINT simple_HashKey<verisimple_string> (verisimple_string key)
{
   return simple_HashKey((const char *) key);
}


template<> UINT simple_HashKey<verisimple_wstring> (verisimple_wstring key)
{
   return simple_HashKey((const wchar_t *) key);
}

