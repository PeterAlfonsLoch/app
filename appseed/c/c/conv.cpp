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


CLASS_DECL_c int nibble_to_low_hex(byte nibble)
{
   if(nibble >= 0 && nibble <= 9)
   {
      return nibble + '0';
   }
   else if(nibble >= 10 && nibble <= 15)
   {
      return nibble + 'a' - 10;
   }
   else
   {
      return -1;
   }
}
