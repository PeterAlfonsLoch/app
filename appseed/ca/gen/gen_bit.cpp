#include "framework.h"

#define BYTE_ALIGN (8)
#define INT_ALIGN (BYTE_ALIGN * sizeof(int))


namespace gen
{
   namespace bit
   {

      void int_aligned_copy(int * pDest, int iDest, int * pSrc, int iSrc, int iCount)
      {
         if((iDest % INT_ALIGN) != (iSrc %INT_ALIGN))
         {
            throw "int aligned only";
         }
         int * pFullDest = &pDest[iDest / INT_ALIGN];
         int * pFullSrc = &pSrc[iSrc / INT_ALIGN];
         if((iDest % INT_ALIGN) > 0)
         {
            pFullDest++;            
            pFullSrc++;
         }
         int iFullCount1 = iCount - (iDest % INT_ALIGN);
         int iFullCount2 = iFullCount1 / INT_ALIGN;
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

      void int_aligned_copy(int * pDest, int * pSrc, int start, int end)
      {
         for(int i = start; i <= end; i++)
         {
            if((*pSrc >> i) & 1)
            {
               *pDest |= (int) (1 << i);
            }
            else
            {
               *pDest &= (int) ~(1 << i);
            }
         }
      }

      void set(void * p, bool b, int start, int end)
      {
         unsigned char * pDest = (unsigned char *) p;
         unsigned char * pFullDestStart = &pDest[start / BYTE_ALIGN];
         unsigned char * pFullDestEnd = &pDest[end / BYTE_ALIGN];
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

      void byte_set(unsigned char * pDest, bool b, int start, int end)
      {
         if(b)
         {
            for(int i = start; i <= end; i++)
            {
               *pDest |= (int) (1 << i);
            }
         }
         else
         {
            for(int i = start; i <= end; i++)
            {
               *pDest &= (int) ~(1 << i);
            }
         }
      }

   } // namespace bit

} // namespace gen
