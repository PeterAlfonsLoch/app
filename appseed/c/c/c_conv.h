#pragma once


CLASS_DECL_c int to_hex_char(int i);
inline int from_hex_char(char ch)
{
   if(ch >= '0' && ch <= '9')
      return ch - '0';
   else
      return (to_lower(ch) - 'a') + 10;
}


CLASS_DECL_c int nibble_to_low_hex(byte nibble);


CLASS_DECL_c char to_upper(int ch);
CLASS_DECL_c char * to_upper(char * pchParam);
