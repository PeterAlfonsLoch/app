#include "framework.h"


namespace gen
{


   int64_t hex::to_int64(const char * lpcsz)
   {
      int64_t r = 0, num = 0;
      if(lpcsz == NULL)
         return -1;
      for(int64_t i = strlen(lpcsz)-1; i >= 0; i--)
      {
         int64_t d = from_char(&(lpcsz)[i]);
         if(d == -1)
            return -1;
         num += d << r;
         r += 4;
      }
      return num;
   }

   unsigned int hex::to_uint(const string & str)
   {
      unsigned int r = 0;
      for (int i = 0; i < str.get_length(); i++)
      {
         r = r * 16 + str[i] - 48 - ((str[i] >= 'A') ? 7 : 0) - ((str[i] >= 'a') ? 32 : 0);
      }
      return r;
   }


   CLASS_DECL_ca int64_t hex::from_char(const char * pszUtf8Char)
   {
      string low = gen::ch::to_lower_case(pszUtf8Char);
      int64_t ch = gen::ch::uni_index(low);
      ch -= '0';
      if(ch >= 'a'-'0' && ch <= 'f'-'0')
      {
         return ch - 0x27;
      }
      else if (ch <= 9)
      {
         return ch;
      }
      else
      {
         return -1;
      }
   }

   CLASS_DECL_ca string hex::from(void * p, primitive::memory_size s)
   {
      byte * pb = (byte *) p;
      string str;
      LPTSTR lpsz = str.GetBufferSetLength(s * 2);
      while(s > 0)
      {
         byte_to_hex(lpsz, *pb);
         s--;
         lpsz+=2;
         pb++;
      }
      *lpsz = '\0';
      str.ReleaseBuffer();
      return str;
   }

} // namespace gen


