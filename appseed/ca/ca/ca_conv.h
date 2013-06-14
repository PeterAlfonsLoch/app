#pragma once


inline int32_t to_lo_hex_char(int32_t i)
{

   if(i >= 10 && i <= 15)
   {
      return i + 'a' - 10;
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

inline int32_t to_hi_hex_char(int32_t i)
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


inline char __to_lo_hex_char(byte b)
{

   if(b >= 10)
   {
      return b + 'a' - 10;
   }
   else
   {
      return b + '0';
   }

}


inline char __to_hi_hex_char(byte b)
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

inline int32_t from_hex_char(char ch)
{
   if(ch >= '0' && ch <= '9')
      return ch - '0';
   else
      return (to_lower(ch) - 'a') + 10;
}

inline void byte_to_lo_hex(char * sz, byte b)
{

   sz[0] = __to_lo_hex_char((b >> 4) & (char) 0x0f);
   sz[1] = __to_lo_hex_char(b & (char) 0x0f);

}

inline void byte_to_hi_hex(char * sz, byte b)
{

   sz[0] = __to_hi_hex_char((b >> 4) & (char) 0x0f);
   sz[1] = __to_hi_hex_char(b & (char) 0x0f);

}


CLASS_DECL_c int32_t nibble_to_low_hex(byte nibble);


CLASS_DECL_c char to_upper(int32_t ch);
CLASS_DECL_c char * to_upper(char * pchParam);

// sz buffer should have twice size of s (p)
inline void lo_hex_from(char * sz, void * p, size_t s)
{
    byte * pb = (byte *) p;
    while(s)
    {
        byte_to_lo_hex(sz, *pb);
		s--;
        sz+=2;
        pb++;
    }
}

inline void hi_hex_from(char * sz, void * p, size_t s)
{
    byte * pb = (byte *) p;
    while(s)
    {
        byte_to_hi_hex(sz, *pb);
		s--;
        sz+=2;
        pb++;
    }
}

