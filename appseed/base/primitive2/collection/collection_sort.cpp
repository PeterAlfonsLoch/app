#include "framework.h"


namespace  sort
{

   void quick_sort(
                  ::array<uint32_t, uint32_t> & array,
                  int32_t fCompare(const index, const index),
                  void swap(void * lpVoidSwapArg, index iA, index iB),
                  void * lpVoidSwapArg);
   
   void BubbleSort(LPINT lpInt, int32_t size);
   


   void quick_sort(
      ::array<uint32_t, uint32_t> & array,
      int32_t fCompare(const index, const index),
      void swap(void * lpVoidSwapArg, index iA, index iB),
      void * lpVoidSwapArg)
   {
      
      index_array stackLowerBound;
      index_array stackUpperBound;
      index iLowerBound;
      index iUpperBound;
      index iLPos, iUPos, iMPos;

      uint32_t t;

      if(array.get_size() >= 2)
      {
         stackLowerBound.push(0);
         stackUpperBound.push(array.get_upper_bound());
         while(true)
         {
            iLowerBound = stackLowerBound.pop();
            iUpperBound = stackUpperBound.pop();
            iLPos = iLowerBound;
            iMPos = iLowerBound;
            iUPos = iUpperBound;
            while(true)
            {
               while(true)
               {
                  if(iMPos == iUPos)
                     break;
                  if(fCompare(array.get_at(iMPos), array.get_at(iUPos)) <= 0)
                     iUPos--;
                  else
                  {
                     t = array.get_at(iMPos);
                     array.set_at(iMPos, array.get_at(iUPos));
                     array.set_at(iUPos, t);
                     swap(lpVoidSwapArg, iUPos, iMPos);
                     break;
                  }
               }
               if(iMPos == iUPos)
                  break;
               iMPos = iUPos;
               while(true)
               {
                  if(iMPos == iLPos)
                     break;
                  if(fCompare(array.get_at(iLPos), array.get_at(iMPos)) <= 0)
                     iLPos++;
                  else
                  {
                     t = array.get_at(iMPos);
                     array.set_at(iMPos, array.get_at(iLPos));
                     array.set_at(iLPos, t);
                     swap(lpVoidSwapArg, iLPos, iMPos);
                     break;
                  }
               }
               if(iMPos == iLPos)
                  break;
               iMPos = iLPos;
            }
            if(iLowerBound < iMPos - 1)
            {
               stackLowerBound.push(iLowerBound);
               stackUpperBound.push(iMPos - 1);
            }
            if(iMPos + 1 < iUpperBound)
            {
               stackLowerBound.push(iMPos + 1);
               stackUpperBound.push(iUpperBound);
            }
            if(stackLowerBound.get_size() == 0)
               break;
         }
      }

   }

   void BubbleSort(LPINT lpInt, int32_t size)
   {
      for(int32_t i = 0; i < size; i++)
         for(int32_t j = i + 1; j < size; j++)
         {
            if(lpInt[i] > lpInt[j])
            {
               INT swap = lpInt[j];
               lpInt[j] = lpInt[i];
               lpInt[i] = swap;
            }
         }

   }



   void quick_sort(
      index iSize,
      ::array < ARG_COMPARE_FUNCTION, ARG_COMPARE_FUNCTION > & comparefna,
      ::array < ARG_SWAP_FUNCTION, ARG_SWAP_FUNCTION > & swapfna,
      ::array < void *, void * > & comparearga,
      ::array < void *, void * > & swaparga)
   {
      
      index_array stackLowerBound;
      index_array stackUpperBound;
      index iLowerBound;
      index iUpperBound;
      index iLPos, iUPos, iMPos;
      
      int32_t iCmp;
      int32_t iCompare;

      if(iSize >= 2)
      {
         stackLowerBound.push(0);
         stackUpperBound.push(iSize - 1);
         while(true)
         {
            iLowerBound = stackLowerBound.pop();
            iUpperBound = stackUpperBound.pop();
            iLPos = iLowerBound;
            iMPos = iLowerBound;
            iUPos = iUpperBound;
            while(true)
            {
               while(true)
               {
                  if(iMPos == iUPos)
                     break;
                  iCmp = 0;
                  for(int32_t i = 0; i < comparefna.get_size(); i++)
                  {
                     iCompare = comparefna[i](comparearga[i], iMPos, iUPos);
                     if(iCompare > 0)
                     {
                        iCmp = 1;
                        break;
                     }
                     else if(iCompare < 0)
                     {
                        iCmp = -1;
                        break;
                     }
                  }
                  if(iCmp <= 0)
                     iUPos--;
                  else
                  {
                     for(int32_t i = 0; i < swapfna.get_size(); i++)
                     {
                        swapfna[i](swaparga[i], iMPos, iUPos);
                     }
                     break;
                  }
               }
               if(iMPos == iUPos)
                  break;
               iMPos = iUPos;
               while(true)
               {
                  if(iMPos == iLPos)
                     break;
                  iCmp = 0;
                  for(int32_t i = 0; i < comparefna.get_size(); i++)
                  {
                     iCompare = comparefna[i](comparearga[i], iLPos, iMPos);
                     if(iCompare > 0)
                     {
                        iCmp = 1;
                        break;
                     }
                     else if(iCompare < 0)
                     {
                        iCmp = -1;
                        break;
                     }
                  }
                  if(iCmp <= 0)
                     iLPos++;
                  else
                  {
                     for(int32_t i = 0; i < swapfna.get_size(); i++)
                     {
                        swapfna[i](swaparga[i], iLPos, iMPos);
                     }
                     break;
                  }
               }
               if(iMPos == iLPos)
                  break;
               iMPos = iLPos;
            }
            if(iLowerBound < iMPos - 1)
            {
               stackLowerBound.push(iLowerBound);
               stackUpperBound.push(iMPos - 1);
            }
            if(iMPos + 1 < iUpperBound)
            {
               stackLowerBound.push(iMPos + 1);
               stackUpperBound.push(iUpperBound);
            }
            if(stackLowerBound.get_size() == 0)
               break;
         }
      }
   }


} // namespace sort


