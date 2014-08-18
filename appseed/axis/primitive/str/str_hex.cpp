#include "framework.h"


namespace hex
{


   int64_t to_int64(const char * lpcsz)
   {
      int64_t r = 0, num = 0;
      if(lpcsz == NULL)
         return -1;
      for(int64_t i = strlen(lpcsz)-1; i >= 0; i--)
      {
         int64_t d = utf8_char_to(&(lpcsz)[i]);
         if(d == -1)
            return -1;
         num += d << r;
         r += 4;
      }
      return num;
   }

   uint32_t to_uint(const string & str)
   {
      uint32_t r = 0;
      for (int32_t i = 0; i < str.get_length(); i++)
      {
         r = r * 16 + str[i] - 48 - ((str[i] >= 'A') ? 7 : 0) - ((str[i] >= 'a') ? 32 : 0);
      }
      return r;
   }


   int64_t utf8_char_to(const char * pszUtf8Char)
   {
      string low = ::str::ch::to_lower_case(pszUtf8Char);
      int64_t ch = ::str::ch::uni_index(low);
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


/*   string lower_from(void * p, primitive::memory_size s)
   {
      string str;
      char * lpsz = str.GetBufferSetLength(s * 2);
	   lower_from(lpsz, p, s);
      lpsz[s * 2] = '\0';
      str.ReleaseBuffer(s * 2);
      return str;
   }


   string upper_from(void * p, primitive::memory_size s)
   {
      string str;
      char * lpsz = str.GetBufferSetLength(s * 2);
	   upper_from(lpsz, p, s);
      lpsz[s * 2] = '\0';
      str.ReleaseBuffer(s * 2);
      return str;
   }
   */



} // namespace str


