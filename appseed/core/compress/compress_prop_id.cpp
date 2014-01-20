#include "framework.h"


void StringToProp(const string &s, var * value);

string FlagsToString(const CUInt32PCharPair *pairs, uint32_t num, uint32_t flags);


void StringToProp(const string &s, var * value)
{
  *value = s;
}


string FlagsToString(const CUInt32PCharPair *pairs, uint32_t num, uint32_t flags)
{
  string s;
  for (uint32_t i = 0; i < num; i++)
  {
    const CUInt32PCharPair &p = pairs[i];
    uint32_t flag = (uint32_t)1 << (uint32_t)p.Value;
    if ((flags & flag) != 0)
    {
      if (!s.is_empty())
        s += ' ';
      s += p.Name;
    }
    flags &= ~flag;
  }
  if (flags != 0)
  {
    if (!s.is_empty())
      s += ' ';
    string strHex;
    strHex.Format("%0xd", flags);
    s += strHex;
  }
  return s;
}


void FlagsToProp(const CUInt32PCharPair *pairs, uint32_t num, uint32_t flags, var * value)
{
  StringToProp(FlagsToString(pairs, num, flags), value);
}
