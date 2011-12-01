#pragma once


namespace gen
{
   namespace bit
   {
      CLASS_DECL_ca void int_aligned_copy(int * pDest, int iDest, int * pSrc, int iSrc, int iCount);
      CLASS_DECL_ca void int_aligned_copy(int * pDest, int * pSrc, int start, int end);
      CLASS_DECL_ca void set(void * pDest, bool b, int start, int end);
      CLASS_DECL_ca void byte_set(unsigned char * pDest, bool b, int start, int end);
   }
}
