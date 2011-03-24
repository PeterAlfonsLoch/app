#include "install_spaboot.h"

void memset_dup(void * p, unsigned char uch, int iSize)
{
   unsigned char * puch = (unsigned char * ) p;
   while(iSize > 0)
   {
      *puch = uch;
      puch++;
      iSize--;
   }
}




void memcpy_dup(void * dst, void * src, int iSize)
{
   unsigned char * puchDst = (unsigned char * ) dst;
   unsigned char * puchSrc = (unsigned char * ) src;
   while(iSize > 0)
   {
      *puchDst = *puchSrc;
      puchDst++;
      puchSrc++;
      iSize--;
   }
}