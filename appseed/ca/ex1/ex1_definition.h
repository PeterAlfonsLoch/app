#pragma once


// from 7-zip

namespace ex1
{

   template <class T> inline T MyMin(T a, T b)
   {
      return a < b ? a : b; 
   }

   template <class T> inline T MyMax(T a, T b)
   {
      return a > b ? a : b; 
   }

   template <class T> inline int32_t MyCompare(T a, T b)
   {
      return a < b ? -1 : (a == b ? 0 : 1);
   }

   inline int32_t BoolToInt(bool value)
   { 
      return (value ? 1 : 0); 
   }

   inline bool IntToBool(int32_t value)
   { 
      return (value != 0); 
   }

} // // from 7-zip