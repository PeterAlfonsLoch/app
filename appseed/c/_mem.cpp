#include "StdAfx.h"

void * memset_dup(void * p, int uch, size_t iSize)
{
   unsigned char * puch = (unsigned char * ) p;
   while(iSize > 0)
   {
      *puch = static_cast < unsigned char > (uch);
      puch++;
      iSize--;
   }
   return p;
}


#if defined(WINDOWS) && defined(_X86_)

#pragma function(memcpy)

void * memcpy(void * dst, const void * src, size_t iSize)
{
   return memcpy_dup(dst, src, iSize);
}

#endif

void * memcpy_dup(void * dst, const void * src, size_t iSize)
{
   unsigned char * puchDst = (unsigned char * ) dst;
   unsigned char * puchSrc = (unsigned char * ) src;
   if(puchDst == puchSrc)
      return dst;
   while(iSize > 0)
   {
      *puchDst = *puchSrc;
      puchDst++;
      puchSrc++;
      iSize--;
   }
   return dst;
}

void * memrcpy_dup(void * dst, const void * src, size_t iSize)
{
   unsigned char * puchDst = ((unsigned char * ) dst) + iSize - 1;
   unsigned char * puchSrc = ((unsigned char * ) src) + iSize - 1;
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
   if(dst <= src)
      return memcpy_dup(dst, src, iSize);
   else
      return memrcpy_dup(dst, src, iSize);
   return dst;
}

int memcmp_dup(const void * sz1, const void * sz2, size_t iLen)
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
   int iCmp = 0;
   while(iLen > 0)
   {
      iCmp = *(unsigned char *)sz1 - *(unsigned char *)sz2;
      if(iCmp != 0)
         return iCmp;
      ((unsigned char * &)sz1)++;
      ((unsigned char * &)sz2)++;
      iLen--;
   }
   return iCmp;
}




wchar_t * wmemcpy_dup(wchar_t * dst, const wchar_t * src, size_t iSize)
{
   if(dst == src)
      return dst;
   while(iSize > 0)
   {
      *dst = *src;
      dst++;
      src++;
      iSize--;
   }
   return dst;
}


