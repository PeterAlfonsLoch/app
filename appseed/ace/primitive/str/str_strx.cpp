//#include "framework.h"

/* --------------------------------------------------------------------- */

/*
* Index into the table below with the first byte of a UTF-8 sequence to
* get the number of trailing bytes that are supposed to follow it.
* Note that *legal* UTF-8 values can't have 4 or 5-bytes. The table is
* left as-is for anyone who may want to do such conversion, which was
* allowed in earlier algorithms.
*/
const char trailingBytesForUTF8[256] = {
   (const char)  -1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
   1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
   2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2, 3,3,3,3,3,3,3,3,4,4,4,4,5,5,5,5
};

/*
* Magic values subtracted from a buffer value during UTF8 conversion.
* This table contains as many values as there might be trailing bytes
* in a UTF-8 sequence.
*/
static const uint32_t offsetsFromUTF8[6] = { 0x00000000UL, 0x00003080UL, 0x000E2080UL,
   0x03C82080UL, 0xFA082080UL, 0x82082080UL };


const char * utf8_inc(const char * psz)
{
   char len =  1 + trailingBytesForUTF8[(uchar) *psz];
   if(len == 0)      return NULL;
   if(*psz++ == 0)   return NULL;
   if(len == 1)      return psz;
   if(*psz++ == 0)   return NULL;
   if(len == 2)      return psz;
   if(*psz++ == 0)   return NULL;
   if(len == 3)      return psz;
   if(*psz++ == 0)   return NULL;
   if(len == 4)      return psz;
   if(*psz++ == 0)   return NULL;
   if(len == 5)      return psz;
   if(*psz++ == 0)   return NULL;
   if(len == 6)      return psz;
   return NULL;
}



int32_t uni_to_utf8(char * psz, int32_t w)
{
   if(w < 0x0080 )
   {
      psz[0] = (char) w;
      return 1;
   }
   else if(w < 0x0800)
   {
      psz[0] = (char)(0xc0 | ((w) >> 6));
      psz[1] = (char)(0x80 | ((w) & 0x3f));
      return 2;
   }
   else
   {
      psz[0] = (char)(0xe0 | ((w) >> 12));
      psz[1] = (char)(0x80 | (((w) >> 6) & 0x3f));
      psz[2] = (char)(0x80 | ((w) & 0x3f));
      return 3;
   }
}


::count utf16_len(const char * psz)
{
   if(psz == NULL)
      return -1;
   int32_t count = 0;
   while((psz = utf8_inc(psz)) != NULL)
   {
      count++;
   }
   return count;
}

::count utf16_len_len(const char * psz, strsize srclen)
{
   if(psz == NULL)
      return -1;
   int32_t count = 0;
   while(srclen > 0 && (psz = utf8_inc(psz)) != NULL)
   {
      count++;
      srclen--;
   }
   return count;
}


void utf8_to_utf16(unichar * pwsz, const char * psz)
{

   strsize len;

   while(psz != NULL && *psz != '\0')
   {
      
      *pwsz++ = (unichar) ::str::ch::uni_index_len(psz, len);

      psz += len;

   }

   if(psz != NULL)
   {

      *pwsz = L'\0';

   }

}

void utf8_to_utf16_len(unichar * pwsz,const char * psz, strsize srclen)
{

   strsize len;

   while(srclen > 0 && psz != NULL && *psz != '\0')
   {

      *pwsz++ = (unichar) ::str::ch::uni_index_len(psz,len);

      psz += len;

      srclen -= len;

   }

   if(psz != NULL)
   {

      *pwsz = L'\0';

   }

}


/*
WCHAR * utf8_to_utf16(const char * psz)
{

   ::count iCount = utf16_len(psz);

   if(iCount < 0)
      return NULL;

   WCHAR * pwz = new WCHAR[iCount + 1];

   utf8_to_16(pwz, psz);

   return pwz;

}*/

int32_t utf8_len(const unichar * pwsz)
{
   if(pwsz == NULL)
      return -1;
   int32_t count = 0;
   int32_t n;
   char sz[16];
   while(*pwsz != L'\0')
   {
      n = uni_to_utf8(sz, *pwsz);
      if(n <= 0)
         break;
      count += n;
      pwsz++;
   }
   return count;
}

int32_t utf8_len_len(const unichar * pwsz, strsize srclen)
{
   if(pwsz == NULL)
      return -1;
   int32_t count = 0;
   int32_t n;
   char sz[16];
   while(srclen > 0 && *pwsz != L'\0')
   {
      n = uni_to_utf8(sz,*pwsz);
      if(n <= 0)
         break;
      count += n;
      srclen--;
      pwsz++;
   }
   return count;
}


CLASS_DECL_ACE string utf16_to_utf8(const unichar * pwsz,strsize srcLen)
{

   string str;

   strsize len;

   if(srcLen < 0)
   {

      len = utf8_len(pwsz);

   }
   else
   {

      len = utf8_len_len(pwsz,srcLen);

   }

   LPSTR psz = str.GetBufferSetLength(len);

   utf16_to_utf8(psz, pwsz);

   str.ReleaseBuffer();

   return str;
}



void utf16_to_utf8(char * psz, const unichar * pwsz)
{
   //unsigned short * pwsz = (unsigned short *)pwszParam;
   if(pwsz == NULL || psz == NULL)
      return;
   int32_t n;
   while(*pwsz != L'\0')
   {
      n = uni_to_utf8(psz, *pwsz);
      if(n <= 0)
         break;
      pwsz++;
      psz += n;
   }
   *psz = L'\0';
}

void utf16_to_utf8_len(char * psz,const unichar * pwsz, strsize srclen)
{
   //unsigned short * pwsz = (unsigned short *)pwszParam;
   int32_t n;
   while(srclen > 0 && *pwsz != L'\0')
   {
      n = uni_to_utf8(psz,*pwsz);
      if(n <= 0)
         break;
      pwsz++;
      psz += n;
      srclen--;
   }
   *psz = L'\0';
}

/*
char * ::str::international::unicode_to_utf8(const unichar * pwsz)
{
   int32_t iCount = utf8_len(pwsz);
   if(iCount < 0)
      return NULL;
   char * psz = new char[iCount + 1];
   ::str::international::unicode_to_utf8(psz, pwsz);
   return psz;
}
*/


unichar w_to_lower(int32_t c)
{
   uint32_t c1 = CHAR_PROP(c);
   if (CHAR_CATEGORY(c1) == CHAR_CATEGORY_Ll) return unichar(c);
   if (CHAR_CATEGORY(c1) == CHAR_CATEGORY_Lt) return unichar(c+1);
   return unichar(c - (c1>>16));
}









unichar w_to_upper(int32_t c)
{

   uint32_t c1 = CHAR_PROP(c);
   if (CHAR_CATEGORY(c1) == CHAR_CATEGORY_Lu) return unichar(c);
   if (CHAR_CATEGORY(c1) == CHAR_CATEGORY_Lt) return unichar(c-1);
   return unichar(c - (c1>>16));

}




int32_t x_size_of_tables()
{

   return sizeof(arr_idxCharInfo)+sizeof(arr_CharInfo)+sizeof(arr_idxCharInfo2)+sizeof(arr_CharInfo2);

}



