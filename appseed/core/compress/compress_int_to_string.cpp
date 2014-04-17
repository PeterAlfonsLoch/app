// Common/IntToString.cpp
#include "framework.h"

//#include "IntToString.h"

string uint64_to_string(uint64_t value);
string uint32_base_to_string(uint32_t value, uint32_t base);
string int64_to_string(int64_t value);
string uint32_to_zero_padded_hex(uint32_t value);

string convert_to_string(uint64_t value, uint32_t base)
{
  if (base <2 || base > 36)
  {
    return "";
  }
  char sz[72];
  int32_t pos = 0;
  do
  {
    int32_t delta = (int32_t)(value % base);
    sz[pos++] = (char)((delta < 10) ? ('0' + delta) : ('a' + (delta - 10)));
    value /= base;
  }
  while (value != 0);
  return sz;
}

string uint64_to_string(uint64_t value)
{
  char sz[32];
  int32_t pos = 0;
  do
  {
    sz[pos++] = (wchar_t)('0' + (int32_t)(value % 10));
    value /= 10;
  }
  while (value != 0);
  return sz;
}

string uint32_base_to_string(uint32_t value, uint32_t base)
{
   return convert_to_string((uint64_t) value, base);
}


string int64_to_string(int64_t value)
{
   return value < 0 ? "-" + uint64_to_string((uint64_t) -value) : uint64_to_string((uint64_t) value);
}


string uint32_to_zero_padded_hex(uint32_t value)
{
   char sz[9];
   for (int32_t i = 0; i < 8; i++)
   {
      int32_t t = value & 0xF;
      value >>= 4;
      sz[7 - i] = (char)((t < 10) ? ('0' + t) : ('A' + (t - 10)));
   }
   sz[8] = '\0';
   return sz;
}
