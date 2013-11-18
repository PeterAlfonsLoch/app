#include "framework.h"


bool hex_to_memory(primitive::memory & memory, const char * pszHex)
{
   ::count len = strlen(pszHex);
   ::count count = (len + 1) / 2;
   memory.allocate(count);
   index i = 0;
   byte b;
   while (*pszHex != '\0')
   {
      char ch = (char)tolower(*pszHex);
      if (ch >= '0' && ch <= '9')
      {
         b = ch - '0';
      }
      else if (ch >= 'a' && ch <= 'f')
      {
         b = ch - 'a' + 10;
      }
      else
      {
         return false;
      }
      pszHex++;
      if (*pszHex == '\0')
      {
         memory.get_data()[i] = b;
         return true;
      }
      b = b << 4;
      ch = (char)tolower(*pszHex);
      if (ch >= '0' && ch <= '9')
      {
         b |= (ch - '0');
      }
      else if (ch >= 'a' && ch <= 'f')
      {
         b |= (ch - 'a' + 10);
      }
      else
      {
         return false;
      }
      pszHex++;
      memory.get_data()[i] = b;
      i++;
   }
   return true;
}


void memory_to_hex(string & strHex, primitive::memory & memory)
{
   ::count count = memory.get_size();
   LPSTR lpsz = strHex.GetBufferSetLength(count * 2);
   for (index i = 0; i < count; i++)
   {
      *lpsz++ = ::hex::lower_from((byte)((memory.get_data()[i] >> 4) & 0xf));
      *lpsz++ = ::hex::lower_from((byte)(memory.get_data()[i] & 0xf));
   }
   strHex.ReleaseBuffer(count * 2);
}

