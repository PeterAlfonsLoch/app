#include "framework.h"


void * memset_dup(void * p, int32_t i, size_t iSize)
{
   uchar * puch = (uchar * ) p;
   while(iSize > 0)
   {
      *puch = static_cast < uchar > (i);
      puch++;
      iSize--;
   }
   return p;
}

void * memand_dup(void * p, const void * p1, const void * p2, size_t iSize)
{

   byte * pb = (byte *) p;
   const byte * pb1 = (const byte *) p1;
   const byte * pb2 = (const byte *) p2;

   while(iSize > 0)
   {
      *pb = *pb1 & *pb2;
      pb++;
      pb1++;
      pb2++;
      iSize--;
   }

   return p;

}


//#if (defined(WINDOWS) && defined(X86)) && !defined(DEBUG)

//#pragma function(memcpy)

/*void * memcpy(void * dst, const void * src, size_t iSize)
{
   return memcpy_dup(dst, src, iSize);
}*/

/*#pragma function(memcmp)

int32_t memcmp(const void * sz1, const void * sz2, size_t iLen)
{
   return memcmp_dup(sz1, sz2, iLen);
}

#pragma function(memset)

void * memset(void * p, int32_t uchar, size_t iSize)
{
   return memset_dup(p, uchar, iSize);
}*/

//#endif

void * memcpy_dup(void * dst, const void * src, size_t iSize)
{
   uchar * puchDst = (uchar * ) dst;
   uchar * puchSrc = (uchar * ) src;
   if(puchDst == puchSrc)
      return dst;
   memcpy(dst, src, iSize);
   return dst;
   /*while(iSize > 0)
   {
      *puchDst = *puchSrc;
      puchDst++;
      puchSrc++;
      iSize--;
   }
   return dst;*/
}

void * memrcpy_dup(void * dst, const void * src, size_t iSize)
{
   uchar * puchDst = ((uchar * ) dst) + iSize - 1;
   uchar * puchSrc = ((uchar * ) src) + iSize - 1;
   if(puchDst == puchSrc)
      return dst;
   while(iSize > 0)
   {
      *puchDst = *puchSrc;
      puchDst--;
      puchSrc--;
      iSize--;
   }
   return dst;
}

void * memmov_dup(void * dst, const void * src, size_t iSize)
{
   memmove(dst,  src, iSize);
   /*if(dst <= src)
      return memcpy_dup(dst, src, iSize);
   else
      return memrcpy_dup(dst, src, iSize);*/
   return dst;
}

int32_t memcmp_dup(const void * sz1, const void * sz2, size_t iLen)
{
   if(iLen <= 0)
      return 0; // equal
   if(sz1 == NULL)
   {
      if(sz2 == NULL)
         return 0;
      else
         return -1;
   }
   else if(sz2 == NULL)
   {
      return 1;
   }
   return memcmp(sz1, sz2, iLen);
   /*int32_t iCmp = 0;
   while(iLen > 0)
   {
      iCmp = *(uchar *)sz1 - *(uchar *)sz2;
      if(iCmp != 0)
         return iCmp;
      ((uchar * &)sz1)++;
      ((uchar * &)sz2)++;
      iLen--;
   }
   return iCmp;*/
}




wchar_t * wmemcpy_dup(wchar_t * dst, const wchar_t * src, size_t iSize)
{
   if(dst == src)
      return dst;
   memcpy(dst, src, iSize * sizeof(wchar_t));
   /*while(iSize > 0)
   {
      *dst = *src;
      dst++;
      src++;
      iSize--;
   }*/
   return dst;
}





void * mem_reverse(void * p, size_t iLen)
{

   char * sz = (char *) p;

   ::count iMid = iLen / 2;

   ::count iL = 0;

   ::count iR = iLen - 1;

   char ch;

   for(; iL < iMid; iL++, iR--)
   {
      ch = sz[iL];
      sz[iL] = sz[iR];
      sz[iR] = ch;
   }

   return p;

}


