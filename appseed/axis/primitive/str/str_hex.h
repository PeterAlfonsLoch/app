#pragma once


namespace hex
{


   CLASS_DECL_BASE int64_t          to_int64(const char * lpcsz);
   CLASS_DECL_BASE uint32_t         to_uint(const string & str);

   CLASS_DECL_BASE int64_t          utf8_char_to(const char * pszUtf8Char);

   //CLASS_DECL_BASE string           pad_from(int64_t i, int32_t iPad);

   
   inline CLASS_DECL_BASE int32_t to(char ch)
   {
      if(ch >= '0' && ch <= '9')
         return ch - '0';
      else
         return (char_to_lower(ch) - 'a') + 10;
   }

   inline CLASS_DECL_BASE char lower_from(byte b)
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


   inline CLASS_DECL_BASE char upper_from(byte b)
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


   inline CLASS_DECL_BASE void lower_from(char * sz, byte b)
   {

      sz[0] = lower_from((b >> 4) & (char) 0x0f);
      sz[1] = lower_from(b & (char) 0x0f);

   }

   inline CLASS_DECL_BASE void upper_from(char * sz, byte b)
   {

      sz[0] = upper_from((b >> 4) & (char) 0x0f);
      sz[1] = upper_from(b & (char) 0x0f);

   }


   // sz buffer should have twice size of s (p)
   inline CLASS_DECL_BASE void lower_from(char * sz, const void * p, ::primitive::memory_size s)
   {
       const byte * pb = (const byte *) p;
       while(s)
       {
           lower_from(sz, *pb);
		      s--;
           sz+=2;
           pb++;
       }
   }

   inline CLASS_DECL_BASE void upper_from(char * sz, const void * p, ::primitive::memory_size s)
   {
       const byte * pb = (const byte *) p;
       while(s)
       {
           upper_from(sz, *pb);
		     s--;
           sz+=2;
           pb++;
       }
   }

   // sz buffer should have twice size of s (p)
   inline CLASS_DECL_BASE string lower_from(const void * p, ::primitive::memory_size s)
   {
      string str;
      lower_from(str.GetBufferSetLength(s * 2), p, s);
      str.ReleaseBuffer(s * 2);
      return str;
   }

   inline CLASS_DECL_BASE string upper_from(const void * p, ::primitive::memory_size s)
   {
      string str;
      upper_from(str.GetBufferSetLength(s * 2), p, s);
      str.ReleaseBuffer(s * 2);
      return str;
   }

   template < typename INT >
   inline string lower_from(INT iValue)
   {
      count c = sizeof(INT) * 2;
      string str;
      LPSTR sz = str.GetBufferSetLength(c);
      for(index i = 0; i < c; i++)
      {
         sz[i] = lower_from((byte) ((iValue >> (4 * i)) &  0xf));
      }
      sz[c] = '\0';
      str.ReleaseBuffer(c);
      return str;
   }

   template < typename INT >
   inline string upper_from(INT iValue)
   {
      count c = sizeof(INT) * 2;
      string str;
      LPSTR sz = str.GetBufferSetLength(c);
      for(index i = 0; i < c; i++)
      {
         sz[i] = upper_from((byte) ((iValue >> (4 * i)) &  0xf));
      }
      sz[c] = '\0';
      str.ReleaseBuffer(c);
      return str;
   }

} // namespace hex

