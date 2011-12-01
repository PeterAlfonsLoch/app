#include "StdAfx.h"
#include "prop_id.h"


void StringToProp(const string &s, var * value)
{
  *value = s;
}


string FlagsToString(const CUInt32PCharPair *pairs, unsigned num, uint32 flags)
{
  string s;
  for (unsigned i = 0; i < num; i++)
  {
    const CUInt32PCharPair &p = pairs[i];
    uint32 flag = (uint32)1 << (unsigned)p.Value;
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


void FlagsToProp(const CUInt32PCharPair *pairs, unsigned num, uint32 flags, var * value)
{
  StringToProp(FlagsToString(pairs, num, flags), value);
}
