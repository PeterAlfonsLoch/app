#include "framework.h"

#define BYTE_ALIGN (8)
#define INT_ALIGN (BYTE_ALIGN * sizeof(int32_t))


namespace core
{
   namespace bit
   {

      void int_aligned_copy(int32_t * pDest, int32_t iDest, int32_t * pSrc, int32_t iSrc, int32_t iCount)
      {
         if((iDest % INT_ALIGN) != (iSrc %INT_ALIGN))
         {
            throw "int32_t aligned only";
         }
         int32_t * pFullDest = &pDest[iDest / INT_ALIGN];
         int32_t * pFullSrc = &pSrc[iSrc / INT_ALIGN];
         if((iDest % INT_ALIGN) > 0)
         {
            pFullDest++;            
            pFullSrc++;
         }
         int32_t iFullCount1 = iCount - (iDest % INT_ALIGN);
         int32_t iFullCount2 = iFullCount1 / INT_ALIGN;
         memcpy(pFullDest, pFullSrc, iFullCount2);
         if(pFullDest > pDest)
         {
            int_aligned_copy(pFullDest - 1, pFullSrc - 1, iDest % INT_ALIGN, INT_ALIGN - 1);
         }
         if((iFullCount1 % INT_ALIGN) > 0)
         {
            int_aligned_copy(pFullDest + iFullCount2, pFullSrc + iFullCount2, 0, (iFullCount1 % INT_ALIGN) - 1);
         }
      }

      void int_aligned_copy(int32_t * pDest, int32_t * pSrc, int32_t start, int32_t end)
      {
         for(int32_t i = start; i <= end; i++)
         {
            if((*pSrc >> i) & 1)
            {
               *pDest |= (int32_t) (1 << i);
            }
            else
            {
               *pDest &= (int32_t) ~(1 << i);
            }
         }
      }

      void set(void * p, bool b, int32_t start, int32_t end)
      {
         uchar * pDest = (uchar *) p;
         uchar * pFullDestStart = &pDest[start / BYTE_ALIGN];
         uchar * pFullDestEnd = &pDest[end / BYTE_ALIGN];
         if((start % BYTE_ALIGN) > 0)
         {
            pFullDestStart++;            
         }
         if(((end + 1) % BYTE_ALIGN) > 0)
         {
            pFullDestEnd--;            
         }
         memset(pFullDestStart, b ? 0xFF : 0, (pFullDestEnd - pFullDestStart + 1) / BYTE_ALIGN);
         if((start % BYTE_ALIGN) > 0)
         {
            byte_set(pFullDestStart - 1, b, start % BYTE_ALIGN, BYTE_ALIGN - 1);
         }
         if(((end + 1) % BYTE_ALIGN) > 0)
         {
            byte_set(pFullDestEnd + 1, b, 0, end % BYTE_ALIGN);
         }
      }

      void byte_set(uchar * pDest, bool b, int32_t start, int32_t end)
      {
         if(b)
         {
            for(int32_t i = start; i <= end; i++)
            {
               *pDest |= (int32_t) (1 << i);
            }
         }
         else
         {
            for(int32_t i = start; i <= end; i++)
            {
               *pDest &= (int32_t) ~(1 << i);
            }
         }
      }

   } // namespace bit

} // namespace core


