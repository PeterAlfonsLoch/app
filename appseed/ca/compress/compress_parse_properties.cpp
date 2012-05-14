#include "framework.h"


bool StringToBool(const string &s, bool &res)
{
  if (s.is_empty() || s.CompareNoCase("ON") == 0 || s.Compare("+") == 0)
  {
    res = true;
    return true;
  }
  if (s.CompareNoCase("OFF") == 0 || s.Compare("-") == 0)
  {
    res = false;
    return true;
  }
  return false;
}
