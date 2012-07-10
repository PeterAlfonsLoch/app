#pragma once


CLASS_DECL_c int to_hex_char(int i);
inline int from_hex_char(char ch)
{
   if(ch >= '0' && ch <= '9')
      return ch - '0';
   else
      return (to_lower(ch) - 'a') + 10;
}