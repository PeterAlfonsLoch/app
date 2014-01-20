#include "framework.h"











string url_encode_dup(const char * psz)
{
   string str;
   char sz[256];
   while (*psz != '\0')
   {
      unsigned char uch = *psz;
      if (isdigit_dup(uch)
         || isalpha_dup(uch)
         || uch == '.'
         || uch == '-'
         || uch == '_')
      {
         str += uch;
      }
      else if (uch == ' ')
      {
         str += "+";
      }
      else
      {
         itoa_dup(sz, uch, 16);
         if (strlen_dup(sz) == 0)
         {
            str += "%00";
         }
         else if (strlen_dup(sz) == 1)
         {
            str += "%0";
            str += sz;
         }
         else if (strlen_dup(sz) == 2)
         {
            str += "%";
            str += sz;
         }
      }
      psz++;
   }
   return str;
}

