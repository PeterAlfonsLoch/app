#include "framework.h"

bool StringToBool(const string &s, bool &res);

bool StringToBool(const string &s, bool &res)
{
  if (s.is_empty() || s.compare_ci("ON") == 0 || s.compare("+") == 0)
  {
    res = true;
    return true;
  }
  if (s.compare_ci("OFF") == 0 || s.compare("-") == 0)
  {
    res = false;
    return true;
  }
  return false;
}
