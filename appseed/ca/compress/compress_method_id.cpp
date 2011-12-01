// MethodId.cpp
// at Sector8J from 7-zip on afternoon of 14/01/2001 - Friday

#include "StdAfx.h"

/*#include "MethodId.h"
#include "../../Common/MyString.h"*/




static inline wchar_t GetHex(byte value)
{
  return (wchar_t)((value < 10) ? ('0' + value) : ('A' + (value - 10)));
}

string ConvertMethodIdToString(uint64 id)
{
  wchar_t s[32];
  int len = 32;
  s[--len] = 0;
  do
  {
    s[--len] = GetHex((byte)id & 0xF);
    id >>= 4;
    s[--len] = GetHex((byte)id & 0xF);
    id >>= 4;
  }
  while (id != 0);
  return s + len;
}
