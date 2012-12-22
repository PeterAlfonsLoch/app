#pragma once


inline int to_hex_char(int i)
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

inline char __to_hex_char(byte b)
{

   if(b >= 10)
   {
      return b + 'A' - 10;
   }
   else
   {
      return b + '0';
   }

}


inline int from_hex_char(char ch)
{
   if(ch >= '0' && ch <= '9')
      return ch - '0';
   else
      return (to_lower(ch) - 'a') + 10;
}

inline void byte_to_hex(char * sz, byte b)
{

   sz[0] = __to_hex_char((b >> 4) & (char) 0x0f);
   sz[1] = __to_hex_char(b & (char) 0x0f);

}



CLASS_DECL_c int nibble_to_low_hex(byte nibble);


CLASS_DECL_c char to_upper(int ch);
CLASS_DECL_c char * to_upper(char * pchParam);
