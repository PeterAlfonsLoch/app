// MethodId.cpp


#include "framework.h"

/*#include "MethodId.h"
#include "../../Common/MyString.h"*/


string ConvertMethodIdToString(uint64_t id);

static inline unichar GetHex(byte value)
{
  return (unichar)((value < 10) ? ('0' + value) : ('A' + (value - 10)));
}

string ConvertMethodIdToString(uint64_t id)
{
  unichar s[32];
  int32_t len = 32;
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
