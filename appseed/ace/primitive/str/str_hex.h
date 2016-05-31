#pragma once



CLASS_DECL_ACE bool ishexdigit(char ch);


namespace hex
{



   CLASS_DECL_ACE int64_t          to_int64(const char * lpcsz);
   CLASS_DECL_ACE uint64_t         to_uint64(const string & lpcsz);
   CLASS_DECL_ACE uint32_t         to_uint(const string & str);

   CLASS_DECL_ACE int64_t          utf8_char_to(const char * pszUtf8Char);

   //CLASS_DECL_ACE string           pad_from(int64_t i, int32_t iPad);


   inline CLASS_DECL_ACE int32_t to(char ch)
   {
      if(ch >= '0' && ch <= '9')
         return ch - '0';
      else
         return (char_to_lower(ch) - 'a') + 10;
   }

   inline CLASS_DECL_ACE char lower_from(byte b)
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


   inline CLASS_DECL_ACE char upper_from(byte b)
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


   inline CLASS_DECL_ACE void lower_from(char * sz, byte b)
   {

      sz[0] = lower_from((b >> 4) & (char) 0x0f);
      sz[1] = lower_from(b & (char) 0x0f);

   }

   inline CLASS_DECL_ACE void upper_from(char * sz, byte b)
   {

      sz[0] = upper_from((b >> 4) & (char) 0x0f);
      sz[1] = upper_from(b & (char) 0x0f);

   }


   // sz buffer should have twice size of s (p)
   inline CLASS_DECL_ACE void lower_from(char * sz, const void * p, memory_size_t s)
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

   inline CLASS_DECL_ACE void upper_from(char * sz, const void * p, memory_size_t s)
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
   inline CLASS_DECL_ACE string lower_from(const void * p, memory_size_t s)
   {
      string str;
      lower_from(str.GetBufferSetLength(s * 2), p, s);
      str.ReleaseBuffer(s * 2);
      return str;
   }

   inline CLASS_DECL_ACE string upper_from(const void * p, memory_size_t s)
   {
      string str;
      upper_from(str.GetBufferSetLength(s * 2), p, s);
      str.ReleaseBuffer(s * 2);
      return str;
   }

   template < typename INT >
   inline string upper_from(INT iValue);

   template < typename INT >
   inline string lower_from(INT iValue)
   {
      return upper_from(iValue).lowered();
   }

   template < typename INT >
   inline string upper_from(INT iValue)
   {
      char sz[sizeof(INT) * 2 + 1];
      count c = sizeof(INT) * 2;
      sz[c] = '\0';
      string str;
      index i = c-1;
      for(; i >=0; i--)
      {
         sz[i] = upper_from((byte) (iValue & 0xf));
         iValue  = iValue >> 4;
         if(iValue == 0)
            break;
      }
      return &sz[i];
   }

   inline string lower_pad_from(INT iValue,int iWidth)
   {
      string str = lower_from(iValue);
      while(str.get_length() < iWidth)
      {
         str = "0" + str;
      }
      return str;
   }

   inline string upper_pad_from(INT iValue,int iWidth)
   {
      string str = upper_from(iValue);
      while(str.get_length() < iWidth)
      {
         str = "0" + str;
      }
      return str;
   }


   inline void to_uint(uint32_t & ui,const string & str) { ui = to_uint(str); }
   inline void to_uint(uint64_t & ui,const string & str) { ui = to_uint64(str); }
   inline uint_ptr to_uint_ptr(const string & str) { uint_ptr ui; to_uint(ui,str); return ui; }

} // namespace hex

