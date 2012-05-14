// Common/IntToString.cpp
// from 7-zip on 2010-12-26, morning with Lucinho at torvon and me at eco - at veriverse
#include "framework.h"

//#include "IntToString.h"

string convert_to_string(uint64 value, uint32 base)
{
  if (base < 2 || base > 36)
  {
    return "";
  }
  char sz[72];
  int pos = 0;
  do
  {
    int delta = (int)(value % base);
    sz[pos++] = (char)((delta < 10) ? ('0' + delta) : ('a' + (delta - 10)));
    value /= base;
  }
  while (value != 0);
  return sz;
}

string uint64_to_string(uint64 value)
{
  char sz[32];
  int pos = 0;
  do
  {
    sz[pos++] = (wchar_t)('0' + (int)(value % 10));
    value /= 10;
  }
  while (value != 0);
  return sz;
}

string uint32_base_to_string(uint32 value, uint32 base)
{
   return convert_to_string((uint64) value, base);
}


string int64_to_string(int64 value)
{
   return value < 0 ? "-" + uint64_to_string((uint64) -value) : uint64_to_string((uint64) value);
}


string uint32_to_zero_padded_hex(uint32 value)
{
   char sz[9];
   for (int i = 0; i < 8; i++)
   {
      int t = value & 0xF;
      value >>= 4;
      sz[7 - i] = (char)((t < 10) ? ('0' + t) : ('A' + (t - 10)));
   }
   sz[8] = '\0';
   return sz;
}
