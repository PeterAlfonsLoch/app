#pragma once

#define INT_TO_NATURAL(i) (i >= 0 ? (unsigned int32_t) i : 0)


#pragma once

inline unsigned int32_t natural(int32_t i)
{
   return i >= 0 ? (unsigned int32_t) i : 0;
}

inline unsigned int32_t natural(unsigned int32_t ui)
{
   return ui;
}

inline unsigned long natural(long l)
{
   return l >= 0 ? (unsigned long) l : 0;
}

inline unsigned long natural(unsigned long ul)
{
   return ul;
}

inline unsigned long long natural(long long ll)
{
   return ll >= 0 ? (unsigned long long) ll: 0;
}

inline unsigned long long natural(unsigned long long ull)
{
   return ull;
}

// return minimum zero or positive integer
// otherwise, return third optional default -1 argument
inline int32_t natural_min(int32_t i1, int32_t i2, int32_t iEscape = -1)
{
   if(i1 >= 0)
   {
      if(i2 >= 0)
      {
         if(i2 < i1)
            return i2;
         else
            return i1;
      }
      else
      {
         return i1;
      }
   }
   else
   {
      if(i2 >= 0)
      {
         return i2;
      }
      else
      {
         return iEscape;
      }
   }
}
