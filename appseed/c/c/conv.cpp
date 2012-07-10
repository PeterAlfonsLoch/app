#include "framework.h"

int to_hex_char(int i)
{
   if(i >= 10 && i <= 15)
   {
      return i + 'A' - 10;
   }
   else if(i >= 0 && i <= 9)
   {
      return i + '0';
   }
   else
   {
      return 0;
   }

}

